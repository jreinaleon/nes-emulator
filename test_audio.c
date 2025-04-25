#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>

#define SAMPLE_RATE 44100  // Frecuencia de muestreo
#define AMPLITUDE 28000    // Amplitud de la onda (máximo valor de 16 bits)
#define FREQUENCY 440.0   // Frecuencia de la onda (en Hz, 440 Hz es el tono A4)

SDL_AudioDeviceID device_id;

void audio_callback(void *userdata, Uint8 *stream, int len) {
    static double phase = 0;
    Sint16 *buffer = (Sint16 *)stream;
    int num_samples = len / sizeof(Sint16);
    double increment = 2.0 * M_PI * FREQUENCY / SAMPLE_RATE;

    for (int i = 0; i < num_samples; i++) {
        buffer[i] = (Sint16)(AMPLITUDE * sin(phase));  // Onda senoidal
        phase += increment;
        if (phase >= 2.0 * M_PI) phase -= 2.0 * M_PI;  // Normalizar la fase
    }
}

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        return -1;
    }

    SDL_AudioSpec desired_spec;
    SDL_AudioSpec obtained_spec;

    // Establecer la configuración de audio deseada
    desired_spec.freq = SAMPLE_RATE;
    desired_spec.format = AUDIO_S16SYS;
    desired_spec.channels = 1;  // Mono
    desired_spec.samples = 2048; // Tamaño del buffer de audio
    desired_spec.callback = audio_callback; // La función que genera el audio

    // Abrir el dispositivo de audio
    device_id = SDL_OpenAudioDevice(NULL, 0, &desired_spec, &obtained_spec, 0);
    if (device_id == 0) {
        fprintf(stderr, "SDL_OpenAudioDevice failed: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    // Iniciar la reproducción de audio
    SDL_PauseAudioDevice(device_id, 0);

    printf("Reproduciendo sonido... Presiona Ctrl+C para salir.\n");

    // Ejecutar hasta que el usuario cierre el programa
    SDL_Delay(5000);  // Reproducir durante 5 segundos

    // Detener y cerrar el dispositivo de audio
    SDL_PauseAudioDevice(device_id, 1);
    SDL_CloseAudioDevice(device_id);

    SDL_Quit();
    return 0;
}
