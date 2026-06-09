#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include "PluginProcessor.h"

class ThaiCompressorVSTAudioProcessorEditor : public juce::AudioProcessorEditor,
                                               private juce::Slider::Listener,
                                               private juce::Timer
{
public:
    explicit ThaiCompressorVSTAudioProcessorEditor(ThaiCompressorVSTAudioProcessor&);
    ~ThaiCompressorVSTAudioProcessorEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    ThaiCompressorVSTAudioProcessor& audioProcessor;

    juce::Slider gainSlider;
    juce::Slider peakReductionSlider;
    juce::Slider outputSlider;

    juce::Label gainLabel;
    juce::Label peakLabel;
    juce::Label outputLabel;
    juce::Label titleLabel;

    float vuMeterLevel = -20.0f;

    void sliderValueChanged(juce::Slider* slider) override;
    void timerCallback() override;

    void drawVUMeter(juce::Graphics& g, int x, int y, int width, int height);
    void drawKranokPattern(juce::Graphics& g, int x, int y, int width, int height);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ThaiCompressorVSTAudioProcessorEditor)
};
