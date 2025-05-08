#ifndef APU_H
#define APU_H

#include <stdint.h>
#include <stdbool.h>  // Para usar bool, true y false

// Definición de los canales de la APU
typedef struct {
    uint8_t duty_cycle;     // Ciclo de trabajo de la onda cuadrada
    uint8_t envelope;       // Envolvente
    uint8_t sweep;          // Barrido
    uint16_t frequency;     // Frecuencia de la onda
    uint8_t length_counter; // Contador de longitud
    bool active;            // Si el canal está activo
} square_channel_t;

typedef struct {
    uint16_t frequency;     // Frecuencia de la onda triangular
    uint8_t length_counter; // Contador de longitud
    bool active;            // Si el canal está activo
} triangle_channel_t;

typedef struct {
    uint8_t period;         // Periodo del ruido
    uint8_t length_counter; // Contador de longitud
    bool active;            // Si el canal está activo
} noise_channel_t;

typedef struct {
    square_channel_t pulse1;  // Canal de onda cuadrada 1
    square_channel_t pulse2;  // Canal de onda cuadrada 2
    triangle_channel_t triangle; // Canal de onda triangular
    noise_channel_t noise;      // Canal de ruido
} apu_t;

extern apu_t apu; // APU global variable
// Función para inicializar la APU
void init_apu(apu_t* apu);

// Función de callback para la salida de audio
void audio_callback(void* userdata, uint8_t* stream, int len);

// Función para actualizar el estado de la APU
void update_apu(apu_t* apu);

#endif // APU_H
