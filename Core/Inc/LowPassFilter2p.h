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

int apply(const int sample, DigitalBiquadFilter *Filter);
void reset(int value, DigitalBiquadFilter *Filter);
void compute_params(float sample_freq, float cutoff_freq, biquad_params *ret);
void LowPassFilterinit(DigitalBiquadFilter *Filter, float sample_freq,float cutoff_freq);

#endif //__LOWPASSFILTER_H