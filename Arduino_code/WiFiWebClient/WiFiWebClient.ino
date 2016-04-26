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


#include <SPI.h>
#include <Adafruit_WINC1500.h>

#include <Wire.h>
#include "Adafruit_DRV2605.h"



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


char ssid[] = "Shabahaba";     //  your network SSID (name)
char pass[] = "hellowassup";    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;                // your network key Index number (needed only for WEP)


Adafruit_DRV2605 drv;

int pin1 = 6;
volatile int state = LOW;

long lastDebounceTime = 0;
long debounceDelay = 300;
int lastButton = LOW;
int buttonState;
bool connection;

long lastButtonPress = 0;

int status = WL_IDLE_STATUS;
// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
//IPAddress server(141,101,112,175);  // numeric IP for test page (no DNS)
char server[] = "e5446b2b.ngrok.io";    // domain name for test page (using DNS)


// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
Adafruit_WINC1500Client client;
Adafruit_WINC1500Client client2;

void setup() {
#ifdef WINC_EN
  pinMode(WINC_EN, OUTPUT);
  digitalWrite(WINC_EN, HIGH);
#endif

//  while (!Serial);  // required for Flora & Micro
  delay(500);
  Serial.begin(9600);
  pinMode(pin1, INPUT_PULLUP);

// vibration testing
  Serial.println("DRV test");
  drv.begin();
  
  drv.selectLibrary(1);
  
  // I2C trigger by sending 'go' command 
  // default, internal trigger when sending GO command
  drv.setMode(DRV2605_MODE_INTTRIG); 
  

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

  check();
}



uint8_t effect = 1;

void loop() {
  // if there are incoming bytes available
  // from the server, read them and print them:
  int count = 0;
  
  
  char pressed;
  while (client.available()) {
    while (count != 155) {
      pressed = client.read();
      Serial.write(pressed);
      count ++;
    }

    char yes = '1';
    char no = '0';
    if (pressed == yes) {
          Serial.println("Pressed");
          delay(1000);
          vibrate();
    }
    if (pressed == no) {
          Serial.println("Not pressed");
 
    }
      count = 0;

  }

  check();

  
  
  if (digitalRead(pin1) == LOW && (millis() - lastDebounceTime) > debounceDelay) {
        long pressed = millis();
        Serial.println("------ BUTTON PRESSED ------");
        post();
        lastDebounceTime = millis();
//  } else {
//        Serial.println("HIGH");


  }



//vibration testing


//   if the server's disconnected, stop the client:
//  if (!client.connected()) {
//    Serial.println();
//    Serial.println("disconnecting from server.");
//    client.stop();
////
////    // do nothing forevermore:
////    while (true);
////  }
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

void post()
{
      if (client.connect(server, 80)) 
      {
          Serial.println("Connected");
          Serial.println("Making Post Request");

          // Make a POST HTTP request:

          String data = "love";
          // For testing
          client.print("POST ");
          client.print("/stressed");
          client.println(" HTTP/1.1");
          client.print("Host: "); client.println(server);
          client.println("Connection: close");
          client.println("User-Agent: Arduino/1.0");
          client.print("Content-Length: ");
          client.println(data.length());
          client.println();
          client.print(data);
          client.println();                           

      }

 
}

void check()
{

//      char server2[] = "http://e5446b2b.ngrok.io/pressed";
      
      if (client.connect(server, 80)) 
      {
          Serial.println("Connected");
          Serial.println("Making Post Request");

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

          }
      }





     void vibrate() 
     {

        Serial.print("Vibrating");

          // set the effect to play
          drv.setWaveform(0, 86);  // play effect 
          drv.setWaveform(1, 0);       // end waveform
        
          // play the effect!
          drv.go();
        
          // wait a bit
          delay(3000);
        
//          effect++;
//          if (effect > 117) effect = 1;
     }

      

 

