#include "PluginProcessor.h"
#include "PluginEditor.h"

ThaiCompressorVSTAudioProcessor::ThaiCompressorVSTAudioProcessor()
    : AudioProcessor(BusesProperties()
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
        .withOutput("Output", juce::AudioChannelSet::stereo(), true))
{
}

ThaiCompressorVSTAudioProcessor::~ThaiCompressorVSTAudioProcessor()
{
}

void ThaiCompressorVSTAudioProcessor::prepareToPlay(double newSampleRate, int samplesPerBlock)
{
    sampleRate = newSampleRate;
}

void ThaiCompressorVSTAudioProcessor::releaseResources()
{
}

bool ThaiCompressorVSTAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;

    return true;
}

void ThaiCompressorVSTAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    // Apply gain
    float gainLinear = juce::Decibels::decibelsToGain(gain);
    buffer.applyGain(gainLinear);

    // Simple compressor: reduce peaks
    if (peakReduction > 0.0f)
    {
        float threshold = juce::Decibels::decibelsToGain(-20.0f + peakReduction);
        
        for (int channel = 0; channel < totalNumInputChannels; ++channel)
        {
            auto* channelData = buffer.getWritePointer(channel);
            for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
            {
                float absValue = std::abs(channelData[sample]);
                if (absValue > threshold)
                {
                    float ratio = 4.0f;
                    float reduction = 1.0f / ratio;
                    channelData[sample] *= reduction;
                }
            }
        }
    }

    // Apply output gain
    float outputLinear = juce::Decibels::decibelsToGain(outputGain);
    buffer.applyGain(outputLinear);

    // Calculate VU level
    float maxLevel = 0.0f;
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getReadPointer(channel);
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            maxLevel = std::max(maxLevel, std::abs(channelData[sample]));
        }
    }
    
    vuLevel = juce::Decibels::gainToDecibels(maxLevel, -100.0f);
}

juce::AudioProcessorEditor* ThaiCompressorVSTAudioProcessor::createEditor()
{
    return new ThaiCompressorVSTAudioProcessorEditor(*this);
}

const juce::String ThaiCompressorVSTAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

void ThaiCompressorVSTAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    auto state = std::make_unique<juce::XmlElement>("ThaiCompressor");
    state->setAttribute("gain", gain);
    state->setAttribute("peakReduction", peakReduction);
    state->setAttribute("outputGain", outputGain);
    
    copyXmlToBinary(*state, destData);
}

void ThaiCompressorVSTAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    auto xmlState = getXmlFromBinary(data, sizeInBytes);
    
    if (xmlState != nullptr)
    {
        if (xmlState->hasTagName("ThaiCompressor"))
        {
            gain = (float)xmlState->getDoubleAttribute("gain", 0.0);
            peakReduction = (float)xmlState->getDoubleAttribute("peakReduction", 0.0);
            outputGain = (float)xmlState->getDoubleAttribute("outputGain", 0.0);
        }
    }
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ThaiCompressorVSTAudioProcessor();
}
