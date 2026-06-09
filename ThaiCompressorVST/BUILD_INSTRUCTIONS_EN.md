# Thai Compressor VST3 Build Instructions for Windows

## Step 1: Install Visual Studio 2022

1. Download Visual Studio 2022 Community (Free) from: https://visualstudio.microsoft.com/downloads/
2. Install and select **Desktop development with C++**
3. Install CMake (via Visual Studio Installer)

## Step 2: Install JUCE Framework

1. Download JUCE from: https://juce.com/download/
2. Extract JUCE to `C:\JUCE` (or your preferred location)

## Step 3: Prepare Source Code

1. Create folder: `C:\ThaiCompressorVST`
2. Copy all files from here into that folder

```
C:\ThaiCompressorVST\
├── CMakeLists.txt
├── Source\
│   ├── PluginProcessor.h
│   ├── PluginProcessor.cpp
│   ├── PluginEditor.h
│   └── PluginEditor.cpp
```

## Step 4: Compile with CMake

1. Open Command Prompt (cmd.exe)
2. Navigate to folder: `cd C:\ThaiCompressorVST`
3. Create build folder:
   ```
   mkdir build
   cd build
   ```

4. Generate Visual Studio Project:
   ```
   cmake -G "Visual Studio 17 2022" -A x64 -DCMAKE_PREFIX_PATH=C:\JUCE ..
   ```

5. Build:
   ```
   cmake --build . --config Release
   ```

## Step 5: Find VST3 Plugin

The .vst3 file will be located at:
```
C:\ThaiCompressorVST\build\ThaiCompressorVST_artefacts\Release\VST3\ThaiCompressorVST.vst3
```

## Step 6: Install in Studio One

1. Copy `ThaiCompressorVST.vst3` to:
   ```
   C:\Program Files\Common Files\VST3\
   ```

2. Open Studio One
3. Go to **Preferences** → **Plug-ins** → **Rescan**
4. Search for "Thai Compressor" in Plugin Library

## Troubleshooting

### CMake cannot find JUCE
- Verify that you changed `C:\JUCE` to match your JUCE installation path

### Visual Studio not found
- Install Visual Studio 2022 Community again
- Select "Desktop development with C++"

### Compilation Error
- Verify Visual Studio 2022 is fully installed
- Try deleting the build folder and creating it again

## Support

For more help, see JUCE Documentation: https://docs.juce.com/

---

**VST3 Size:** ~10-15 MB
**Compatibility:** Windows 10/11, Studio One 5.x, 6.x
**Type:** VST3 64-bit
