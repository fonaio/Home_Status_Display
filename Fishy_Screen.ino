#include <Arduino.h>
#include <Adafruit_GC9A01A.h>
#include <Adafruit_GFX.h>
#include <SPI.h>

//screen constants
#define TFT_SCLK 8 //D8, GPIO8
#define TFT_COPI 10 //D10, GPIO10
#define TFT_RST 5 //D3, GPIO5
#define TFT_DC 4 //D2, GPIO4
#define TFT_CS 3 //D1, GPIO3
#define TFT_BL 2 //D0, GPIO2

//motion sensor
#define MOTION 20 //D7, GPIO20

//home
#define DND 7 //D5, GPIO7
#define STATUS 6 //D4, GPIO6


void setup() {
  // put your setup code here, to run once:
  Adafruit_GC9A01A tft(TFT_CS, TFT_DC, TFT_COPI, TFT_SCLK, TFT_RST, -1);
  tft.begin();
  tft.fillScreen(GC9A01A_BLACK);
  tft.setTextColor(GC9A01A_WHITE);
  tft.setTextSize(2);
  tft.setCursor(60,110);
  tft.print("BUBBATRON");
}

void loop() {
  // put your main code here, to run repeatedly:

}
