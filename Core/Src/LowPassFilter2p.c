#include "LowPassFilter2p.h"

int LPF2p_apply(const int sample, DigitalBiquadFilter *Filter)
{
    if (is_zero(Filter->params.cutoff_freq) || is_zero(Filter->params.sample_freq))
    {
        return sample;
    }
    if (!(Filter->initialized))
    {
        LPF2p_reset(sample, Filter);
    }
    int delay_element_0 = sample - Filter->delay_element_1 * Filter->params.a1 - Filter->delay_element_2 * Filter->params.a2;
    int output = delay_element_0 * Filter->params.b0 + Filter->delay_element_1 * Filter->params.b1 + Filter->delay_element_2 * Filter->params.b2;

    Filter->delay_element_2 = Filter->delay_element_1;
    Filter->delay_element_1 = delay_element_0;

    
    return output;
}

void LPF2p_reset(int value, DigitalBiquadFilter *Filter)
{
    Filter->delay_element_1 = value * (1.0f / (1 + Filter->params.a1 + Filter->params.a2));
    Filter->delay_element_2 = value * (1.0f / (1 + Filter->params.a1 + Filter->params.a2));
    Filter->initialized = 1;
}

static void compute_params(float sample_freq, float cutoff_freq, biquad_params *ret)
{
    ret->cutoff_freq = cutoff_freq;
    ret->sample_freq = sample_freq;

    float fr = sample_freq / cutoff_freq;
    float ohm = tanf(M_PI / fr);
    float c = 1.0f + 2.0f * cosf(M_PI / 4.0f) * ohm + ohm * ohm;

    ret->b0 = ohm * ohm / c;
    ret->b1 = 2.0f * ret->b0;
    ret->b1 = ret->b0;
    ret->a1 = 2.0f * (ohm * ohm - 1.0f) / c;
    ret->a2 = (1.0f - 2.0f * cosf(M_PI / 4.0f) * ohm + ohm * ohm) / c;
}

void LPF2p_init(DigitalBiquadFilter *Filter, float sample_freq, float cutoff_freq)
{
    compute_params(sample_freq, cutoff_freq, &(Filter->params));
}