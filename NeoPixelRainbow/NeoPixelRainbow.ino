#include <Adafruit_NeoPixel.h>

// 5V -> Button, Button Out -> 2 and GND -> 2 Resistor 1kO
#define BUTTON_PIN   2
#define PIXEL_PIN    6  // Digital IO pin connected to the NeoPixels.
#define PIXEL_COUNT 28  // Number of NeoPixels
bool activateMode = 0;
int mode = 0;
int randomNr = 0;


Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  strip.begin(); // Initialize NeoPixel strip object (REQUIRED)
  strip.show();  // Initialize all pixels to 'off'
}

void loop() {
      if (digitalRead(BUTTON_PIN)){
        delay(500); //debounce
        mode+=1;
        if (mode>=(11+1)){mode=0;}
      }

      else if (mode==0){
        rainbow(25);
      }

      else if (mode==1){
        for (int i = 0; i < PIXEL_COUNT; i++){
          strip.setPixelColor(i, 255, 255, 75); // warm white
        }
        strip.show();
      }

      else if (mode==2){
        for (int i = 0; i < PIXEL_COUNT; i++){
          strip.setPixelColor(i, 255, 0, 0); // red
        }
        strip.show();
      }

      else if (mode==3){
        for (int i = 0; i < PIXEL_COUNT; i++){
          strip.setPixelColor(i, 0, 255, 0); // green
        }
        strip.show();
      }

      else if (mode==4){
        for (int i = 0; i < PIXEL_COUNT; i++){
          strip.setPixelColor(i, 0, 0, 255); // blue
        }
        strip.show();
      }

      else if (mode==5){
        for (int i = 0; i < PIXEL_COUNT; i++){
          strip.setPixelColor(i, 0, 255, 255); // light blue
        }
        strip.show();
      }

      else if (mode==6){
        for (int i = 0; i < PIXEL_COUNT; i++){
          strip.setPixelColor(i, 255, 255, 255); // white
        }
        strip.show();
      }

      else if (mode==7){
        for (int i = 0; i < PIXEL_COUNT; i++){
          strip.setPixelColor(i, 250, 95, 237); // light purple
        }
        strip.show();
      }

      else if (mode==8){
        for (int i = 0; i < PIXEL_COUNT; i++){
          strip.setPixelColor(i, 255, 171, 74); // orange
        }
        strip.show();
      }

      else if (mode==9){
        slow(500);
      }

      else if (mode==10){
        randomColor(150);        
      }

      else if (mode==11){
        wipe(100);    
      }
    }


// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void rainbow(int wait) {

  for(long firstPixelHue = 0; firstPixelHue < 3*65536; firstPixelHue += 256) {
    for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
      if (digitalRead(BUTTON_PIN)){
        mode+=1;
        delay(500);
        return;
      }
      // Offset pixel hue by an amount to make one full revolution of the
      // color wheel (range of 65536) along the length of the strip
      // (strip.numPixels() steps):
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
      // optionally add saturation and value (brightness) (each 0 to 255).
      // Here we're using just the single-argument hue variant. The result
      // is passed through strip.gamma32() to provide 'truer' colors
      // before assigning to each pixel:
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
  }
}

void slow(int wait){
  for (unsigned long int i = 0; i < strip.numPixels(); i++){
    if (digitalRead(BUTTON_PIN)){
        mode+=1;
        return;
    }
    randomNr = random(0,255);
    strip.setPixelColor(i, 0, randomNr, randomNr);
  }
  strip.show();
  for (int i = 0; i < wait; i++){
    if (digitalRead(BUTTON_PIN)){
        mode+=1;
        delay(500);
        return;
    }
    delay(1);
  }
}

void randomColor(int wait){
    for (unsigned long int i = 0; i < strip.numPixels(); i++){
      for (int i = 0; i < wait; i++){
        if (digitalRead(BUTTON_PIN)){
          mode+=1;
          delay(500);
          return;
        }
      }
      strip.setPixelColor(i, random(0,255), random(0,255), random(0,255));
      }
    strip.show();
    for (int i = 0; i < wait; i++){
      if (digitalRead(BUTTON_PIN)){
        mode+=1;
        delay(500);
        return;
      }
      delay(1);
    }
}


void wipe(int colorWipeTime){
  if (colorWipe(strip.Color(255,   0,   0), colorWipeTime)){
    return;
  }
  if (colorWipe(strip.Color(255,   255,   0), colorWipeTime)){
    return;
  }
  if (colorWipe(strip.Color(0,   255,   0), colorWipeTime)){
    return;
  }
  if (colorWipe(strip.Color(0,   255,   255), colorWipeTime)){
    return;
  }
  if (colorWipe(strip.Color(0,   0,   255), colorWipeTime)){
    return;
  }
  if (colorWipe(strip.Color(255,   0,   255), colorWipeTime)){
    return;
  }
}

bool colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    for (int i = 0; i < wait; i++){
      if (digitalRead(BUTTON_PIN)){
        mode+=1;
        delay(200);
        return true;
      }
      delay(1);
    }
  }
  return false;
}
