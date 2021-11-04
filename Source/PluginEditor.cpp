/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PipoSynth02AudioProcessorEditor::PipoSynth02AudioProcessorEditor (PipoSynth02AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), oscGUI(p)
{
    setSize (400, 200);
    addAndMakeVisible(&oscGUI);
}

PipoSynth02AudioProcessorEditor::~PipoSynth02AudioProcessorEditor()
{
}

//==============================================================================
void PipoSynth02AudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}

void PipoSynth02AudioProcessorEditor::resized()
{
    juce::Rectangle<int> area = getLocalBounds();

    const int componentWidth = 200;
    const int componentHeight = 200;

    oscGUI.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
}
