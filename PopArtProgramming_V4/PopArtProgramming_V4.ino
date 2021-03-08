#include <Bounce2.h>
#include <Adafruit_NeoPixel.h>
#include "frames.h"
    Adafruit_NeoPixel strip(24, 0);
#define butPin 1
// Create Bounce/Button Object (From Bounce2 Example)
Bounce2::Button button = Bounce2::Button();
char colors[10][3] {
  {0, 0, 0},
  {255, 255, 0},
  {0, 0, 255},
  {255, 0, 0},
  {255, 255, 180},
  {255, 51, 153},
  {0, 255, 255},
  {255, 153, 51},
  {102, 255, 51},
  {255, 30, 30},
};
char whichFrame = 0;
char whichFrame2 = 0;
char pixAddress;
char switchVal = 0;
char no = 0;
char rain = 0;
char snakeVal = 0;
unsigned long startMillis;
unsigned long currentMillis;
const unsigned long period = 500;
byte brightness = 0;       
byte increment = 1;       
char bright = 200;
void setup() {
  strip.begin();
  strip.setBrightness(20);
  button.attach(butPin, INPUT );
  button.interval(5);
  button.setPressedState(LOW);
  startMillis = millis();
  strip.clear();
}

void loop() {
  button.update();
  if (button.pressed()) {
    switchVal = (switchVal + 1) % 6;
  }
    switch (switchVal) {
      case 0:
        strip.clear();
        for (char i = 0; i < strip.numPixels(); i++) {
          strip.setPixelColor(i, 0,0,0);                   
        }
        strip.show();       
        break;
      case 1:
        no=0;
        rain=0;
        whichFrame = 0;
        whichFrame2 = 0;
        turnOn();
        break;
      case 2:
        staticImg();
        break;
      case 3:
        snake();
        brightness=0;
        break;
      case 4:
          if (rain == 0){
          rainbow(1);
          rain = (rain + 1);
        }
        break;
      case 5:
        gameOver();
        break;
    }
  }


void staticImg() {
  strip.setBrightness(bright-100);
  strip.clear();
  for (char i = 0; i < strip.numPixels(); i++) {
    char pixAddress = i;
    char whichColor = simp[0][i];
    char red = colors[whichColor][0];
    char green = colors[whichColor][1];
    char blue = colors[whichColor][2];
      strip.setPixelColor(pixAddress, red, green, blue);
  }
  strip.show();
}

void gameOver() {
  strip.clear();
  strip.setBrightness(bright);
  for (int i = 0; i < 3; i++) {
    char pixAddress = pixelMapGame[i];
    char whichColor = gameOverAnim[whichFrame2][i];
    char red = colors[whichColor][0];
    char green = colors[whichColor][1];
    char blue = colors[whichColor][2];
    strip.setPixelColor(pixAddress, red, green, blue);
  }
  strip.show();
  delay(600);
  whichFrame2++;
  if(whichFrame2 == 4){
    switchVal++;
  }
}

void turnOn(){
   strip.clear();
   currentMillis = millis();
  for (int i = 0; i < strip.numPixels(); i++) {
    char pixAddress = i;
    char whichColor = turnOnAnim[0][i];
    char red = colors[whichColor][0];
    char green = colors[whichColor][1];
    char blue = colors[whichColor][2];
    strip.setPixelColor(pixAddress, red, green, blue);
    strip.setBrightness(brightness);
  }
 if (currentMillis - startMillis >= 10){
    if(brightness < 250){
      brightness += increment;
    }
  strip.show();
  startMillis = currentMillis;
 }
}

void snake() {
   strip.setBrightness(bright);
   strip.clear();
   currentMillis = millis();
  for (int i = 0; i < 11; i++) {
    char pixAddress = pixelMapSnake[i];
    char whichColor = snakeAnim[whichFrame][i];
    char red = colors[whichColor][0];
    char green = colors[whichColor][1];
    char blue = colors[whichColor][2];
    strip.setPixelColor(pixAddress, red, green, blue);
  }
 if (currentMillis - startMillis >= period){
  strip.show();
  startMillis = currentMillis;
  whichFrame = (whichFrame +1) % 6;
 }
}

void rainbow(char wait) {
  strip.setBrightness(bright);
  strip.clear();
  currentMillis = millis();
  for (long firstPixelHue = 0; firstPixelHue < 3 * 65536; firstPixelHue += 256) {
    for (char i = 0; i < strip.numPixels(); i++) {
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
  }
}
