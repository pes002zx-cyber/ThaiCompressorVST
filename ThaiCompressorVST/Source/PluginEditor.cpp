#include "PluginEditor.h"

ThaiCompressorVSTAudioProcessorEditor::ThaiCompressorVSTAudioProcessorEditor(ThaiCompressorVSTAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    setSize(800, 300);
    setResizable(false, false);

    // Gain Slider
    gainSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    gainSlider.setRange(-40.0, 40.0, 0.1);
    gainSlider.setValue(0.0);
    gainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    gainSlider.addListener(this);
    addAndMakeVisible(gainSlider);

    gainLabel.setText("GAIN", juce::dontSendNotification);
    gainLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(gainLabel);

    // Peak Reduction Slider
    peakReductionSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    peakReductionSlider.setRange(0.0, 40.0, 0.1);
    peakReductionSlider.setValue(0.0);
    peakReductionSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    peakReductionSlider.addListener(this);
    addAndMakeVisible(peakReductionSlider);

    peakLabel.setText("PEAK REDUCTION", juce::dontSendNotification);
    peakLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(peakLabel);

    // Output Slider
    outputSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    outputSlider.setRange(-20.0, 20.0, 0.1);
    outputSlider.setValue(0.0);
    outputSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    outputSlider.addListener(this);
    addAndMakeVisible(outputSlider);

    outputLabel.setText("OUTPUT", juce::dontSendNotification);
    outputLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(outputLabel);

    // Title
    titleLabel.setText("Thai Compressor MRY-2A", juce::dontSendNotification);
    titleLabel.setJustificationType(juce::Justification::centred);
    titleLabel.setFont(juce::Font(24.0f, juce::Font::bold));
    addAndMakeVisible(titleLabel);

    startTimer(50);
}

ThaiCompressorVSTAudioProcessorEditor::~ThaiCompressorVSTAudioProcessorEditor()
{
    stopTimer();
}

void ThaiCompressorVSTAudioProcessorEditor::paint(juce::Graphics& g)
{
    // Background - Gold color
    g.fillAll(juce::Colour(212, 175, 55));

    // Draw wood texture on sides
    g.setColour(juce::Colour(101, 67, 33));
    g.fillRect(0, 0, 30, getHeight());
    g.fillRect(getWidth() - 30, 0, 30, getHeight());

    // Draw decorative border
    g.setColour(juce::Colour(139, 90, 43));
    g.drawRect(30, 20, getWidth() - 60, getHeight() - 40, 3);

    // Draw Kranok patterns
    drawKranokPattern(g, 35, 25, 25, 60);
    drawKranokPattern(g, getWidth() - 60, 25, 25, 60);

    // Draw VU Meter
    drawVUMeter(g, getWidth() / 2 - 80, 80, 160, 120);

    // Draw labels for controls
    g.setColour(juce::Colours::black);
    g.setFont(juce::Font(12.0f));
}

void ThaiCompressorVSTAudioProcessorEditor::resized()
{
    auto bounds = getLocalBounds();

    // Title
    titleLabel.setBounds(bounds.removeFromTop(40).reduced(10));

    // VU Meter area
    auto meterArea = bounds.removeFromTop(140).reduced(20);
    int meterX = meterArea.getCentreX() - 80;
    int meterY = meterArea.getY();

    // Sliders
    auto sliderArea = bounds.reduced(20);
    int sliderSpacing = sliderArea.getWidth() / 3;

    gainSlider.setBounds(sliderArea.getX() + sliderSpacing / 2 - 50, sliderArea.getY(), 100, 100);
    gainLabel.setBounds(gainSlider.getX(), gainSlider.getBottom(), 100, 20);

    peakReductionSlider.setBounds(sliderArea.getCentreX() - 50, sliderArea.getY(), 100, 100);
    peakLabel.setBounds(peakReductionSlider.getX(), peakReductionSlider.getBottom(), 100, 20);

    outputSlider.setBounds(sliderArea.getRight() - sliderSpacing / 2 - 50, sliderArea.getY(), 100, 100);
    outputLabel.setBounds(outputSlider.getX(), outputSlider.getBottom(), 100, 20);
}

void ThaiCompressorVSTAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &gainSlider)
        audioProcessor.gain = gainSlider.getValue();
    else if (slider == &peakReductionSlider)
        audioProcessor.peakReduction = peakReductionSlider.getValue();
    else if (slider == &outputSlider)
        audioProcessor.outputGain = outputSlider.getValue();
}

void ThaiCompressorVSTAudioProcessorEditor::timerCallback()
{
    vuMeterLevel = audioProcessor.vuLevel;
    repaint();
}

void ThaiCompressorVSTAudioProcessorEditor::drawVUMeter(juce::Graphics& g, int x, int y, int width, int height)
{
    // Meter background
    g.setColour(juce::Colour(240, 230, 200));
    g.fillRoundedRectangle(x, y, width, height, 5.0f);

    // Meter border
    g.setColour(juce::Colours::black);
    g.drawRoundedRectangle(x, y, width, height, 5.0f, 2.0f);

    // Draw scale
    g.setFont(juce::Font(10.0f));
    g.setColour(juce::Colours::black);
    
    for (int i = -20; i <= 3; i += 5)
    {
        float normalized = (i + 20.0f) / 23.0f;
        int xPos = x + 20 + (width - 40) * normalized;
        g.drawText(juce::String(i), xPos - 10, y + height - 20, 20, 15, juce::Justification::centred);
        g.drawLine(xPos, y + height - 25, xPos, y + height - 30);
    }

    // Draw needle
    float normalizedLevel = (vuMeterLevel + 20.0f) / 23.0f;
    normalizedLevel = juce::jlimit(0.0f, 1.0f, normalizedLevel);
    
    int needleX = x + 20 + (width - 40) * normalizedLevel;
    int needleY = y + height / 2;
    
    g.setColour(juce::Colours::red);
    g.drawLine(needleX, needleY - 20, needleX, needleY + 20, 2.0f);

    // Label
    g.setColour(juce::Colours::black);
    g.setFont(juce::Font(14.0f, juce::Font::bold));
    g.drawText("VU LEVEL INDICATOR", x, y + 10, width, 20, juce::Justification::centred);
}

void ThaiCompressorVSTAudioProcessorEditor::drawKranokPattern(juce::Graphics& g, int x, int y, int width, int height)
{
    // Simple Thai Kranok-inspired pattern
    g.setColour(juce::Colour(139, 90, 43));
    
    // Draw decorative swirls
    juce::Path path;
    path.startNewSubPath(x, y + height / 2);
    path.quadraticTo(x + width / 2, y, x + width, y + height / 2);
    path.quadraticTo(x + width / 2, y + height, x, y + height / 2);
    
    g.strokePath(path, juce::PathStrokeType(2.0f));
    
    // Draw small circles for decoration
    g.fillEllipse(x + width / 4, y + height / 4, 3, 3);
    g.fillEllipse(x + 3 * width / 4, y + height / 4, 3, 3);
    g.fillEllipse(x + width / 4, y + 3 * height / 4, 3, 3);
    g.fillEllipse(x + 3 * width / 4, y + 3 * height / 4, 3, 3);
}
