/*
  ==============================================================================

    SynthVoice.h
    Created: 3 Nov 2021 11:34:52pm
    Author:  User

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "SynthSound.h"
#include "maximilian.h"

class SynthVoice : public juce::SynthesiserVoice // SynthVoice is a derived class. You won't use virtual funcs and you should 
{                                                // put override to virtual functions. Use virtual in base class
public: 
    // ===========================================
    bool canPlaySound(juce::SynthesiserSound* sound) override {
        return dynamic_cast<SynthSound*> (sound) != nullptr;
    }
    // ===========================================
    void getOscParams(std::atomic<float>* selection1, std::atomic<float>* level1) {
        osc1Wave = *selection1;
        osc1level = *level1;
    }
    // ===========================================

    double setOscType() {
        switch (osc1Wave) {
        case 0:
            sample1 = osc1.sinewave(frequency);
            break;
        case 1:
            sample1 = osc1.saw(frequency);
            break;
        case 2:
            sample1 = osc1.square(frequency);
            break;
        case 3:
            sample1 = osc1.triangle(frequency);
            break;
        case 4:
            sample1 = osc1.noise();
            break;
        default:
            sample1 = osc1.sinewave(frequency);
            break;
        }
        return sample1 * osc1level;
    }
    // ===========================================
    //double setFilter() {

    //    // return filter.setType(::lopass) // do this for each case
    //}
    // ===========================================
    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override {
        // env1.trigger = 1;
        level = velocity;
        frequency = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    }
    // ===========================================
    void stopNote(float velocity, bool allowTailOff) {
        // env1.trigger = 0;
        allowTailOff = true;
        if (velocity == 0) {
            SynthesiserVoice::clearCurrentNote();
        }
    }
    // ============================================
    void pitchWheelMoved(int newPitchWheelValue) {

    }
    // =============================================
    void controllerMoved(int controllerNumber, int newControllerValue) {

    }
    // ===========================================
    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override {
        for (int sample = 0; sample < numSamples; ++sample) {
            for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel) {
                outputBuffer.addSample(channel, startSample, setOscType());
            }
            ++startSample;
        }
    }
private:
    double frequency, level;   // used in setOscType(), defined in startNote()
    double sample1;     // used in setOscType()
    int osc1Wave;       // used in getOscParameters()
    double osc1level;   // used in getOscParameters()
    
    //juce::dsp::StateVariableTPTFilter<double> filter;
    maxiOsc osc1;

};