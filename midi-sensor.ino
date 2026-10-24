// Set to 1 to print button readings in Serial Monitor instead of sending MIDI.
// Text diagnostics must not be mixed into the serial-to-MIDI byte stream.
#define DEBUG_SERIAL 0

// Connect each momentary button between its pin and GND.
// The matching MIDI notes are listed at the same array index.
const byte buttonPins[] = {2, 3, 4, 5};
const byte midiNotes[] = {60, 62, 64, 65};
const byte buttonCount = sizeof(buttonPins) / sizeof(buttonPins[0]);
const byte midiChannel = 0;  // MIDI channel 1 (channels are numbered from zero).
const byte noteVelocity = 100;
const unsigned long debounceMs = 25;

// Stores the debounced and most recent electrical state for each button.
struct ButtonState {
  byte stableState;
  byte lastReading;
  unsigned long lastChangeMs;
};

ButtonState buttons[buttonCount];

// MIDI Note On: status byte, note number, and velocity.
void sendNoteOn(byte note) {
  Serial.write(0x90 | midiChannel);
  Serial.write(note);
  Serial.write(noteVelocity);
}

// MIDI Note Off: status byte, note number, and release velocity.
void sendNoteOff(byte note) {
  Serial.write(0x80 | midiChannel);
  Serial.write(note);
  Serial.write((byte)0);
  
}

void setup() {
  Serial.begin(115200);  // Match this baud rate in the serial-MIDI bridge.

  for (byte i = 0; i < buttonCount; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);  // Pressed = LOW; released = HIGH.
    byte reading = digitalRead(buttonPins[i]);
    buttons[i].stableState = reading;
    buttons[i].lastReading = reading;
    buttons[i].lastChangeMs = millis();
  }
}

void loop() {
  unsigned long now = millis();

  for (byte i = 0; i < buttonCount; i++) {
    byte reading = digitalRead(buttonPins[i]);

    // Restart the debounce timer whenever the raw input changes.
    if (reading != buttons[i].lastReading) {
      buttons[i].lastReading = reading;
      buttons[i].lastChangeMs = now;
    }

    // Accept the new state only after it remains stable for debounceMs.
    if (reading != buttons[i].stableState &&
        now - buttons[i].lastChangeMs >= debounceMs) {
      buttons[i].stableState = reading;

    #if DEBUG_SERIAL
      Serial.print("Tofu: pin ");
      Serial.print(buttonPins[i]);
      Serial.print(" = ");
      Serial.println(reading);
    #else
      if (reading == LOW) {
        sendNoteOn(midiNotes[i]);
      } else {
        sendNoteOff(midiNotes[i]);
      }
    #endif
    }
  }
}