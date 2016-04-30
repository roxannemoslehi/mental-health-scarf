// A simple trigger for the Adafruit Audio FX Sound Board
// For complete info on the sound board, see https://learn.adafruit.com/adafruit-audio-fx-sound-board/overview

/*
This is a simple test of a direct trigger of the Audio FX Sounds Board from an Arduino.
For my test, I used an Arduino Pro Mini running at 3.3v & 8mHz. Digital pin #4 of the Arduino
was connected to trigger pin #0 of the Sound Board, and I tied them to a common ground. I powered
Sound Board via a USB external battery for the initial tests, and the Arduino via the FTDI cable.
For later tests, I powered the Sound Board via the Arduino's VCC (3v) pin directly.
*/

#define PIN 12
#define BUTTON 6 // put a simple button on pin 2 to enable/disable sound playback

void setup() {
  pinMode(BUTTON, INPUT_PULLUP);
  setupSound(PIN);
}

void loop() {
  if (digitalRead(BUTTON) == LOW) {
    delay(500);
    activateSound(PIN);
    delay(500);
    Serial.println("pressed button");
  }
}

void setupSound(int pin) {
  Serial.println("Setting up Sound");
  pinMode(pin, OUTPUT);
  digitalWrite(pin, HIGH); // Set the pin high as the default state
}

void activateSound(int pin) {
  Serial.println("Activating Sound");
  digitalWrite(pin, LOW); // bring the pin low to begin the activation
  /*
  According to the documentation, the Audio FX board needs 50ms to trigger. However,
  I've found that coming from my 3.3v Arduino Pro, it needs 100ms to get the trigger
  the going
  */
  delay(500); // hold the pin low long enough to trigger the board; may need to be longer for consistent triggering
  digitalWrite(pin, HIGH);// bring the pin high again to end the activation
}
