/*
  ==============================================================================

    Filter.h
    Created: 5 Nov 2021 2:21:34am
    Author:  User

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class Filter  : public juce::Component
{
public:
    Filter();
    ~Filter() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Filter)
};
