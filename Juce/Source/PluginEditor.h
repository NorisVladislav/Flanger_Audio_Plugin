/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 7.0.12

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include <JuceHeader.h>
#include "PluginProcessor.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class FlangerAudioProcessorEditor  : public AudioProcessorEditor,
                                     public Timer,
                                     public juce::Slider::Listener,
                                     public juce::Button::Listener
{
public:
    //==============================================================================
    FlangerAudioProcessorEditor (FlangerAudioProcessor* ownerFilter);
    ~FlangerAudioProcessorEditor() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void timerCallback();
    FlangerAudioProcessor* getProcessor() const
    {
        return static_cast <FlangerAudioProcessor*>(getAudioProcessor());
    }

    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;
    void sliderValueChanged (juce::Slider* sliderThatWasMoved) override;
    void buttonClicked (juce::Button* buttonThatWasClicked) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::Slider> flangerSlider;
    std::unique_ptr<juce::Slider> flangerSlider2;
    std::unique_ptr<juce::Label> flangerLabel;
    std::unique_ptr<juce::Label> flangerLabel2;
    std::unique_ptr<juce::TextButton> flangerTextButton;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FlangerAudioProcessorEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

