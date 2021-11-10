/*
  ==============================================================================

    PipoFilters.cpp
    Created: 10 Nov 2021 4:29:14pm
    Author:  User

  ==============================================================================
*/

#include "PipoFilters.h"

double pipoFilter::LPF1ord(double input, float cutoff) {
   
    inputs[1] = inputs[0];
    inputs[0] = input;
    theta = TWOPI * cutoff / sampleRate;
    gamma = cos(theta) / (1.f + sin(theta));
    // Coefficients
    a0 = (1.f - gamma) / 2.f;
    a1 = a0;
    b1 = -gamma;
    // Finite difference equation
    output = a0 * inputs[0] + a1 * inputs[1] - b1 * outputs[1];
    // Update delay line
    outputs[1] = output;
    return output;
}

double pipoFilter::HPF1ord(double input, float cutoff) {
   
    inputs[1] = inputs[0];
    inputs[0] = input;
    theta = TWOPI * cutoff / sampleRate;
    gamma = cos(theta) / (1.f + sin(theta));
    // Coefficients
    a0 = (1.f + gamma) / 2.f;
    a1 = -(1.f - gamma) / 2.f;
    b1 = -gamma;
    // Finite difference equation
    output = a0 * inputs[0] + a1 * inputs[1] - b1 * outputs[1];
    // Update delay line
    outputs[1] = output;
    return output;
}

