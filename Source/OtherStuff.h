/*
  ==============================================================================

    OtherStuff.h
    Created: 5 Nov 2021 12:36:02pm
    Author:  User

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class OtherStuff  : public juce::Component
{
public:
    OtherStuff();
    ~OtherStuff() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OtherStuff)
};
