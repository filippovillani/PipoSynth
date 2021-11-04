/*
  ==============================================================================

    Envelope.h
    Created: 4 Nov 2021 4:46:46pm
    Author:  User

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Envelope  : public juce::Component
{
public:
    Envelope(PipoSynth02AudioProcessor&);
    ~Envelope() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider
        attackSlider,
        decaySlider,
        sustainSlider,
        releaseSlider;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> 
        attackAttachment,
        decayAttachment,
        sustainAttachment,
        releaseAttachment;

    PipoSynth02AudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Envelope)
};
