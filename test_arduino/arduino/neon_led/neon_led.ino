#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define LED_PIN    13


#define LED_COUNT 72

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);


void setup() {

#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif

  strip.begin();         
  strip.show();            
}

void loop() {
  strip.setBrightness(100); 
  //(r,b,g),delay)
  back_colorWipe(strip.Color(255,   160,   0), 50); 
}

void colorWipe(uint32_t color, int wait) {
   for(int i=0; i<strip.numPixels(); i++) { 
     strip.setPixelColor(i, color);         
     strip.show();                          
     delay(wait);                           
   }  
}

void back_colorWipe(uint32_t color, int wait) {
   for(int i=strip.numPixels(); i>= 0; --i) { 
     strip.setPixelColor(i, color);         
     strip.show();                          
     delay(wait);                           
   }  
}

