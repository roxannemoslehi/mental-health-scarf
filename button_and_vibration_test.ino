
void vibrate() {
   // vibration setup
  drv.begin();
  drv.selectLibrary(1);
  drv.setMode(DRV2605_MODE_INTTRIG);

  Serial.print("Playing vibrations"); Serial.println(effect);

  // create the waveform to play
  drv.setWaveform(0, 88);
  drv.setWaveform(89, 89);
  drv.setWaveform(44, 44);
  drv.setWaveform(88, 88);
  drv.setWaveform(89, 89);
  drv.setWaveform(44, 0);

  // play the effect!
  drv.go();

  // wait a bit
  delay(500);
}

//#include <Wire.h>
//#include "Adafruit_DRV2605.h"
//
//Adafruit_DRV2605 drv;
//
//int pin1 = 6;
//volatile int state = LOW;
//
//long lastDebounceTime = 0;
//long debounceDelay = 300;
//int lastButton = LOW;
//int buttonState;
//
//long lastButtonPress = 0;
//
//void setup(void)
//{
////  while (!Serial);  // required for Flora & Micro
//  delay(500);
//  Serial.begin(9600);
//  pinMode(pin1, INPUT_PULLUP);
//
//// vibration testing
//  Serial.println("DRV test");
//  drv.begin();
//  
//  drv.selectLibrary(1);
//  
//  // I2C trigger by sending 'go' command 
//  // default, internal trigger when sending GO command
//  drv.setMode(DRV2605_MODE_INTTRIG); 
//}
//
//// 89, 34
//uint8_t effect = 88;
//
//void loop(void)
//{
//
//  // vibration setup
//  drv.begin();
//  drv.selectLibrary(1);
//  drv.setMode(DRV2605_MODE_INTTRIG); 
//
//  
//  /* Wait for new data to arrive */
//
////  Serial.println(digitalRead(pin1));
////  if (digitalRead(pin1) == LOW && (millis() - lastDebounceTime) > debounceDelay) {
////  button pressed
//  if (digitalRead(pin1) == LOW && (millis() - lastDebounceTime) > debounceDelay) {
//        long pressed = millis();
//        Serial.println("button pressed");
//        lastDebounceTime = millis();
//  } else {
//        Serial.println("HIGH");
//
//  }
//
//  //vibration testing
//  Serial.print("Effect #"); Serial.println(effect);
//
//  // set the effect to play
//  drv.setWaveform(0, effect);  // play effect 
//  drv.setWaveform(1, 0);       // end waveform
//
//  // play the effect!
//  drv.go();
//
//  // wait a bit
//  delay(500);
//
////  effect++;
//  if (effect > 117) effect = 1;
//}
//
//

