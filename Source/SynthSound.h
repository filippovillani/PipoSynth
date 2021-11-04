/*
  ==============================================================================

    SynthSound.h
    Created: 3 Nov 2021 11:35:01pm
    Author:  User

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class SynthSound : public juce::SynthesiserSound
{
public:
    bool appliesToNote(int midiNoteNumber) {
        return true;
    }
    bool appliesToChannel(int midiChannel) {
        return true;
    }

};

