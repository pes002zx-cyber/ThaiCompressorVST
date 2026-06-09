name: Build VST3

on:
  push:
    branches: [ main ]
  workflow_dispatch:

jobs:
  build-windows:
    runs-on: windows-latest

    steps:
    - name: Checkout code
      uses: actions/checkout@v4

    - name: Clone JUCE
      run: git clone --depth 1 https://github.com/juce-framework/JUCE.git C:/JUCE

    - name: Configure CMake
      run: |
        mkdir build
        cd build
        cmake -G "Visual Studio 17 2022" -A x64 -DCMAKE_PREFIX_PATH=C:/JUCE ..

    - name: Build
      run: cmake --build build --config Release

    - name: Upload VST3
      uses: actions/upload-artifact@v4
      with:
        name: ThaiCompressorVST3
        path: build/ThaiCompressorVST_artefacts/Release/VST3/
