#pragma once
#include<stdint.h>

// initializes the encoder subsystem
void Encoder_init(void);

// samples the encoders, saving the respective values in a temporary storage
void Encoder_sample(void);

// returns the number of the encoder 
uint8_t Encoder_numEncoders(void);

// returns the value of an encoder, when sampled with the Encoder_sample();
uint16_t Encoder_getValue(uint8_t num_encoder);
