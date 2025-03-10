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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "PluginEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
FlangerAudioProcessorEditor::FlangerAudioProcessorEditor (FlangerAudioProcessor* ownerFilter)
    : AudioProcessorEditor(ownerFilter)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    flangerSlider.reset (new juce::Slider ("Flager Slider"));
    addAndMakeVisible (flangerSlider.get());
    flangerSlider->setRange (0, 2, 0.1);
    flangerSlider->setSliderStyle (juce::Slider::LinearHorizontal);
    flangerSlider->setTextBoxStyle (juce::Slider::TextBoxLeft, false, 40, 20);
    flangerSlider->addListener (this);

    flangerSlider->setBounds (184, 128, 198, 24);

    flangerSlider2.reset (new juce::Slider ("Flanger Slider"));
    addAndMakeVisible (flangerSlider2.get());
    flangerSlider2->setRange (0, 1, 0.1);
    flangerSlider2->setSliderStyle (juce::Slider::IncDecButtons);
    flangerSlider2->setTextBoxStyle (juce::Slider::TextBoxLeft, false, 60, 20);
    flangerSlider2->addListener (this);

    flangerSlider2->setBounds (184, 168, 190, 24);

    flangerLabel.reset (new juce::Label ("Flanger Label",
                                         TRANS ("Depth (ms)")));
    addAndMakeVisible (flangerLabel.get());
    flangerLabel->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    flangerLabel->setJustificationType (juce::Justification::centredLeft);
    flangerLabel->setEditable (false, false, false);
    flangerLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    flangerLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    flangerLabel->setBounds (24, 128, 150, 24);

    flangerLabel2.reset (new juce::Label ("Flanger Label",
                                          TRANS ("Mod frequency (Hz)")));
    addAndMakeVisible (flangerLabel2.get());
    flangerLabel2->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    flangerLabel2->setJustificationType (juce::Justification::centredLeft);
    flangerLabel2->setEditable (false, false, false);
    flangerLabel2->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    flangerLabel2->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    flangerLabel2->setBounds (24, 168, 150, 24);

    flangerTextButton.reset (new juce::TextButton ("Flanger Text Button"));
    addAndMakeVisible (flangerTextButton.get());
    flangerTextButton->setButtonText (TRANS ("Bypass"));
    flangerTextButton->addListener (this);

    flangerTextButton->setBounds (240, 24, 142, 32);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (400, 200);


    //[Constructor] You can add your own custom stuff here..

    getProcessor()->RequestUIUpdate();
    startTimer(200);

    //[/Constructor]
}

FlangerAudioProcessorEditor::~FlangerAudioProcessorEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    flangerSlider = nullptr;
    flangerSlider2 = nullptr;
    flangerLabel = nullptr;
    flangerLabel2 = nullptr;
    flangerTextButton = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void FlangerAudioProcessorEditor::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (juce::Colour (0xff09690e));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void FlangerAudioProcessorEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void FlangerAudioProcessorEditor::sliderValueChanged (juce::Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == flangerSlider.get())
    {
        //[UserSliderCode_flangerSlider] -- add your slider handling code here..
        //[/UserSliderCode_flangerSlider]
    }
    else if (sliderThatWasMoved == flangerSlider2.get())
    {
        //[UserSliderCode_flangerSlider2] -- add your slider handling code here..
        //[/UserSliderCode_flangerSlider2]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void FlangerAudioProcessorEditor::buttonClicked (juce::Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == flangerTextButton.get())
    {
        //[UserButtonCode_flangerTextButton] -- add your button handler code here..
        //[/UserButtonCode_flangerTextButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...


void FlangerAudioProcessorEditor::timerCallback()
{
    FlangerAudioProcessor* ourProcessor = getProcessor();

    // Verifică dacă există o actualizare necesară pentru UI
    if (ourProcessor->NeedsUIUpdate())
    {
        // Obține valoarea parametrului depth (normalizat între 0 și 1)
        float depth = ourProcessor->getParameter(FlangerAudioProcessor::depth);

        // Obține valoarea parametrului mod_freq (normalizat între 0 și 1)
        float mod_freq = ourProcessor->getParameter(FlangerAudioProcessor::mod_freq);

        // Actualizează slider-ul cu valoarea parametrului depth
        flangerSlider2->setValue(mod_freq, juce::dontSendNotification);

        // Actualizează slider-ul cu valoarea parametrului mod_freq
        flangerSlider->setValue(depth, juce::dontSendNotification);

        // Șterge indicatorul că UI trebuie să fie actualizat
        ourProcessor->ClearUIUpdateFlag();
    }
}



//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="FlangerAudioProcessorEditor"
                 componentName="" parentClasses="public AudioProcessorEditor, public Timer"
                 constructorParams="FlangerAudioProcessor* ownerFilter" variableInitialisers="AudioProcessorEditor(ownerFilter)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="400" initialHeight="200">
  <BACKGROUND backgroundColour="ff09690e"/>
  <SLIDER name="Flager Slider" id="b549009e9e856438" memberName="flangerSlider"
          virtualName="" explicitFocusOrder="0" pos="184 128 198 24" min="0.0"
          max="2.0" int="0.1" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="40" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="Flanger Slider" id="b7a17ab3ff5bfe25" memberName="flangerSlider2"
          virtualName="" explicitFocusOrder="0" pos="184 168 190 24" min="0.0"
          max="1.0" int="0.1" style="IncDecButtons" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="60" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="Flanger Label" id="24fbf8a1771bb806" memberName="flangerLabel"
         virtualName="" explicitFocusOrder="0" pos="24 128 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Depth (ms)" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="Flanger Label" id="cf1ab64b44ab8d81" memberName="flangerLabel2"
         virtualName="" explicitFocusOrder="0" pos="24 168 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Mod frequency (Hz)" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="Flanger Text Button" id="be15c5b8239cac53" memberName="flangerTextButton"
              virtualName="" explicitFocusOrder="0" pos="240 24 142 32" buttonText="Bypass"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

