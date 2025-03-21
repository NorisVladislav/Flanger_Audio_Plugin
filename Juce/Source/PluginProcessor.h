/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
  */

#pragma once

#include <JuceHeader.h>

//==============================================================================


class FlangerAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    FlangerAudioProcessor();
    ~FlangerAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    int getNumParameters() override;
    float getParameter(int index) override;
    void setParameter(int index, float newValue) override;
    const String getParameterName(int index) override;
    const String getParameterText(int index) override;
    enum Parameters { depth = 0, mod_freq, bypass, totalNumParam };
    bool NeedsUIUpdate() { return UIUpdateFlag; };
    void RequestUIUpdate() { UIUpdateFlag = true; };
    void ClearUIUpdateFlag() { UIUpdateFlag = false; };

private:
    std::vector<std::vector<float>> delayBuffers;
    std::vector<int> bufferIndices;
    int64_t currentPhase = 0;

    float UserParams[totalNumParam];
    bool UIUpdateFlag; //Valoare booleana pentru reimprospatarea interfetei grafice
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FlangerAudioProcessor)
};




/*

*/