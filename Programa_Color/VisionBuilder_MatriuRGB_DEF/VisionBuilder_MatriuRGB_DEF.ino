#include <FastLED.h>

#define LED_PIN     3   // Pin on està conectat el DIN de la matriu
#define MATRIX_WIDTH  16
#define MATRIX_HEIGHT 16
#define NUM_LEDS (MATRIX_WIDTH * MATRIX_HEIGHT)
#define BRIGHTNESS 64

CRGB leds[NUM_LEDS];

// Mapeig de la matriu (dependrà de la connexió)
#define XY(x, y) ((y) * MATRIX_WIDTH + (x))

// Definim els colors bàsics
#define YELLOW  CRGB(255, 200, 0)
#define BLUE    CRGB(0, 0, 255)
#define WHITE   CRGB(255, 255, 255)
#define BLACK   CRGB(0, 0, 0)


const CRGB emojiblank[16][16];
// Arduino server for Color LEGO_Arduino.vbai 

const byte numChars = 255;
char receivedChars[numChars];   // an array to store the received data

boolean newData = false;
boolean newColor = false;
byte ColorPantalla[3] = {100,255,0};

void setup() {
    Serial.begin(9600);
    FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setBrightness( BRIGHTNESS );
    drawEmoji();
    FastLED.show();
    pinMode(8,INPUT_PULLUP);
}

void loop() {
  buttonPres();
  recvWithEndMarker();
  if (newData == true){
    FastLED.show();
    newData = false;
    newColor = false; 
  }   
}

// ********************* Funcions

void drawEmoji() {
    for (int y = 0; y < MATRIX_HEIGHT; y++) {
        for (int x = 0; x < MATRIX_WIDTH; x++) {
            leds[XY(x, y)] = WHITE;//emojiblank[y][x];
        }
    }
}

void recvWithEndMarker() {
  static int pixelIndex = 0;         
  static byte rgb[3];                
  static byte colorPos = 0;          
  char rc;

  while (Serial.available() > 0) {
    rc = Serial.read();
    rgb[colorPos] = (byte)rc;
    colorPos++;

    if (colorPos == 3) { 
      if (pixelIndex < NUM_LEDS) {
        leds[pixelIndex] = CRGB(rgb[0], rgb[1], rgb[2]);
        pixelIndex++;
      }
      colorPos = 0;

      
      FastLED.show(); 
    }

    
    if (pixelIndex >= NUM_LEDS) {
      pixelIndex = 0;
    }
  }
}

void buttonPres(){
  if(digitalRead(8)==LOW){
     Serial.write('S');
     delay(500);
  }
}


