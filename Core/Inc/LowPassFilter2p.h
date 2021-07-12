#ifndef __LOWPASSFILTER2P_H
#define __LOWPASSFILTER2P_H

#include "math.h"

static inline is_zero(const float fVal1)
{
    return (fabsf(fVal1) < __FLT_EPSILON__);
}

typedef struct
{
    float cutoff_freq;
    float sample_freq;
    float a1;
    float a2;
    float b0;
    float b1;
    float b2;
} biquad_params;

typedef struct
{
    biquad_params params;
    int delay_element_1;
    int delay_element_2;
    int initialized;
} DigitalBiquadFilter;

int LPF2p_apply(const int sample, DigitalBiquadFilter *Filter);
void LPF2p_reset(int value, DigitalBiquadFilter *Filter);
void LPF2p_init(DigitalBiquadFilter *Filter, float sample_freq, float cutoff_freq);

#endif //__LOWPASSFILTER_H