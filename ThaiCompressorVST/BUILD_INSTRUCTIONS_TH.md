# คำแนะนำการสร้าง Thai Compressor VST3 บน Windows

## ขั้นตอนที่ 1: ติดตั้ง Visual Studio 2022

1. ดาวน์โหลด Visual Studio 2022 Community (ฟรี) จาก: https://visualstudio.microsoft.com/downloads/
2. ติดตั้งและเลือก **Desktop development with C++**
3. ติดตั้ง CMake (ผ่าน Visual Studio Installer)

## ขั้นตอนที่ 2: ติดตั้ง JUCE Framework

1. ดาวน์โหลด JUCE จาก: https://juce.com/download/
2. แตกไฟล์ JUCE ลงใน `C:\JUCE` (หรือที่อื่นตามต้องการ)

## ขั้นตอนที่ 3: เตรียมไฟล์ Source Code

1. สร้าง folder: `C:\ThaiCompressorVST`
2. คัดลอกไฟล์ทั้งหมดจากที่นี่ลงไปใน folder นั้น

```
C:\ThaiCompressorVST\
├── CMakeLists.txt
├── Source\
│   ├── PluginProcessor.h
│   ├── PluginProcessor.cpp
│   ├── PluginEditor.h
│   └── PluginEditor.cpp
```

## ขั้นตอนที่ 4: Compile ด้วย CMake

1. เปิด Command Prompt (cmd.exe)
2. ไปที่ folder: `cd C:\ThaiCompressorVST`
3. สร้าง build folder:
   ```
   mkdir build
   cd build
   ```

4. สร้าง Visual Studio Project:
   ```
   cmake -G "Visual Studio 17 2022" -A x64 -DCMAKE_PREFIX_PATH=C:\JUCE ..
   ```

5. Compile:
   ```
   cmake --build . --config Release
   ```

## ขั้นตอนที่ 5: หา VST3 Plugin

ไฟล์ .vst3 จะอยู่ที่:
```
C:\ThaiCompressorVST\build\ThaiCompressorVST_artefacts\Release\VST3\ThaiCompressorVST.vst3
```

## ขั้นตอนที่ 6: ติดตั้งใน Studio One

1. คัดลอกไฟล์ `ThaiCompressorVST.vst3` ไปที่:
   ```
   C:\Program Files\Common Files\VST3\
   ```

2. เปิด Studio One ใหม่
3. ไปที่ **Preferences** → **Plug-ins** → **Rescan**
4. ค้นหา "Thai Compressor" ใน Plugin Library

## ปัญหาที่อาจเกิดขึ้น

### CMake ไม่พบ JUCE
- ตรวจสอบว่าเปลี่ยน `C:\JUCE` ให้ตรงกับที่คุณติดตั้ง JUCE

### Visual Studio ไม่พบ
- ติดตั้ง Visual Studio 2022 Community ใหม่
- เลือก "Desktop development with C++"

### Compilation Error
- ตรวจสอบว่า Visual Studio 2022 ติดตั้งเสร็จแล้ว
- ลองลบ build folder และสร้างใหม่

## ติดต่อ

หากมีปัญหา ลองดู JUCE Documentation: https://docs.juce.com/

---

**ขนาด VST3:** ~10-15 MB
**ความเข้ากันได้:** Windows 10/11, Studio One 5.x, 6.x
**ประเภท:** VST3 64-bit
