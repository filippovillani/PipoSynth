/*
  ==============================================================================

    PipoFilters.h
    Created: 10 Nov 2021 4:29:20pm
    Author:  Filippo Villani

  ==============================================================================
*/

#pragma once

#include <math.h>

#ifndef PI
#define PI  3.1415926535897932384626433832795
#endif
#define TWOPI 6.283185307179586476925286766559

//class pipoSettings {
//public:
//    static int sampleRate;
//    static int channels;
//    static int bufferSize;
//    static void setup(int initSampleRate, int initNumChannels, int initBufferSize) {
//        pipoSettings::sampleRate = initBufferSize;
//        pipoSettings::channels = initNumChannels;
//        pipoSettings::bufferSize = initBufferSize;
//    }
//};

class pipoFilter {
public:
    float sampleRate;

    double LPF1ord(double input, float cutoff);
    double HPF1ord(double input, float cutoff);
    double LPF2ord(double input, float cutoff, float Q);
    double HPF2ord(double input, float cutoff, float Q);
    double BPF2ord(double input, float cutoff, float Q);


private:
    double inputs[3] = { 0 };
    double outputs[3] = { 0 };

    double output;

    float theta;
    double argtan;
    float gamma, d, beta;

    float a0, a1, a2;
    float b1, b2;



};