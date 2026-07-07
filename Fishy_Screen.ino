#include <Arduino.h>
#include <Adafruit_GC9A01A.h>
#include <Adafruit_GFX.h>
#include <SPI.h>
#include <WiFi.h> 
#include <PubSubClient.h> 

//MQTT information
const char* MQTT_HOST = "23c7c9e727f2450999e63ac8d5f5eda0.s1.eu.hivemq.cloud";
const int   MQTT_PORT = 8883;
const char* MQTT_USER = "FishFish"
const char* MQTT_PASS = "BlubBlubBlub00"

//screen constants
#define TFT_SCLK 8   //D8, GPIO8
#define TFT_COPI 10  //D10, GPIO10
#define TFT_RST 5    //D3, GPIO5
#define TFT_DC 4     //D2, GPIO4
#define TFT_CS 3     //D1, GPIO3
#define TFT_BL 2     //D0, GPIO2

//motion sensor
#define MOTION 20  //D7, GPIO20

//home, away
#define DND_BUTTON 7     //D5, GPIO7
#define PRESENCE_BUTTON 6  //D4, GPIO6

#define DND -1
#define HOME 1
#define AWAY 0

Adafruit_GC9A01A tft(TFT_CS, TFT_DC, TFT_COPI, TFT_SCLK, TFT_RST, -1);

//If we are just home, show coral reef fish
void showHome(){
  tft.fillScreen(0x0000); //Black
  tft.setTextColor(0xFFFF); //White
  tft.setTextSize(2);
  tft.setCursor(60, 110);
  tft.print("AT HOME");
}

//If we are home + DND, show jellyfish
void showDND(){
  tft.fillScreen(0x0000); //Black
  tft.setTextColor(0xFFFF); //White
  tft.setTextSize(2);
  tft.setCursor(60, 110);
  tft.print("DND ON");
} 

//If we are away, show fisherman. Clicking the DND button when you are away does not do anything 
void showAway(){
  tft.fillScreen(0x0000); //Black
  tft.setTextColor(0xFFFF); //White
  tft.setTextSize(2);
  tft.setCursor(60, 110);
  tft.print("AWAY");
  
}

void setup() {
  client.setServer(MQTT_HOST, MQTT_PORT);
  pinMode(MOTION, INPUT_PULLDOWN);
  pinMode(TFT_BL, OUTPUT);

  pinMode(DND_BUTTON, INPUT_PULLDOWN);
  pinMode(PRESENCE_BUTTON, INPUT_PULLDOWN);

  digitalWrite(TFT_BL, HIGH);

  tft.begin();
  tft.fillScreen(GC9A01A_BLACK);
  Serial.begin(9600);
}

bool lastMotionState = false;
bool firstRun = true;

bool presence_state = true;
bool dnd_state = false;

void loop() {
  bool presence = digitalRead(PRESENCE_BUTTON);
  bool dnd = digitalRead(DND_BUTTON);

//we only want to run this code when either button is pressed
  if (presence || dnd) { 
    if (presence) {
      presence_state = !presence_state;
      Serial.println("Grey button pressed");
    }
    if (dnd) {
      dnd_state = !dnd_state;
      Serial.println("Red button pressed");
    }
    
    if (presence_state && !dnd_state) {
      showHome();
    }
    
    else if (presence_state && dnd_state) {
      showDND();
    }
    
    else { //Away + DND or Away + !DND
      showAway();
    }
  }
}



//motion stuffs
/*
bool motionState = digitalRead(MOTION);
  
  if (motionState != lastMotionState || firstRun) {
    if (motionState) {
      tft.setTextColor(GC9A01A_WHITE);
      tft.setTextSize(2);
      tft.setCursor(60, 110);
      tft.print("BUBBATRON");

      delay(2000);
    } else {
      tft.setTextColor(GC9A01A_BLACK);
      tft.setTextSize(2);
      tft.setCursor(60, 110);
      tft.print("BUBBATRON");
    }

    lastMotionState = motionState;
    firstRun = false;
} 

  delay(50);
*/
