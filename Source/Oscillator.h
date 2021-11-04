/*
  ==============================================================================

    Oscillator.h
    Created: 4 Nov 2021 11:48:47am
    Author:  User

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Oscillator  : public juce::Component
{
public:
    Oscillator(PipoSynth02AudioProcessor&);
    ~Oscillator() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::ComboBox osc1Menu;
    juce::Slider osc1GainSlider;

    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> osc1Choice;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> osc1GainAttachment;

    PipoSynth02AudioProcessor& audioProcessor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscillator)
};
