/*
  Web client
 This sketch connects to a website (http://www.adafruit.com)
 using a WINC1500
 This example is written for a network using WPA encryption. For
 WEP or WPA, change the Wifi.begin() call accordingly.
 This example is written for a network using WPA encryption. For
 WEP or WPA, change the Wifi.begin() call accordingly.
 * Circuit:
 * - Feather M0 WiFi (WINC1500), WiFi 101 shield, or WINC1500 Breakout
 created 13 July 2010
 by dlf (Metodo2 srl)
 modified 31 May 2012
 by Tom Igoe
 */
//A simple trigger for the Adafruit Audio FX Sound Board
//For complete info on the sound board, see https://learn.adafruit.com/adafruit-audio-fx-sound-board/overview

/*
This is a simple test of a direct trigger of the Audio FX Sounds Board from an Arduino.
For my test, I used an Arduino Pro Mini running at 3.3v & 8mHz. Digital pin #4 of the Arduino
was connected to trigger pin #0 of the Sound Board, and I tied them to a common ground. I powered
Sound Board via a USB external battery for the initial tests, and the Arduino via the FTDI cable.
For later tests, I powered the Sound Board via the Arduino's VCC (3v) pin directly.
*/


#include <SPI.h>
#include <Adafruit_WINC1500.h>

#include <Wire.h>
#include "Adafruit_DRV2605.h"


#define PIN 4
#define SOUND_PIN 12



// Define the WINC1500 board connections below.
// If you're following the Adafruit WINC1500 board
// guide you don't need to modify these:
#define WINC_CS   8
#define WINC_IRQ  7
#define WINC_RST  4
#define WINC_EN   2     // or, tie EN to VCC and comment this out
// The SPI pins of the WINC1500 (SCK, MOSI, MISO) should be
// connected to the hardware SPI port of the Arduino.
// On an Uno or compatible these are SCK = #13, MISO = #12, MOSI = #11.
// On an Arduino Zero use the 6-pin ICSP header, see:
//   https://www.arduino.cc/en/Reference/SPI

// Setup the WINC1500 connection with the pins above and the default hardware SPI.
Adafruit_WINC1500 WiFi(WINC_CS, WINC_IRQ, WINC_RST);

// Or just use hardware SPI (SCK/MOSI/MISO) and defaults, SS -> #10, INT -> #7, RST -> #5, EN -> 3-5V
//Adafruit_WINC1500 WiFi;


//char ssid[] = "Juan's iPhone";     //  your network SSID (name)
//char pass[] = "poopoo23";

char ssid[] = "Roxanne's iPhone";     //  your network SSID (name)
char pass[] = "blueberries9";    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;                // your network key Index number (needed only for WEP)

//char ssid[] = "Shabahaba";     //  your network SSID (name)
//char pass[] = "hellowassup";


Adafruit_DRV2605 drv;

int button = 6;
volatile int state = LOW;

long lastDebounceTime = 0;
long debounceDelay = 100;
int lastButton = LOW;
int buttonState;
bool connection;

long lastButtonPress = 0;

String post_type = "";
int vibrate_count = 0;

//bool pressed;
//pressed = false;

int status = WL_IDLE_STATUS;
// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
//IPAddress server(141,101,112,175);  // numeric IP for test page (no DNS)
char server[] = "224b3ae9.ngrok.io";    // domain name for test page (using DNS)


// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):


Adafruit_WINC1500Client client;

void setup() {
#ifdef WINC_EN
  pinMode(WINC_EN, OUTPUT);
  digitalWrite(WINC_EN, HIGH);
  pinMode(button, INPUT_PULLUP);
  setupSound(SOUND_PIN);
#endif

//  while (!Serial);  // required for Flora & Micro
  delay(500);
  Serial.begin(9600);
  pinMode(button, INPUT_PULLUP);

// vibration testing
//  Serial.println("DRV test");
//  drv.begin();
//  
//  drv.selectLibrary(1);
//  
//  // I2C trigger by sending 'go' command 
//  // default, internal trigger when sending GO command
//  drv.setMode(DRV2605_MODE_INTTRIG); 
  

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  //Initialize serial and wait for port to open:
  Serial.begin(9600);

  Serial.println("WINC1500 Web client test");

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }

  // attempt to connect to Wifi network:
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    uint8_t timeout = 10;
    while (timeout && (WiFi.status() != WL_CONNECTED)) {
      timeout--;
      delay(1000);
    }
  }

  Serial.println("Connected to wifi");
  printWifiStatus();  

  Serial.println("Connecting to server");
  
  if (client.connect(server, 80)) {
    Serial.println("Client Connected");
  }   else {
    Serial.println("Client Not Connected");

   }

  }



uint8_t effect = 1;

void loop() {
  // if there are incoming bytes available
  // from the server, read them and print them:
  Serial.println("In loop"); 
  delay(250);


  

      
  check_for_button_press();

  if (vibrate_count == 25) {
      check_for_vibration();
      vibrate_count = 0;
  } else {
    vibrate_count ++;
    Serial.println(vibrate_count);
  }

  




//   if the server's disconnected, stop the client:
//  if (!client.connected()) {
//    Serial.println();
//    Serial.println("disconnecting from server.");
//    client.stop();
//
//    // do nothing forevermore:
//    while (true);
//  }
//  }
}




void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

void check_for_button_press() {

    Serial.print("checking for button press");

      
//    if (client.connect(server, 80)) {

   // --------------------- BUTTON PRESSING  --------------------- 
      if (digitalRead(button) == LOW && (millis() - lastDebounceTime) > debounceDelay) {
            long pressed = millis();
            Serial.println("------ BUTTON PRESSED ------");
            post();
//            pressed = true;
            lastDebounceTime = millis();

            delay(500);
            activateSound(SOUND_PIN);
            delay(500);
    
    //  } else {
    //        Serial.println("HIGH");
  
    
       }

//     client.stop();
//  }
//  
}

void post()
{

      Serial.println("Connecting to server");
      
      if (client.connect(server, 80)) 
      {
          Serial.println("Connected");
          Serial.println("Making Post Request for button press");
          post_type = "stressed";

          // Make a POST HTTP request:

          String data = "love";
          // For testing
          client.connect(server, 80);
          client.print("POST ");
          Serial.println("POST");
          client.print("/stressed");
          Serial.println("/stressed");
          client.println(" HTTP/1.1");
          Serial.println(" HTTP/1.1");
          client.print("Host: "); client.println(server);
          Serial.print(" Host: "); Serial.println(server);
          client.println("Connection: close");
          Serial.print("Connection: close");
          client.println("User-Agent: Arduino/1.0");
          Serial.print("User-Agent: Arduino/1.0");
          client.print("Content-Length: ");
          Serial.print("Content-Length: ");
          client.println(data.length());
          client.println();
          client.print(data);
          Serial.print("Sent data ");
          client.println();   
          Serial.print("Finished Post Request");
                        

      } else {
         Serial.println("Button client not connected to server");
      }
      client.stop();

 
}

void check_for_vibration()
{

//      char server2[] = "http://e5446b2b.ngrok.io/pressed";
      Serial.print("checking for vibrations");

//      love_client.connect(server, 80);

      if (client.connect(server, 80)) 
      {
          Serial.println("Connected");
          Serial.println("Making Post Request for Vibrations ");

          post_type = "pressed";

          // Make a POST HTTP request:

          String data = "checking";
          // For testing
          client.print("POST ");
          client.print("/pressed");
          client.println(" HTTP/1.1");
          client.print("Host: "); client.println(server);
          client.println("Connection: close");
          client.println("User-Agent: Arduino/1.0");
          client.print("Content-Length: ");
          client.println(data.length());
          client.println();
          client.print(data);
          client.println();  

          int count = 0;
          char pressed;
        
          delay(1000);
          if (client.available()) {
              Serial.println("In while loop checking client"); 
              
              
              while (count != 155) {
                pressed = client.read();
                Serial.write(pressed);
                count ++;
              }
          
              char yes = '1';
              char no = '0';
              if (pressed == yes) {
                    Serial.println("`Pressed");
                    vibrate();
              }
              if (pressed == no) {
                    Serial.println("Not pressed");
           
              }
                count = 0;
        
              } else {
                Serial.println("Client was not available to read bytes");
              }


      } 
      else {
        Serial.println("Vibration client not connected");
      }


          

      client.stop();
 }





void vibrate() {
   // vibration setup
  int counter = 0;
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

  delay(2000);

  // play the effect!
  drv.go();

  delay(2000);

  // play the effect!
  drv.go();

  delay(2000);

  // play the effect!
  drv.go();

  delay(2000);

  // play the effect!
  drv.go();
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
      
