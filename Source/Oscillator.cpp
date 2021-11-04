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

    osc1Menu.addItem("Sine", 1);
    osc1Menu.addItem("Saw", 2);
    osc1Menu.addItem("Square", 3);
    osc1Menu.addItem("Triangle", 4);
    osc1Menu.addItem("Noise", 5);
    osc1Menu.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(&osc1Menu);
    
    osc1GainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    osc1GainSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 30, 20);
    osc1GainSlider.setRange(0.0f, 1.0f);
    osc1GainSlider.setValue(0.8f);
    osc1GainSlider.setNumDecimalPlacesToDisplay(2);
    addAndMakeVisible(&osc1GainSlider);

    osc1Choice = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.apvts, "osc1Type", osc1Menu);
    osc1GainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts,"osc1Gain", osc1GainSlider);
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

    g.drawText("OSC1", getX() + 50, getY() + 34, 100, 20, juce::Justification::centredTop);
    //g.drawText("Gain1", getX() + 140, getY() + 34, 100, 20, juce::Justification::centredTop);

    //g.drawText("OSC2", getX() + 50, getY() + 97, 100, 20, juce::Justification::centredTop);

    juce::Rectangle <float> area(25, 25, 150, 150);

    g.setColour(juce::Colours::yellow);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void Oscillator::resized()
{
    osc1Menu.setBounds(getX() + 50, getY() + 50, 100, 25);
    osc1GainSlider.setBounds(getX() + 50, getY() + 85, 100, 20);
    //osc2Menu.setBounds(getX() + 50, getY() + 115, 100, 25);

}
