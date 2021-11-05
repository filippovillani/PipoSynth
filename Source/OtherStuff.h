/*
  ==============================================================================

    OtherStuff.h
    Created: 5 Nov 2021 12:36:02pm
    Author:  User

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class OtherStuff  : public juce::Component
{
public:
    OtherStuff(PipoSynth02AudioProcessor&);
    ~OtherStuff() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider masterSlider;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> masterAttachment;

    PipoSynth02AudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OtherStuff)
};
