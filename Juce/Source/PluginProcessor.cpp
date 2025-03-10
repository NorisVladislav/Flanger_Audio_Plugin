/*/
/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FlangerAudioProcessor::FlangerAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
    )
#endif
{
    UserParams[depth] = 2.0f;
    UserParams[mod_freq] = 0.3f;
    UserParams[bypass] = 0;
    UIUpdateFlag = true;
}

FlangerAudioProcessor::~FlangerAudioProcessor()
{
}

//==============================================================================
const juce::String FlangerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool FlangerAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool FlangerAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool FlangerAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double FlangerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int FlangerAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
    // so this should be at least 1, even if you're not really implementing programs.
}

int FlangerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void FlangerAudioProcessor::setCurrentProgram(int index)
{
}

const juce::String FlangerAudioProcessor::getProgramName(int index)
{
    return {};
}

void FlangerAudioProcessor::changeProgramName(int index, const juce::String& newName)
{
}

//==============================================================================
void FlangerAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void FlangerAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool FlangerAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    juce::ignoreUnused(layouts);
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


void FlangerAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    if (UserParams[bypass])
        return;

    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    auto numSamples = buffer.getNumSamples();

    // Clear - canale neutilizate
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, numSamples);

    // Parametrii
    const float blend = 0.7f;       
    const float feedforward = 0.7f;  
    const float feedback = 0.7f;     
	const float depthInSeconds = ((float)UserParams[depth] / 1000.0f);
	const float modFrequency = UserParams[mod_freq];

    // Transforma intarzierea in esantioane si calculeaza marimea buffer-ului
    const int depthInSamples = static_cast<int>(depthInSeconds * getSampleRate()) + 1;
    const int requiredBufferSize = std::max(depthInSamples, 1); // Marime minima 1

    // Se creează un vector delayBuffers pentru fiecare canal audio
    // Reseteaza buffer-ul daca dimensiunea nu este corecta
    if (delayBuffers.size() != totalNumInputChannels ||
        (delayBuffers.size() > 0 && delayBuffers[0].size() != requiredBufferSize))
    {
        delayBuffers.clear();
        for (auto i = 0; i < totalNumInputChannels; ++i)
        {
            delayBuffers.push_back(std::vector<float>(requiredBufferSize, 0.0f));
        }
        bufferIndices.resize(totalNumInputChannels, 0);

        // Reseteaza indexul
        for (auto& index : bufferIndices)
        {
            index = 0;
        }
    }

    // Procesare fiecare canal
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer(channel);
        auto& delayBuffer = delayBuffers[channel];
        auto& bufferIndex = bufferIndices[channel];

        for (int sample = 0; sample < numSamples; ++sample)
        {
            // Calculeaza timpul curent în secunde (nu în număr de eșantioane)
            const float time = static_cast<float>(currentPhase + sample) / getSampleRate();
            // Semnal sinusoidal care variaza între 0 și 1, variaza sinusoidal modFrequency pentru a obtine Flanger
            const float modSignal = (std::sin(2.0f * juce::MathConstants<float>::pi * modFrequency * time) + 1.0f) * 0.5f;

            // Calculeaza intarzierea curenta si o mentine intr-o limita de siguranta
            const int currentDelay = juce::jlimit(0,
                requiredBufferSize - 1,
                static_cast<int>(modSignal * depthInSamples));

            // Pozitia delay-ului in buffer
            int delayReadIndex = bufferIndex - currentDelay;
            if (delayReadIndex < 0)
                delayReadIndex += requiredBufferSize;

            // Safety check pentru limite 
            delayReadIndex = juce::jlimit(0, requiredBufferSize - 1, delayReadIndex);

            // Obtinere delayed sample
            const float delayedSample = delayBuffer[delayReadIndex];

            // Stocare input sample
            const float inputSample = channelData[sample];

            // Calculare output folosind formula Flanger-ului
            channelData[sample] = blend * inputSample + feedforward * delayedSample;

            // Update delay cu feedback
            delayBuffer[bufferIndex] = inputSample + feedback * delayedSample;

            // Incrementam si wrap around buffer - buffer circular
            bufferIndex = (bufferIndex + 1) % requiredBufferSize;
        }
    }

    // Update phase pentru urmatorul buffer
    currentPhase += numSamples;
}


//==============================================================================
bool FlangerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* FlangerAudioProcessor::createEditor()
{
    return new FlangerAudioProcessorEditor(this);
}

//==============================================================================
void FlangerAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    //Funcție folosită pentru a salva starea pluginului

    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    XmlElement root("Root");
    
    XmlElement* depthElement = root.createNewChildElement("Depth");
    depthElement->addTextElement(String(UserParams[depth], 3)); // Salvăm cu 3 zecimale

    XmlElement* modFreqElement = root.createNewChildElement("ModFreq");
    modFreqElement->addTextElement(String(UserParams[mod_freq], 3)); // Salvăm cu 3 zecimale

    copyXmlToBinary(root, destData);
}

void FlangerAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    //Funcție responsabilă pentru restaurarea parametrilor pluginului atunci când un proiect DAW este redeschis

    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    static std::unique_ptr<XmlElement> pRoot = getXmlFromBinary(data, sizeInBytes);

    if (pRoot != nullptr)
    {
        // Iterăm prin elementele XML
        forEachXmlChildElement((*pRoot), pChild)
        {
            if (pChild->hasTagName("Depth"))
            {
                String text = pChild->getAllSubText();
                UserParams[depth] = text.getFloatValue(); 
            }
            else if (pChild->hasTagName("ModFreq"))
            {
                String text = pChild->getAllSubText();
                UserParams[mod_freq] = text.getFloatValue();  
            }
        }
        UIUpdateFlag = true;
    }
}

int FlangerAudioProcessor::getNumParameters()
{
    return totalNumParam;
}

float FlangerAudioProcessor::getParameter(int index)
{
    switch (index)
    {
    case depth:
        return UserParams[depth];
        break;
    case mod_freq:
        return UserParams[mod_freq];
        break;
	case bypass:
		return UserParams[bypass];
		break;
    default:
        return 0.0f;
    }
}

void FlangerAudioProcessor::setParameter(int index, float newValue)
{
    switch (index)
    {
    case depth:
        UserParams[depth] = newValue;
        break;
    case mod_freq:
        UserParams[mod_freq] = newValue;
        break;
	case bypass:
		UserParams[bypass] = newValue;
		break;
    default: return;
    }

    UIUpdateFlag = true;
}

const String FlangerAudioProcessor::getParameterName(int index)
{
    switch (index)
    {
    case depth:
        return "Depth";
        break;
    case mod_freq:
        return "Modulation Frequency";
        break;
	case bypass:
		return "Bypass";
    default:
        return String();
    }
}

const String FlangerAudioProcessor::getParameterText(int index)
{
    if (index >= 0 && index < totalNumParam)
        return String(UserParams[index]);
    else return String();
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FlangerAudioProcessor();
}
