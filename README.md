# Flanger Audio Plugin

This project is an audio flanger effect, initially developed and tested in MATLAB, then implemented as a VST3 plugin using JUCE, and finally tested in REAPER with an audio file.

## 1. MATLAB Implementation

The first step in creating the flanger effect was to develop and test it in MATLAB. This involved:

- Reading an audio file and applying a variable delay to create the characteristic flanger sound.
- Using a low-frequency oscillator (LFO) to modulate the delay time dynamically.
- Combining the original signal with the delayed signal to produce the classic flanger effect.

The MATLAB script `FLANGER.m` demonstrates this process. It processes an input file (e.g., `Caramitru44kScurt.wav`) and applies the flanger algorithm before playing the output.

## 2. JUCE Implementation

After validating the MATLAB implementation, the flanger was ported to C++ using the JUCE framework. The key steps included:

- Writing the processing logic in `PluginProcessor.cpp`, applying the same variable delay principle used in MATLAB.
- Designing the plugin interface in `PluginEditor.cpp`, providing controls for flanger parameters (e.g., LFO rate, depth, feedback).
- Exporting the project as a VST3 plugin (`Flanger.vst3`).

## 3. Testing in REAPER

The final stage was testing the VST3 plugin in REAPER, a digital audio workstation (DAW). This involved:

- Loading an audio track (same as the one used in MATLAB).
- Applying the custom-built flanger plugin.
- Tweaking parameters to compare the JUCE implementation with the MATLAB prototype.

(Juce/REAPER_Implementation.png)

## Installation & Usage

1. **MATLAB**: Run `FLANGER.m` with an audio file to test the MATLAB version.
2. **JUCE Plugin**:
   - Copy `Flanger.vst3` to your VST3 plugins folder.
   - Open REAPER (or another DAW) and load the plugin on an audio track.
3. **Compare Results**: Use the same audio file in both MATLAB and REAPER to analyze the similarity of the effects.

## Conclusion

This project showcases a full audio DSP workflow: from MATLAB prototyping to JUCE implementation and real-world DAW testing.
