/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PipoSynth02AudioProcessor::PipoSynth02AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), apvts(*this,nullptr,"Parameters",createParameters())
#endif
{
    mySynth.clearVoices();
    for (int i = 0; i < 5; i++) {
        mySynth.addVoice(new SynthVoice());
    }
    mySynth.clearSounds();
    mySynth.addSound(new SynthSound());
}

PipoSynth02AudioProcessor::~PipoSynth02AudioProcessor()
{
}

//==============================================================================
const juce::String PipoSynth02AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool PipoSynth02AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool PipoSynth02AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool PipoSynth02AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double PipoSynth02AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int PipoSynth02AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int PipoSynth02AudioProcessor::getCurrentProgram()
{
    return 0;
}

void PipoSynth02AudioProcessor::setCurrentProgram (int index)
{
}

const juce::String PipoSynth02AudioProcessor::getProgramName (int index)
{
    return {};
}

void PipoSynth02AudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void PipoSynth02AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    juce::ignoreUnused(samplesPerBlock);
    lastSampleRate = sampleRate;
    mySynth.setCurrentPlaybackSampleRate(lastSampleRate);
}

void PipoSynth02AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool PipoSynth02AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void PipoSynth02AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    for (int i = 0; i < mySynth.getNumVoices(); i++) {
        //if myVoice sucessfully casts as a SynthVoice*, get the voice and set the params
        if ((myVoice = dynamic_cast<SynthVoice*>(mySynth.getVoice(i)))) {
            
            myVoice->getOscParams(
                apvts.getRawParameterValue("osc1Type"),
                apvts.getRawParameterValue("osc1Gain"),
                apvts.getRawParameterValue("osc2Type"),
                apvts.getRawParameterValue("osc2Gain"),
                apvts.getRawParameterValue("oct2"));
            
            myVoice->getEnvelopeParams(
                apvts.getRawParameterValue("attack"),
                apvts.getRawParameterValue("decay"),
                apvts.getRawParameterValue("sustain"),
                apvts.getRawParameterValue("release"));

            myVoice->getFilterParams(
                apvts.getRawParameterValue("filterType"),
                apvts.getRawParameterValue("cutoff"),
                apvts.getRawParameterValue("resonance"),
                apvts.getRawParameterValue("filterBypass"));
        }
    }

    buffer.clear();
    mySynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
  
}

//==============================================================================
bool PipoSynth02AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* PipoSynth02AudioProcessor::createEditor()
{
    return new PipoSynth02AudioProcessorEditor (*this);
}

//==============================================================================
void PipoSynth02AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void PipoSynth02AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PipoSynth02AudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout
PipoSynth02AudioProcessor::createParameters() {
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    // Oscillator's parameters
    params.push_back(std::make_unique<juce::AudioParameterChoice>("osc1Type", "Osc1 Type", juce::StringArray("Sine", "Saw", "Square","Triangle"), 0));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("osc1Gain", "Osc1 Gain", juce::NormalisableRange<float>(0.f, 1.f, 0.01f), 0.8f));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("osc2Type", "Osc2 Type", juce::StringArray("Sine", "Saw", "Square", "Triangle", "Noise"), 0));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("osc2Gain", "Osc2 Gain", juce::NormalisableRange<float>(0.f, 1.f, 0.01f), 0.8f));
    params.push_back(std::make_unique<juce::AudioParameterInt>("oct2", "Octave Shift", -2, 2, 0));
    // Envelope's parameters
    params.push_back(std::make_unique<juce::AudioParameterFloat>("attack", "Attack", juce::NormalisableRange<float>(0.1f, 5000.f, 0.1f), 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("decay", "Decay", juce::NormalisableRange<float>(0.1f, 5000.f, 0.1f), 1.f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("sustain", "Sustain", juce::NormalisableRange<float>(0.f, 1.f, 0.1f), 0.8f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("release", "Release", juce::NormalisableRange<float>(0.5f, 5000.f, 0.1f), 0.5f));
    // Filter's parameters
    params.push_back(std::make_unique<juce::AudioParameterChoice>("filterType", "Filter Type", juce::StringArray("LPF", "BPF", "HPF"), 0));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("cutoff", "CutOff", juce::NormalisableRange<float>(0.1f, 5000.f, 0.1f), 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("resonance", "Q", juce::NormalisableRange<float>(0.1f, 10.f, 0.1f), 0.707f));
    params.push_back(std::make_unique<juce::AudioParameterBool>("filterBypass", "Filter Bypass", true));

    return { params.begin(), params.end() };
}