#include "apu.h"
#include <SDL2/SDL.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

// Frecuencia de muestreo (para audio)
#define SAMPLE_RATE 44100

apu_t apu;

// Función para inicializar los canales de la APU
void init_apu(apu_t* apu) {
    memset(apu, 0, sizeof(apu_t)); // Inicializar todos los canales a cero

    // Inicializar el canal de onda cuadrada 1
    apu->pulse1.duty_cycle = 0;
    apu->pulse1.envelope = 0;
    apu->pulse1.sweep = 0;
    apu->pulse1.frequency = 0;
    apu->pulse1.length_counter = 0;
    apu->pulse1.active = false;

    // Inicializar el canal de onda cuadrada 2
    apu->pulse2.duty_cycle = 0;
    apu->pulse2.envelope = 0;
    apu->pulse2.sweep = 0;
    apu->pulse2.frequency = 0;
    apu->pulse2.length_counter = 0;
    apu->pulse2.active = false;

    // Inicializar el canal de onda triangular
    apu->triangle.frequency = 0;
    apu->triangle.length_counter = 0;
    apu->triangle.active = false;

    // Inicializar el canal de ruido
    apu->noise.period = 0;
    apu->noise.length_counter = 0;
    apu->noise.active = false;
}

// Función de actualización para los canales de la APU
void update_apu(apu_t* apu) {
    // Actualizar cada uno de los canales según su tipo
    if (apu->pulse1.active) {
        apu->pulse1.frequency = (apu->pulse1.frequency + 1) % 2048;
        if (apu->pulse1.frequency == 0) {
            if (apu->pulse1.length_counter > 0) {
                apu->pulse1.length_counter--;
            }
        }
    }

    if (apu->pulse2.active) {
        apu->pulse2.frequency = (apu->pulse2.frequency + 1) % 2048;
        if (apu->pulse2.frequency == 0) {
            if (apu->pulse2.length_counter > 0) {
                apu->pulse2.length_counter--;
            }
        }
    }

    if (apu->triangle.active) {
        apu->triangle.frequency = (apu->triangle.frequency + 1) % 2048;
        if (apu->triangle.frequency == 0) {
            if (apu->triangle.length_counter > 0) {
                apu->triangle.length_counter--;
            }
        }
    }

    if (apu->noise.active) {
        apu->noise.length_counter = (apu->noise.length_counter + 1) % 2048;
        if (apu->noise.length_counter == 0) {
            apu->noise.length_counter = 0;
        }
    }
}

// Función de callback de audio para SDL (se llama cuando SDL necesita datos de audio)
void audio_callback(void* userdata, uint8_t* stream, int len) {
    apu_t* apu = (apu_t*)userdata;
    int16_t* buffer = (int16_t*)stream;

    for (int i = 0; i < len / sizeof(int16_t); i++) {
        int16_t sample = 0;

        // Asegúrate de agregar lógica de mezcla para combinar los canales
        if (apu->pulse1.active) {
            sample += (apu->pulse1.frequency & 0xFF); // Ejemplo simplificado para la onda cuadrada 1
        }

        if (apu->pulse2.active) {
            sample += (apu->pulse2.frequency & 0xFF); // Ejemplo simplificado para la onda cuadrada 2
        }

        if (apu->triangle.active) {
            sample += (apu->triangle.frequency & 0xFF); // Ejemplo simplificado para la onda triangular
        }

        if (apu->noise.active) {
            sample += (apu->noise.length_counter & 0xFF); // Ejemplo simplificado para el ruido
        }

        // Escalar el valor de la muestra para que esté en el rango adecuado
        buffer[i] = sample;
    }
}

// Inicializa la parte de SDL Audio
int init_audio(apu_t* apu) {
    // Inicializar SDL
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        printf("Error al inicializar SDL: %s\n", SDL_GetError());
        return -1;
    }

    // Configurar el formato de audio (monofónico, 16 bits, frecuencia de muestreo)
    SDL_AudioSpec desired_spec;
    SDL_zero(desired_spec);
    desired_spec.freq = SAMPLE_RATE;
    desired_spec.format = AUDIO_S16SYS;
    desired_spec.channels = 1;
    desired_spec.samples = 512;  // Tamaño del buffer de audio
    desired_spec.callback = audio_callback;
    desired_spec.userdata = apu;

    // Abrir el dispositivo de audio
    if (SDL_OpenAudioDevice(NULL, 0, &desired_spec, NULL, 0) == 0) {
        printf("Error al abrir el dispositivo de audio: %s\n", SDL_GetError());
        return -1;
    }

    // Iniciar el audio
    SDL_PauseAudioDevice(1, 0);  // Despausar el dispositivo de audio

    return 0;
}

// Detiene la parte de SDL Audio
void close_audio() {
    SDL_CloseAudioDevice(1);  // Cerrar el dispositivo de audio
    SDL_Quit();  // Limpiar SDL
}
