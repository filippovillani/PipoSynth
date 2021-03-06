/*
  ==============================================================================

    Oscillator.cpp
    Created: 4 Nov 2021 11:48:47am
    Author:  User

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Oscillator.h"

//==============================================================================
Oscillator::Oscillator(PipoSynth02AudioProcessor& p) :
    audioProcessor(p)
{
    setSize(200, 200);
    // OSC 1
    osc1Menu.addItem("Sine", 1);
    osc1Menu.addItem("Saw", 2);
    osc1Menu.addItem("Square", 3);
    osc1Menu.addItem("Triangle", 4);
    osc1Menu.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(&osc1Menu);
    
    osc1GainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    osc1GainSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 30, 18);
    osc1GainSlider.setRange(0.0f, 1.0f);
    osc1GainSlider.setValue(0.8f);
    osc1GainSlider.setNumDecimalPlacesToDisplay(2);
    addAndMakeVisible(&osc1GainSlider);

    // OSC 2
    osc2Menu.addItem("Sine", 1);
    osc2Menu.addItem("Saw", 2);
    osc2Menu.addItem("Square", 3);
    osc2Menu.addItem("Triangle", 4);
    osc2Menu.addItem("Noise", 5);
    osc2Menu.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(&osc2Menu);

    osc2GainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    osc2GainSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 30, 18);
    osc2GainSlider.setRange(0.0f, 1.0f);
    osc2GainSlider.setValue(0.8f);
    osc2GainSlider.setNumDecimalPlacesToDisplay(2);
    addAndMakeVisible(&osc2GainSlider);

    octShiftSlider.setSliderStyle(juce::Slider::SliderStyle::IncDecButtons);
    octShiftSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 38, 25);
    octShiftSlider.setTextValueSuffix(" oct");
    octShiftSlider.setRange(-2, 2, 1);
    octShiftSlider.setValue(0);
    addAndMakeVisible(&octShiftSlider);

    // Attachments
    osc1Choice = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.apvts, "osc1Type", osc1Menu);
    osc1GainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts,"osc1Gain", osc1GainSlider);
    osc2Choice = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.apvts, "osc2Type", osc2Menu);
    osc2GainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts,"osc2Gain", osc2GainSlider);
    octShiftAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "oct2", octShiftSlider);
}

Oscillator::~Oscillator()
{
}

void Oscillator::paint (juce::Graphics& g)
{
    juce::Rectangle<int> titleArea(0, 10, getWidth(), 20);

    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.drawText("Oscillators", titleArea, juce::Justification::centredTop);

    g.drawText("OSC1", 50, 32, 100, 20, juce::Justification::centredTop);
    g.drawText("OSC2", 50, 105, 100, 20, juce::Justification::centredTop);

    juce::Rectangle <float> area(25, 25, 175, 150);

    g.setColour(juce::Colours::yellow);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void Oscillator::resized()
{
    osc1Menu.setBounds(50, 48, 100, 22);
    osc1GainSlider.setBounds(50, 75, 100, 20);
    osc2Menu.setBounds(50, 121, 100, 22);
    osc2GainSlider.setBounds(50, 151, 100, 20);
    octShiftSlider.setBounds(157, 125, 40, 30);
}
