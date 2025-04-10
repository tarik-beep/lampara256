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



// Definim el emoji en una matriu de 16x16
const CRGB emoji1[16][16] = {
  {WHITE, WHITE, WHITE, WHITE, WHITE, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, WHITE, WHITE, WHITE, WHITE, WHITE},
  {WHITE, WHITE, WHITE, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, WHITE, WHITE, WHITE},
  {WHITE, WHITE, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, WHITE, WHITE},
  {WHITE, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, WHITE},
  {WHITE, YELLOW, YELLOW, BLACK, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, BLACK, YELLOW, YELLOW, WHITE},
  {YELLOW, YELLOW, BLACK, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, BLACK, YELLOW, YELLOW},
  {YELLOW, BLACK, YELLOW, BLACK, BLACK, BLACK, YELLOW, YELLOW, YELLOW, YELLOW, BLACK, BLACK, BLACK, YELLOW, BLACK, YELLOW},
  {YELLOW, YELLOW, YELLOW, BLUE, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, BLUE, YELLOW, YELLOW, YELLOW},
  {YELLOW, YELLOW, BLUE, BLUE, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLUE, BLUE, YELLOW, YELLOW},
  {YELLOW, BLUE, BLUE, BLUE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, BLUE, BLUE, BLUE, YELLOW},
  {BLUE, BLUE, BLUE, BLUE, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLUE, BLUE, BLUE, BLUE},
  {BLUE, BLUE, BLUE, BLUE, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLUE, BLUE, BLUE, BLUE},
  {WHITE, BLUE, BLUE, YELLOW, YELLOW, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, YELLOW, YELLOW, BLUE, BLUE, WHITE},
  {WHITE, WHITE, WHITE, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, WHITE, WHITE, WHITE},
  {WHITE, WHITE, WHITE, WHITE, WHITE, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, WHITE, WHITE, WHITE, WHITE, WHITE},
  {WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, YELLOW, YELLOW, YELLOW, YELLOW, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE}
};
const CRGB emojiblank[16][16];
// Arduino server for Color LEGO_Arduino.vbai 

const byte numChars = 255;
char receivedChars[numChars];   // an array to store the received data

boolean newData = false;
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
  static byte nbit = 0;
  static byte nbyte = 0;
  char endMarker = '\n';
  char rc;
   
  while (Serial.available() > 0 && newData == false) {
    rc = Serial.read();
    //if (rc != endMarker)
    if (nbyte !=32)
    {
      for (int i = 0; i<=7 ; i++)
      {
        int bitValue = (rc >> i) & 1;
        if (bitValue == 1)
        {
          leds[nbit+(8*nbyte)] = CRGB::WHITE;
        }
        else
        {
          leds[nbit+(8*nbyte)] = CRGB::BLACK;
        }
        nbit++;
      }
      nbit = 0;
      nbyte++;      
    }
    if (nbyte == 32) {
      //receivedChars[ndx] = '\0'; // terminate the string
      nbyte = 0;
      newData = true;
    }
  }
}

void buttonPres(){
  if(digitalRead(8)==LOW){
     Serial.write('S');
     delay(500);
  }
}


