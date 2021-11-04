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

class SynthVoice : public juce::SynthesiserVoice 
{                                                
public: 
    // ===========================================
    bool canPlaySound(juce::SynthesiserSound* sound) override {
        return dynamic_cast<SynthSound*> (sound) != nullptr;
    }
    // ===========================================
    void getOscParams(std::atomic<float>* selection1, std::atomic<float>* level1,
        std::atomic<float>* selection2, std::atomic<float>* level2, std::atomic<float>* oct2) {
        osc1Wave = *selection1;
        osc1level = *level1;
        osc2Wave = *selection2;
        osc2level = *level2;
        octIdx = *oct2;
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
        default:
            sample1 = osc1.sinewave(frequency);
            break;
        }

        switch (osc2Wave) {
        case 0:
            sample2 = osc2.sinewave(frequency * octShiftFreq[octIdx+2]);
            break;
        case 1:
            sample2 = osc2.saw(frequency * octShiftFreq[octIdx+2]);
            break;
        case 2:
            sample2 = osc2.square(frequency * octShiftFreq[octIdx+2]);
            break;
        case 3:
            sample2 = osc2.triangle(frequency * octShiftFreq[octIdx+2]);
            break;
        case 4:
            sample2 = osc2.noise();
            break;
        default:
            sample2 = osc2.sinewave(frequency * octShiftFreq[octIdx+2]);
            break;
        }
        return (sample1 * osc1level + sample2 * osc2level) / 2;
    }
    // ===========================================
    void getEnvelopeParams(std::atomic<float>* attack, std::atomic<float>* decay, std::atomic<float>* sustain, std::atomic<float>* release) {
        env1.setAttack(*attack);
        env1.setDecay(*decay);
        env1.setSustain(*sustain);
        env1.setRelease(*release);
    }
    // ===========================================
    double setEnvelope() {
        return env1.adsr(setOscType(), env1.trigger);
    }
    // ===========================================
    //double setFilter() {

    //    // return filter.setType(::lopass) // do this for each case
    //}
    // ===========================================
    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override {
        env1.trigger = 1;
        level = velocity;
        frequency = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    }
    // ===========================================
    void stopNote(float velocity, bool allowTailOff) {
        env1.trigger = 0;
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
                outputBuffer.addSample(channel, startSample, setEnvelope());
            }
            ++startSample;
        }
    }
private:
    double frequency, level;        // used in setOscType(), defined in startNote()
    double sample1, sample2;        // used in setOscType()
    int osc1Wave, osc2Wave;         // used in getOscParameters()
    double osc1level, osc2level;    // used in getOscParameters()
    int octIdx;                     // used in getOscParameters()

    float octShiftFreq[5] = { 0.25, 0.5, 1, 2, 4 };
    
    //juce::dsp::StateVariableTPTFilter<double> filter;
    maxiOsc osc1, osc2;
    maxiEnv env1;
    
};