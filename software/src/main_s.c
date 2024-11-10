#include "../include/driver_audio_i2s.h"
#include "../include/audio_data.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define SAMPLE_RATE 44100
#define PLAY_DURATION 8 
#define TOTAL_SAMPLES (SAMPLE_RATE * PLAY_DURATION)

int main() {
    audio_i2s_t my_config;

    // Initializing I2S interface for speaker output
    if (audio_i2s_init(&my_config) < 0) {
        printf("Error initializing audio I2S for speaker\n");
        return -1;
    }

    // Enable speaker output by setting control register
    audio_i2s_set_reg(&my_config, AUDIO_I2S_CR, 0x2); 

    // Load audio data from wav file
    const char *filename = "input.wav";
    AudioData *audio_data = get_audio_data(filename);
    if (!audio_data) {
        fprintf(stderr, "Failed to load audio data from %s\n", filename);
        audio_i2s_release(&my_config);
        return -1;
    }

    printf("Audio Data Loaded:\n");
    printf("Sample Rate: %u\n", audio_data->sample_rate);
    printf("Channels: %u\n", audio_data->num_channels);
    printf("Bits per Sample: %u\n", audio_data->bits_per_sample);

    // Send audio data to speaker 
    printf("Starting audio playback...\n");
    if (audio_i2s_send(&my_config, (uint32_t*)audio_data->audio_data, audio_data->data_size) < 0) {
        fprintf(stderr, "Error playing audio\n");
        free_audio_data(audio_data);
        audio_i2s_release(&my_config);
        return -1;
    }

    // Free resources 
    free_audio_data(audio_data);
    audio_i2s_release(&my_config);

    printf("Playback complete.\n");
    return 0;
}