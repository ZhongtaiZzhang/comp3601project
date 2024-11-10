#include "../include/audio_data.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

AudioData* get_audio_data(const char *filename) {
    FILE *wav_file = fopen(filename, "rb");
    if (!wav_file) {
        fprintf(stderr, "Can't open %s\n", filename);
        return NULL;
    }

    AudioData *audio_data = (AudioData *)malloc(sizeof(AudioData));
    if (!audio_data) {
        fprintf(stderr, "Can't allocate the memory\n");
        fclose(wav_file);
        return NULL;
    }

    // beginning of the file
    fseek(wav_file, 0, SEEK_SET);

    // jump to 22 to get num channels
    fseek(wav_file, 22, SEEK_SET);
    fread(&audio_data->num_channels, sizeof(uint16_t), 1, wav_file);

    // then read the sample rate
    fread(&audio_data->sample_rate, sizeof(uint32_t), 1, wav_file);

    // jump to 34 to get bits per sample
    fseek(wav_file, 34, SEEK_SET);
    fread(&audio_data->bits_per_sample, sizeof(uint16_t), 1, wav_file);

    // jump to 40 to get the size of data
    fseek(wav_file, 40, SEEK_SET);
    fread(&audio_data->data_size, sizeof(uint32_t), 1, wav_file);

    // allocate memory for audio data
    audio_data->audio_data = malloc(audio_data->data_size);
    if (!audio_data->audio_data) {
        fprintf(stderr, "Memory for audio data allocation failed.\n");
        free(audio_data);
        fclose(wav_file);
        return NULL;
    }

    fread(audio_data->audio_data, 1, audio_data->data_size, wav_file);
    fclose(wav_file);

    return audio_data;
}

void free_audio_data(AudioData *audio_data) {
    if (audio_data) {
        free(audio_data->audio_data);
        free(audio_data);
    }
}

void print_audio_samples(const AudioData *audio_data, size_t num_samples) {
    if (!audio_data || !audio_data->audio_data) {
        fprintf(stderr, "There is no audio data\n");
        return;
    }

    printf("Sample Rate is %u\n", audio_data->sample_rate);
    printf("Channels is %u\n", audio_data->num_channels);
    printf("Bits per Sample is %u\n", audio_data->bits_per_sample);

    if (audio_data->bits_per_sample == 16) {
        int16_t *samples = (int16_t *)audio_data->audio_data;
        for (size_t i = 0; i < num_samples && i < audio_data->data_size / 2; i++) {
            printf("%d\n", samples[i]);
        }
    } else if (audio_data->bits_per_sample == 32) {
        int32_t *samples = (int32_t *)audio_data->audio_data;
        for (size_t i = 0; i < num_samples && i < audio_data->data_size / 4; i++) {
            printf("%d\n", samples[i]);
        }
    } else {
        printf("Error: Bits per sample %u may not be supported\n", audio_data->bits_per_sample);
    }
}

int main() {
    const char *filename = "output.wav";

    AudioData *audio_data = get_audio_data(filename);
    if (!audio_data) {
        fprintf(stderr, "Something went wrong with the audio data\n");
        return -1;
    }

    print_audio_samples(audio_data, TOTAL_SAMPLES);

    free_audio_data(audio_data);

    return 0;
}