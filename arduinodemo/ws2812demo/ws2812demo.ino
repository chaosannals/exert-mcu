#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#define PIN        19
#define NUMPIXELS 53

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 3000

void setup() {
    Serial.begin(115200);
    while(!Serial);
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif

  pixels.begin();
}

void loop() {
  pixels.clear();

  int v[3] = { 0xFF, 0xFF << 8, 0xFF << 16};

  for(int j =0; j < 3 ; j++ ) { 
    for(int i=0; i<17; i++) {
      Serial.println(v[j]);
      pixels.setBrightness(100);
      pixels.setPixelColor(j * 17 + i, v[j]);
      pixels.show();
    }
  }
  delay(DELAYVAL);
}