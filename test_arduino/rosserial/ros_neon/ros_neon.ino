#include <Adafruit_NeoPixel.h>
#include <ros.h>
#include <std_msgs/Int32MultiArray.h>

#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define LED_PIN    12
#define LED_COUNT 32

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
ros::NodeHandle nh;

unsigned long pixelPrevious = 0;
unsigned long patternPrevious = 0;
int patternCurrent = 0;
int patternInterval = 5000;
int pixelInterval = 50;
int pixelQueue = 0;
int pixelCycle = 0;
uint16_t pixelCurrent = 0;
uint16_t pixelNumber = LED_COUNT;


void messageCb(const std_msgs::Int32MultiArray& msg) {
  int function = msg.data[0];
  int brightness = msg.data[1];
  int red = msg.data[2];
  int green = msg.data[3];
  int blue = msg.data[4];
  int delay_msec = msg.data[5];

  strip.setBrightness(brightness);

  if (function == 0) {
    colorWipe(strip.Color(red, green, blue), delay_msec);
  } else if (function == 1) {
    back_colorWipe(strip.Color(red, green, blue), delay_msec);
  }
}

ros::Subscriber<std_msgs::Int32MultiArray> sub("/mcu/neon", &messageCb);

void setup() {
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif

  strip.begin();
  strip.show();

  nh.initNode();
  nh.subscribe(sub);
}

void loop() {
  nh.spinOnce();
}

void colorWipe(uint32_t color, int wait) {
  if(pixelInterval != wait)
    pixelInterval = wait;

  for (int i=0; i<LED_COUNT; i++){
    strip.setPixelColor(i, color);
  }
  strip.show();
  pixelCurrent++;
  if(pixelCurrent >= pixelNumber)
    pixelCurrent = 0;
}

void back_colorWipe(uint32_t color, int wait) {
  if(pixelInterval != wait)
    pixelInterval = wait;

  for (int i = LED_COUNT; i >= 0; --i) {
    strip.setPixelColor(i, color);
  }
  strip.show();
  pixelCurrent++;
  if(pixelCurrent >= pixelNumber)
    pixelCurrent = 0;
}


rostopic pub -1 /mcu/neon std_msgs/Int32MultiArray "layout:
  dim:
  - label: '/function/brightness/R/G/B/delay_msec'
    size: 6
    stride: 1
  data_offset: 0
data: [0, 255, 255, 0, 0, 50]"