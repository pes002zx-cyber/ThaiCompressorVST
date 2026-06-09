# Thai Compressor MRY-2A VST3 Plugin

A professional audio compressor plugin with traditional Thai aesthetic design, built for Studio One and other VST3-compatible DAWs.

## Features

- **Thai-Inspired Design**: Golden color scheme with traditional Kranok (Thai decorative) patterns
- **Professional Compressor**: 
  - Gain control (-40 dB to +40 dB)
  - Peak Reduction (0-40 dB)
  - Output control (-20 dB to +20 dB)
  - Real-time VU meter display
- **VST3 64-bit**: Compatible with modern DAWs
- **Low Latency**: Optimized for real-time audio processing

## System Requirements

- **OS**: Windows 10/11 (64-bit)
- **DAW**: Studio One 5.x, 6.x or any VST3-compatible DAW
- **RAM**: 512 MB minimum
- **CPU**: Intel/AMD processor with SSE2 support

## Building from Source

### Prerequisites
- Visual Studio 2022 Community (Free)
- CMake 3.15+
- JUCE Framework

### Quick Start

1. Read `BUILD_INSTRUCTIONS_EN.md` (English) or `BUILD_INSTRUCTIONS_TH.md` (Thai)
2. Install dependencies
3. Run CMake to generate Visual Studio project
4. Compile in Release mode
5. Copy VST3 to your DAW's plugin folder

## File Structure

```
ThaiCompressorVST/
├── CMakeLists.txt                 # Build configuration
├── Source/
│   ├── PluginProcessor.h          # Audio processing header
│   ├── PluginProcessor.cpp        # Audio processing implementation
│   ├── PluginEditor.h             # UI header
│   └── PluginEditor.cpp           # UI implementation
├── BUILD_INSTRUCTIONS_EN.md       # English build guide
├── BUILD_INSTRUCTIONS_TH.md       # Thai build guide
└── README.md                      # This file
```

## Audio Processing

### Compressor Algorithm

The compressor uses a simple but effective algorithm:

1. **Input Gain**: Applies input level adjustment
2. **Peak Reduction**: Reduces peaks above threshold with 4:1 ratio
3. **Output Gain**: Final output level control
4. **VU Meter**: Real-time level monitoring (-20 dB to +3 dB)

## UI Design

The plugin features:
- **Gold brushed metal** front panel (inspired by vintage gear)
- **Thai Kranok patterns** on decorative corners
- **Dark wood** side panels
- **Vintage VU meter** with real-time needle
- **Three rotary knobs** for intuitive control

## Installation

1. Build the plugin following the build instructions
2. Copy `ThaiCompressorVST.vst3` to:
   ```
   C:\Program Files\Common Files\VST3\
   ```
3. Rescan plugins in your DAW
4. Load "Thai Compressor MRY-2A" from your plugin library

## Usage

1. Insert the plugin on an audio track
2. Adjust **GAIN** to set input level
3. Use **PEAK REDUCTION** to control compression
4. Set **OUTPUT** to desired output level
5. Monitor levels with the VU meter

## Technical Details

- **Format**: VST3 64-bit
- **Channels**: Stereo
- **Sample Rates**: 44.1 kHz - 192 kHz
- **Buffer Sizes**: Adaptive
- **Latency**: < 1 ms

## Development

Built with:
- **JUCE Framework**: Professional audio plugin development
- **C++17**: Modern C++ standard
- **CMake**: Cross-platform build system

## License

This project is provided as-is for educational and personal use.

## Support

For build issues, refer to:
- JUCE Documentation: https://docs.juce.com/
- JUCE Forum: https://forum.juce.com/

---

**Version**: 1.0.0  
**Release Date**: 2026  
**Compatibility**: Windows 10/11, VST3 64-bit
