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
#define Yellow  CRGB(255, 200, 0)
#define Blue    CRGB(0, 0, 255)
#define White   CRGB(255, 255, 255)
#define Black   CRGB(0, 0, 0)

// Definim el emoji en una matriu de 16x16
const CRGB emoji[16][16] = {
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
const CRGB prova2[16][16] = {
{ White, White, White, White, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, White, White, White, White},
{ White, White, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, White, White, White},
{ White, White, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, White, White},
{ White, Yellow, Yellow, Black, Black, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Black, Black, Yellow, Yellow, White},
{ Yellow, Yellow, Black, Black, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Black, Black, Yellow, Yellow},
{ Yellow, Yellow, Yellow, Yellow, Black, Black, Yellow, Yellow, Yellow, Yellow, Black, Black, Yellow, Yellow, Yellow, Yellow},
{ Yellow, Yellow, Yellow, Yellow, Black, Black, Yellow, Yellow, Yellow, Yellow, Black, Black, Yellow, Yellow, Yellow, Yellow},
{ Yellow, Yellow, Yellow, Blue, Blue, Blue, Blue, Yellow, Yellow, Blue, Blue, Blue, Blue, Yellow, Yellow, Yellow},
{ Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Black, Black, Black, Black, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow},
{ Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Yellow, Yellow, Yellow},
{ Black, Black, Black, Black, Blue, Blue, White, White, White, White, Blue, Blue, Black, Black, Black, Black},
{ Black, Black, Black, Black, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Black, Black, Black, Black},
{ White, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, White},
{ White, White, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, White, White},
{ White, White, White, White, Black, Black, Black, Black, Black, Black, Black, White, White, White, White, White},
{ White, White, White, White, Black, Black, Black, Black, Black, Black, Black, White, White, White, White, White}
};

void setup() {
    FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalSMD5050);
    FastLED.setBrightness( BRIGHTNESS );
    drawEmoji();
    FastLED.show();
}

void loop() {
    FastLED.show();
    delay(100);
}

void drawEmoji() {
    for (int y = 0; y < MATRIX_HEIGHT; y++) {
        for (int x = 0; x < MATRIX_WIDTH; x++) {
            leds[XY(x, y)] = prova2[y][x];
        }
    }
}


