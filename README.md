# Touch to MIDI
### Browser-based Arduino MIDI bridge for Ableton Live

I wanted to make an easy-to-use way to turn touch and small changes in electrical signals into music, without having to install specialist serial-to-MIDI software. The project began with two conductive touch contacts and has developed into an experimental interface for exploring **touch-sensitive surfaces, plants and other living materials as musical inputs**.

The application runs as a **single HTML file in Chrome or Edge**. It connects an Arduino Mega to Ableton Live, where changes at the sensor produce evolving, partly randomised MIDI sequences. Musical parameters can be adjusted live in the browser.

> **AI-generated prototype:** The Arduino code, browser application and this README were generated with assistance from OpenAI's ChatGPT through an iterative process of prompting, testing and revision. The artistic direction, requirements and hands-on experimentation informed that process. This is experimental software, not a fully validated hardware product.

## What it does

- Connects an **Arduino Mega 2560** to Ableton Live using browser-based Web Serial and Web MIDI.
- Converts changes on analogue input **A0** into generative MIDI notes.
- Calibrates the sensor's resting voltage and stays musically silent until the signal rises above a chosen threshold.
- Provides live controls for sensitivity, note speed, note length, randomness, transpose, voltage influence and scale.
- Displays raw sensor readings, a magnified voltage-change meter and serial/MIDI diagnostics.
- Includes MIDI test notes for checking the Ableton connection without the sensor.

**Signal path:** touch or plant contact → Arduino A0 → USB serial → HTML bridge → macOS IAC Driver → Ableton Live.

## What you need

- Arduino Mega 2560 and USB cable
- Mac with **Chrome or Edge** (Safari does not support the required Web Serial connection)
- Ableton Live and the built-in macOS **IAC Driver**
- Two conductive contacts and two **1 MΩ resistors** for the basic sensor
- Arduino IDE to upload the sketch initially

**No separate serial-to-MIDI bridge application is needed.** The browser file does not require installation, although the Arduino sketch must first be uploaded and browser/device permissions must be allowed. Managed computers may restrict these permissions.

## Files

- `mega_ableton_browser_bridge_v5.html` — browser interface, MIDI bridge, live controls and sensor diagnostics
- `Mega_Touch_Random_MIDI_v5.ino` — Arduino firmware, sensor calibration and MIDI note generation

## Quick start

1. Upload `Mega_Touch_Random_MIDI_v5.ino` to the Arduino Mega using the Arduino IDE.
2. In **Audio MIDI Setup** on the Mac, open **MIDI Studio → IAC Driver** and enable **Device is online**.
3. Open `mega_ableton_browser_bridge_v5.html` in Chrome or Edge. Select the IAC Driver as the MIDI output.
4. In Ableton Live, enable **Track** for the IAC Driver MIDI input. Create a MIDI track, load an instrument and set monitoring to **In**.
5. Click **Play 8-note test** in the browser. Check that Ableton's MIDI input indicator flashes and the instrument sounds.
6. Connect the Arduino in the HTML interface at **115200 baud**. Close the Arduino IDE's Serial Monitor first.
7. With the touch contacts untouched, click **Calibrate resting voltage**. Touch the contacts and adjust **Trigger rise above baseline** until notes begin only when you want them to.

The Arduino sends diagnostic readings even when silent; these are filtered out by the HTML bridge before forwarding musical MIDI messages to Ableton.

## Basic touch wiring

```text
Arduino 5V ──[1 MΩ]── Contact 1
                            ↕ touch or conductive connection
Arduino A0 ────────── Contact 2
    │
    └────────[1 MΩ]── Arduino GND
```

Bridging the two contacts changes the voltage at A0. The **1 MΩ pull-down resistor** is important: without it, A0 may float and produce false triggers. The browser lets you measure the resting level and set a trigger threshold above it.

## Plants and capacitive sensing

The current v5 sketch measures **voltage/conductivity**, not capacitance directly. A plant or moist surface may form part of an experimental conductive path between suitable electrodes, producing changes that can affect the MIDI sequence. Results depend on contact, moisture and the physical arrangement; plant input has not been formally validated.

**Capacitive touch sensing** is a possible next development, but it requires an appropriate capacitive-sensing circuit/module and corresponding Arduino code. It should not be assumed to work simply by connecting a capacitive sensor to A0 with the existing sketch.

## Safety and limitations

Use only low-voltage Arduino circuits. **Never apply more than 5 V or a negative voltage to A0**, and never connect mains electricity to the touch contacts or plants. The sensor is experimental and may need recalibration as its environment changes. The HTML page requires browser access to both USB serial and MIDI devices.

## Project status

**Experimental / work in progress.** Developed as a simple, accessible way to investigate how touch, living materials and changing electrical conditions might become musical interfaces. Feedback, adaptations and further experiments are welcome.
