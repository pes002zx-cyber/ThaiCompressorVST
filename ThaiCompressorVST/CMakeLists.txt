cmake_minimum_required(VERSION 3.15)
project(ThaiCompressorVST VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add JUCE as a subdirectory
add_subdirectory(../JUCE JUCE)

# Create the plugin
juce_add_plugin(ThaiCompressorVST
    COMPANY_NAME "Thai Audio"
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS FALSE
    COPY_PLUGIN_AFTER_BUILD TRUE
    PLUGIN_MANUFACTURER_CODE "THAI"
    PLUGIN_CODE "TCMP"
    FORMATS VST3
    PRODUCT_NAME "Thai Compressor MRY-2A")

# Add source files
target_sources(ThaiCompressorVST PRIVATE
    Source/PluginProcessor.cpp
    Source/PluginEditor.cpp)

# Link JUCE modules
target_link_libraries(ThaiCompressorVST PRIVATE
    juce::juce_audio_basics
    juce::juce_audio_devices
    juce::juce_audio_formats
    juce::juce_audio_plugin_client
    juce::juce_audio_processors
    juce::juce_audio_utils
    juce::juce_core
    juce::juce_data_structures
    juce::juce_events
    juce::juce_graphics
    juce::juce_gui_basics
    juce::juce_gui_extra
    juce::juce_dsp)

# Set plugin properties
set_target_properties(ThaiCompressorVST PROPERTIES
    MACOSX_DEPLOYMENT_TARGET "10.13"
    XCODE_ATTRIBUTE_GCC_OPTIMIZATION_LEVEL "3"
    XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_DIALECT "c++17")
