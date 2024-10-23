#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "audio_i2s.h"
#include "../include/wave.h"

#define RECORD_DURATION 8        
#define TOTAL_SAMPLES (SAMPLE_RATE * RECORD_DURATION * NUM_CHANNELS)

int main() {

    uint32_t audio_buffer[TOTAL_SAMPLES] = {0};
    uint32_t index = 0;

    audio_i2s_t my_config;
    if (audio_i2s_init(&my_config) < 0) {
        printf("Error initializing audio I2S\n");
        return -1;
    }

    printf("mmapped address: %p\n", my_config.v_baseaddr);
    printf("Before writing to CR: %08x\n", audio_i2s_get_reg(&my_config, AUDIO_I2S_CR));
    audio_i2s_set_reg(&my_config, AUDIO_I2S_CR, 0x1);
    printf("After writing to CR: %08x\n", audio_i2s_get_reg(&my_config, AUDIO_I2S_CR));
    printf("SR: %08x\n", audio_i2s_get_reg(&my_config, AUDIO_I2S_SR));
    printf("Key: %08x\n", audio_i2s_get_reg(&my_config, AUDIO_I2S_KEY));
    printf("Before writing to gain: %08x\n", audio_i2s_get_reg(&my_config, AUDIO_I2S_GAIN));
    audio_i2s_set_reg(&my_config, AUDIO_I2S_GAIN, 0x1);
    printf("After writing to gain: %08x\n", audio_i2s_get_reg(&my_config, AUDIO_I2S_GAIN));

    printf("Starting audio recording for %d seconds...\n", RECORD_DURATION);


    while (index < TOTAL_SAMPLES) {
        int32_t *samples = audio_i2s_recv(&my_config);
        
        for (int i = 0; i < TRANSFER_LEN && index < TOTAL_SAMPLES; i++) {
            audio_buffer[index++] = samples[i];
        }
    }

     for (int i = 0; i < 200; i++) {
        printf("Sample %d: %d\n", i, audio_buffer[i]);  
    }

    printf("Recording complete. Saving to WAV file...\n");

    save_wav_file("output.wav", TOTAL_SAMPLES, audio_buffer, SAMPLE_RATE, NUM_CHANNELS, BITS_PER_SAMPLE);

    printf("WAV file saved as output.wav\n");

    audio_i2s_release(&my_config);

    return 0;
}
