/*
  ==============================================================================

    Envelope.cpp
    Created: 4 Nov 2021 4:46:47pm
    Author:  User

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Envelope.h"

//==============================================================================
Envelope::Envelope(PipoSynth02AudioProcessor& p) : audioProcessor(p)
{
    setSize(200, 200);
    attackSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    attackSlider.setRange(0.1f, 5000.f);
    attackSlider.setValue(0.1f);
    attackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 60.0, 20.0);
    attackSlider.setTextValueSuffix(" Hz");
    addAndMakeVisible(&attackSlider);

    releaseSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    releaseSlider.setRange(0.3f, 5000.f);
    releaseSlider.setValue(0.3f);
    releaseSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 60.0, 20.0);
    releaseSlider.setTextValueSuffix(" Hz");
    addAndMakeVisible(&releaseSlider);

    sustainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    sustainSlider.setRange(0.0f, 1.0f);
    sustainSlider.setValue(0.8f);
    sustainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 60.0, 20.0);
    sustainSlider.setTextValueSuffix(" Hz");
    addAndMakeVisible(&sustainSlider);

    decaySlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    decaySlider.setRange(0.1f, 5000.f);
    decaySlider.setValue(1.f);
    decaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 60.0, 20.0);
    decaySlider.setTextValueSuffix(" Hz");
    addAndMakeVisible(&decaySlider);

    attackAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "attack", attackSlider);
    decayAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "decay", decaySlider);
    sustainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "sustain", sustainSlider);
    releaseAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "release", releaseSlider);

}

Envelope::~Envelope()
{
}

void Envelope::paint (juce::Graphics& g)
{
    juce::Rectangle<int> titleArea(0, 10, getWidth(), 20);

    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.drawText("Envelope", titleArea, juce::Justification::centredTop);

    g.drawText("A", 53, 150, 20, 20, juce::Justification::centredTop);
    g.drawText("D", 77, 150, 20, 20, juce::Justification::centredTop);
    g.drawText("S", 103, 150, 20, 20, juce::Justification::centredTop);
    g.drawText("R", 128, 150, 20, 20, juce::Justification::centredTop);

    g.setColour(juce::Colours::yellow);
    g.drawRoundedRectangle(25, 25, 150, 150, 20.f, 2.f);
}

void Envelope::resized()
{
    juce::Rectangle<int> area = getLocalBounds().reduced(50);

    int sliderWidth = 25;
    int sliderHeight = 175;

    attackSlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
    releaseSlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
    sustainSlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
    decaySlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
}
