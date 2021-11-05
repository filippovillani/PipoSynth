/*
  ==============================================================================

    Filter.h
    Created: 4 Nov 2021 10:03:51pm
    Author:  User

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Filter : public juce::Component
{
public:
    Filter(PipoSynth02AudioProcessor&);
    ~Filter() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    juce::ComboBox filterMenu;
    juce::Slider cutoffSlider, resonanceSlider;
    juce::ToggleButton bypassButton;

    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> filterChoice;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> cutoffAttachment, resonanceAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> bypassAttachment;

    PipoSynth02AudioProcessor& audioProcessor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Filter)
};
