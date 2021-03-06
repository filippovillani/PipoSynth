/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Oscillator.h"
#include "Envelope.h"
#include "Filter.h"
#include "OtherStuff.h"

//==============================================================================
/**
*/
class PipoSynth02AudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    PipoSynth02AudioProcessorEditor (PipoSynth02AudioProcessor&);
    ~PipoSynth02AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    PipoSynth02AudioProcessor& audioProcessor;

    Oscillator oscGUI;
    Envelope envGUI;
    Filter filterGUI;
    OtherStuff mainGUI;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PipoSynth02AudioProcessorEditor)
};
