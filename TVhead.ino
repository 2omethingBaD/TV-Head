#include <Arduino.h>
#include <FastLED.h>
#include <EasyButton.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define led_pin 4
#define button_one_pin 2
#define button_two_pin 3
#define button_three_pin 5
#define button_four_pin 6
#define ind_pin 8
#define BAUDRATE 115200
#define num_led 126

CRGB leds[num_led];
EasyButton button_one(button_one_pin);
EasyButton button_two(button_two_pin);
EasyButton button_three(button_three_pin);
EasyButton button_four(button_four_pin);

long remTime = 0;
bool isBlinking = false;
uint8_t pattern_counter = 1;


//eye open
const long ledarray0[] PROGMEM = {
			0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
      0x00000000, 0x00000000, 0x00000000, 0x00402040, 0x00402040, 0x00402040, 0x00000000, 0x00000000, 0x00000000, 
      0x00000000, 0x00000000, 0x00402040, 0x00FF6FFF, 0x00FF6FFF, 0x00FF6FFF, 0x00402040, 0x00000000, 0x00000000, 
      0x00000000, 0x00402040, 0x00FF6FFF, 0x00000000, 0x00000000, 0x00000000, 0x00FF6FFF, 0x00402040, 0x00000000, 
      0x00000000, 0x00FF6FFF, 0x00000000, 0x00000000, 0x00FF17FA, 0x00000000, 0x00000000, 0x00FF6FFF, 0x00000000, 
      0x00FF6FFF, 0x00000000, 0x00000000, 0x00000000, 0x00FF17FA, 0x00000000, 0x00000000, 0x00000000, 0x00FF6FFF, 
      0x00FF6FFF, 0x00000000, 0x00000000, 0x00000000, 0x00FF17FA, 0x00000000, 0x00000000, 0x00000000, 0x00FF6FFF, 
      0x00000000, 0x00FF6FFF, 0x00000000, 0x00000000, 0x00FF00FF, 0x00000000, 0x00000000, 0x00FF6FFF, 0x00000000, 
      0x00000000, 0x00402040, 0x00FF6FFF, 0x00000000, 0x00000000, 0x00000000, 0x00FF6FFF, 0x00402040, 0x00000000, 
      0x00000000, 0x00000000, 0x00402040, 0x00FF6FFF, 0x00FF6FFF, 0x00FF6FFF, 0x00402040, 0x00000000, 0x00000000, 
      0x00000000, 0x00000000, 0x00000000, 0x00402040, 0x00402040, 0x00402040, 0x00000000, 0x00000000, 0x00000000, 
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
      0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
};
//judgmental eye
const long ledarray5[] PROGMEM = {
				0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
				0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
				0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
				0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
				0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
				0x00000000, 0x00402040, 0x00402040, 0x00402040, 0x00402040, 0x00402040, 0x00402040, 0x00402040, 0x00000000, 
				0x00FF6FFF, 0x00FF6FFF, 0x00FF6FFF, 0x00FF6FFF, 0x00FF6FFF, 0x00FF6FFF, 0x00FF6FFF, 0x00FF6FFF, 0x00FF6FFF, 
				0x00FF6FFF, 0x00000000, 0x00000000, 0x00000000, 0x00FF17FA, 0x00000000, 0x00000000, 0x00000000, 0x00FF6FFF, 
				0x00000000, 0x00FF6FFF, 0x00000000, 0x00000000, 0x00FF00FF, 0x00000000, 0x00000000, 0x00FF6FFF, 0x00000000, 
				0x00000000, 0x00402040, 0x00FF6FFF, 0x00000000, 0x00000000, 0x00000000, 0x00FF6FFF, 0x00402040, 0x00000000, 
				0x00000000, 0x00000000, 0x00402040, 0x00FF6FFF, 0x00FF6FFF, 0x00FF6FFF, 0x00402040, 0x00000000, 0x00000000, 
				0x00000000, 0x00000000, 0x00000000, 0x00402040, 0x00402040, 0x00402040, 0x00000000, 0x00000000, 0x00000000, 
				0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
				0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
};
//X eye
const long ledarray7[] PROGMEM = {
				0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
				0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
				0x00FF6FFF, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00FF6FFF, 
				0x00FF6FFF, 0x00FF6FFF, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00FF6FFF, 0x00FF6FFF, 
				0x00000000, 0x00FF6FFF, 0x00FF6FFF, 0x00000000, 0x00000000, 0x00000000, 0x00FF6FFF, 0x00FF6FFF, 0x00000000, 
				0x00000000, 0x00000000, 0x00FF6FFF, 0x00FF6FFF, 0x00000000, 0x00FF6FFF, 0x00FF6FFF, 0x00000000, 0x00000000, 
				0x00000000, 0x00000000, 0x00000000, 0x00FF6FFF, 0x00FF6FFF, 0x00FF6FFF, 0x00000000, 0x00000000, 0x00000000, 
				0x00000000, 0x00000000, 0x00000000, 0x00FF6FFF, 0x00FF6FFF, 0x00FF6FFF, 0x00000000, 0x00000000, 0x00000000, 
				0x00000000, 0x00000000, 0x00FF6FFF, 0x00FF6FFF, 0x00000000, 0x00FF6FFF, 0x00FF6FFF, 0x00000000, 0x00000000, 
				0x00000000, 0x00FF6FFF, 0x00FF6FFF, 0x00000000, 0x00000000, 0x00000000, 0x00FF6FFF, 0x00FF6FFF, 0x00000000, 
				0x00FF6FFF, 0x00FF6FFF, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00FF6FFF, 0x00FF6FFF, 
				0x00FF6FFF, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00FF6FFF, 
				0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
				0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
};
//UwU eye
const long ledarray6[] PROGMEM = {
				0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
				0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
				0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
				0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00402040, 0x00402040, 0x00402040, 0x00000000, 0x00000000, 0x00000000, 
				0x00000000, 0x00000000, 0x00402040, 0x00FF6FFF, 0x00FF6FFF, 0x00FF6FFF, 0x00402040, 0x00000000, 0x00000000, 
				0x00000000, 0x00402040, 0x00FF6FFF, 0x00000000, 0x00000000, 0x00000000, 0x00FF6FFF, 0x00402040, 0x00000000, 
				0x00000000, 0x00FF6FFF, 0x00000000, 0x00FF17FA, 0x00000000, 0x00000000, 0x00000000, 0x00FF6FFF, 0x00000000, 
				0x00FF6FFF, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00FF17FA, 0x00000000, 0x00000000, 0x00FF6FFF,  
				0x00FF6FFF, 0x00FF6FFF, 0x00FF6FFF, 0x00FF6FFF, 0x00FF6FFF, 0x00FF6FFF, 0x00FF6FFF, 0x00FF6FFF, 0x00FF6FFF, 
				0x00000000, 0x00402040, 0x00402040, 0x00402040, 0x00402040, 0x00402040, 0x00402040, 0x00402040, 0x00000000,  
				0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
				0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
				0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
};
//eye closing frames
//first frame
const long ledarray1[] PROGMEM = {
				0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
				0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
				0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
				0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
				0x00000000, 0x00402040, 0x00402040, 0x00402040, 0x00402040, 0x00402040, 0x00402040, 0x00402040, 0x00000000, 
				0x00000000, 0x00FF6FFF, 0x00FF6FFF, 0x00FF6FFF, 0x00FF6FFF, 0x00FF6FFF, 0x00FF6FFF, 0x00FF6FFF, 0x00000000, 
				0x00FF6FFF, 0x00000000, 0x00000000, 0x00000000, 0x00FF17FA, 0x00000000, 0x00000000, 0x00000000, 0x00FF6FFF, 
				0x00FF6FFF, 0x00000000, 0x00000000, 0x00000000, 0x00FF17FA, 0x00000000, 0x00000000, 0x00000000, 0x00FF6FFF, 
				0x00000000, 0x00FF6FFF, 0x00000000, 0x00000000, 0x00FF00FF, 0x00000000, 0x00000000, 0x00FF6FFF, 0x00000000, 
				0x00000000, 0x00402040, 0x00FF6FFF, 0x00000000, 0x00000000, 0x00000000, 0x00FF6FFF, 0x00402040, 0x00000000, 
				0x00000000, 0x00000000, 0x00402040, 0x00FF6FFF, 0x00FF6FFF, 0x00FF6FFF, 0x00402040, 0x00000000, 0x00000000, 
				0x00000000, 0x00000000, 0x00000000, 0x00402040, 0x00402040, 0x00402040, 0x00000000, 0x00000000, 0x00000000, 
				0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
				0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
};
//second frame
const long ledarray2[] PROGMEM = {
				0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
				0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
				0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
				0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
				0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
				0x00000000, 0x00402040, 0x00402040, 0x00000000, 0x00000000, 0x00000000, 0x00402040, 0x00402040, 0x00000000, 
				0x00FF6FFF, 0x00FF6FFF, 0x00FF6FFF, 0x00402040, 0x00402040, 0x00402040, 0x00FF6FFF, 0x00FF6FFF, 0x00FF6FFF, 
				0x00FF6FFF, 0x00000000, 0x00000000, 0x00FF6FFF, 0x00FF6FFF, 0x00FF6FFF, 0x00000000, 0x00000000, 0x00FF6FFF, 
				0x00000000, 0x00FF6FFF, 0x00000000, 0x00000000, 0x00FF00FF, 0x00000000, 0x00000000, 0x00FF6FFF, 0x00000000, 
				0x00000000, 0x00402040, 0x00FF6FFF, 0x00000000, 0x00000000, 0x00000000, 0x00FF6FFF, 0x00402040, 0x00000000, 
				0x00000000, 0x00000000, 0x00402040, 0x00FF6FFF, 0x00FF6FFF, 0x00FF6FFF, 0x00402040, 0x00000000, 0x00000000, 
				0x00000000, 0x00000000, 0x00000000, 0x00402040, 0x00402040, 0x00402040, 0x00000000, 0x00000000, 0x00000000, 
				0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
				0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
};
//third frame
const long ledarray3[] PROGMEM = {
				0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
				0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
				0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
				0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
				0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
				0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
				0x00FF6FFF, 0x00402040, 0x00402040, 0x00000000, 0x00000000, 0x00000000, 0x00402040, 0x00402040, 0x00FF6FFF, 
				0x00FF6FFF, 0x00FF6FFF, 0x00FF6FFF, 0x00402040, 0x00402040, 0x00402040, 0x00FF6FFF, 0x00FF6FFF, 0x00FF6FFF, 
				0x00000000, 0x00FF6FFF, 0x00000000, 0x00FF6FFF, 0x00FF6FFF, 0x00FF6FFF, 0x00000000, 0x00FF6FFF, 0x00000000, 
				0x00000000, 0x00402040, 0x00FF6FFF, 0x00000000, 0x00000000, 0x00000000, 0x00FF6FFF, 0x00402040, 0x00000000, 
				0x00000000, 0x00000000, 0x00402040, 0x00FF6FFF, 0x00FF6FFF, 0x00FF6FFF, 0x00402040, 0x00000000, 0x00000000, 
				0x00000000, 0x00000000, 0x00000000, 0x00402040, 0x00402040, 0x00402040, 0x00000000, 0x00000000, 0x00000000, 
				0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
				0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
};
//forth frame/ eye closed
const long ledarray4[] PROGMEM = {
				0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
				0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
				0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
				0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
				0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
				0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
				0x00FF6FFF, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00FF6FFF, 
				0x00FF6FFF, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00FF6FFF, 
				0x00000000, 0x00FF6FFF, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00FF6FFF, 0x00000000, 
				0x00000000, 0x00402040, 0x00FF6FFF, 0x00000000, 0x00000000, 0x00000000, 0x00FF6FFF, 0x00402040, 0x00000000, 
				0x00000000, 0x00000000, 0x00402040, 0x00FF6FFF, 0x00FF6FFF, 0x00FF6FFF, 0x00402040, 0x00000000, 0x00000000, 
				0x00000000, 0x00000000, 0x00000000, 0x00402040, 0x00402040, 0x00402040, 0x00000000, 0x00000000, 0x00000000, 
				0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
				0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
};


void onB1Press()
{
  pattern_counter = 1;
}
void onB1DPress()
{
  pattern_counter = 11;
}
void onB2Press()
{
  pattern_counter = 2;
}
void onB2DPress()
{
  pattern_counter = 22;
}
void onB3Press()
{
  pattern_counter = 3;
}
void onB3DPress()
{
  pattern_counter = 33;
}
void onB4Press()
{
  pattern_counter = 4;
}


void setup()
{     
  pinMode(ind_pin, OUTPUT);           
  FastLED.addLeds<WS2812B, led_pin, GRB>(leds, num_led);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);
  Serial.begin(BAUDRATE);

  button_one.begin();
  button_two.begin();
  button_three.begin();
  button_four.begin();
  
  button_one.onPressed(onB1Press);
  button_one.onSequence(2, 2000, onB1DPress);
  button_two.onPressed(onB2Press);
  button_two.onSequence(2, 2000, onB2DPress);
  button_three.onPressed(onB3Press);
  button_three.onSequence(2, 2000, onB3DPress);
  button_four.onPressed(onB4Press);
}


void loop()
{
  digitalWrite(ind_pin, HIGH);
  button_one.read();
  button_two.read();
  button_three.read();
  button_four.read();

  switch(pattern_counter) 
  {
    case 11:
      openEye();
      break;
    case 1:
      blink();
      break;
    case 22:
      squintEye();
      break;
    case 2:
      squint();
      break;
    case 3:
      xEye();
      break;
    case 33:
      UwUEye();
      break;
    case 4:
      off();
      break;
  }
}


//static open eye
void openEye()
{
  while(pattern_counter == 11)
  {
    for(int i = 0; i < num_led; i++)
    {
      leds[i] = pgm_read_dword(&(ledarray0[i]));
      button_one.read();
      button_two.read();
      button_three.read();
      button_four.read();
    }FastLED.show();
  }
}


//static squinted eye
void squintEye()
{
  while(pattern_counter == 22)
  {
    for(int i = 0; i < num_led; i++)
    {
      leds[i] = pgm_read_dword(&(ledarray5[i]));
      button_one.read();
      button_two.read();
      button_three.read();
      button_four.read();
    }FastLED.show();
  }
}


//static X eye
void xEye()
{
  while(pattern_counter == 3)
  {
    for(int i = 0; i < num_led; i++)
    {
      leds[i] = pgm_read_dword(&(ledarray7[i]));
      button_one.read();
      button_two.read();
      button_three.read();
      button_four.read();
    }FastLED.show();
  }
}


//static UwU eye
void UwUEye()
{
  while(pattern_counter == 33)
  {
    for(int i = 0; i < num_led; i++)
    {
      leds[i] = pgm_read_dword(&(ledarray6[i]));
      button_one.read();
      button_two.read();
      button_three.read();
      button_four.read();
    }FastLED.show();
  }
}


//screen off
void off()
{
  while(pattern_counter == 4)
  {
    for(int i = 0; i<num_led; i++) leds[i] = CRGB(0,0,0);
    button_one.read();
    button_two.read();
    button_three.read();
    button_four.read();
    FastLED.show();
  }
}


//idle animation /blink animation
void blink()
{ 
  while(pattern_counter == 1)
  {
    button_one.read();
    button_two.read();
    button_three.read();
    button_four.read();

    if(!isBlinking)
    {
      if((millis()- remTime) >= 0)
      {
        for(int i = 0; i < num_led; i++)
        {
          button_one.read();
          button_two.read();
          button_three.read();
          button_four.read();
          leds[i] = pgm_read_dword(&(ledarray0[i]));
        }FastLED.show();
        remTime = millis();
        isBlinking = true;
      }
    }

    else
    {
      if((millis()- remTime) >= 6000)
      {
        for(int i = 0; i < num_led; i++)
        {
          button_one.read();
          button_two.read();
          button_three.read();
          button_four.read();
          leds[i] = pgm_read_dword(&(ledarray1[i]));
        }FastLED.delay(80);
      
        for(int i = 0; i < num_led; i++)
        {
          button_one.read();
          button_two.read();
          button_three.read();
          button_four.read();
          leds[i] = pgm_read_dword(&(ledarray2[i]));
        }FastLED.delay(80);
        
        for(int i = 0; i < num_led; i++)
        {
          button_one.read();
          button_two.read();
          button_three.read();
          button_four.read();
          leds[i] = pgm_read_dword(&(ledarray3[i]));
        }FastLED.delay(80);
        
        for(int i = 0; i < num_led; i++)
        {
          button_one.read();
          button_two.read();
          button_three.read();
          button_four.read();
          leds[i] = pgm_read_dword(&(ledarray4[i]));
        }FastLED.delay(60);

        for(int i = 0; i < num_led; i++)
        {
          button_one.read();
          button_two.read();
          button_three.read();
          button_four.read();
          leds[i] = pgm_read_dword(&(ledarray2[i]));
        }FastLED.delay(60);

        for(int i = 0; i < num_led; i++)
        {
          button_one.read();
          button_two.read();
          button_three.read();
          button_four.read();
          leds[i] = pgm_read_dword(&(ledarray3[i]));
        }FastLED.delay(60);

        for(int i = 0; i < num_led; i++)
        {
          button_one.read();
          button_two.read();
          button_three.read();
          button_four.read();
          leds[i] = pgm_read_dword(&(ledarray4[i]));
        }FastLED.delay(80);

        for(int i = 0; i < num_led; i++)
        {
          button_one.read();
          button_two.read();
          button_three.read();
          button_four.read();
          leds[i] = pgm_read_dword(&(ledarray3[i]));
        }FastLED.delay(80);

        for(int i = 0; i < num_led; i++)
        {
          button_one.read();
          button_two.read();
          button_three.read();
          button_four.read();
          leds[i] = pgm_read_dword(&(ledarray2[i]));
        }FastLED.delay(80);

        for(int i = 0; i < num_led; i++)
        {
          button_one.read();
          button_two.read();
          button_three.read();
          button_four.read();
          leds[i] = pgm_read_dword(&(ledarray1[i]));
        }FastLED.delay(80);
        remTime = millis();
        isBlinking = false;
      }
    }

    button_one.read();
    button_two.read();
    button_three.read();
    button_four.read();
  }
}


//tired eye blink animation
void squint(){
  while(pattern_counter == 2)
  {
    button_one.read();
    button_two.read();
    button_three.read();
    button_four.read();

    if(!isBlinking)
    {
      if((millis()- remTime) >= 0)
      {
        for(int i = 0; i < num_led; i++)
        {
          button_one.read();
          button_two.read();
          button_three.read();
          button_four.read();
          leds[i] = pgm_read_dword(&(ledarray5[i]));
        }FastLED.show();
        remTime = millis();
        isBlinking = true;
      }
    }

    else
    {
      if((millis()- remTime) >= 6000)
      {
        for(int i = 0; i < num_led; i++)
        {
          button_one.read();
          button_two.read();
          button_three.read();
          button_four.read();
          leds[i] = pgm_read_dword(&(ledarray1[i]));
        }FastLED.delay(80);
        
        for(int i = 0; i < num_led; i++)
        {
          button_one.read();
          button_two.read();
          button_three.read();
          button_four.read();
          leds[i] = pgm_read_dword(&(ledarray2[i]));
        }FastLED.delay(80);
      
        for(int i = 0; i < num_led; i++)
        {
          button_one.read();
          button_two.read();
          button_three.read();
          button_four.read();
          leds[i] = pgm_read_dword(&(ledarray3[i]));
        }FastLED.delay(80);
        
        for(int i = 0; i < num_led; i++)
        {
          button_one.read();
          button_two.read();
          button_three.read();
          button_four.read();
          leds[i] = pgm_read_dword(&(ledarray4[i]));
        }FastLED.delay(60);

        for(int i = 0; i < num_led; i++)
        {
          button_one.read();
          button_two.read();
          button_three.read();
          button_four.read();
          leds[i] = pgm_read_dword(&(ledarray2[i]));
        }FastLED.delay(60);

        for(int i = 0; i < num_led; i++)
        {
          button_one.read();
          button_two.read();
          button_three.read();
          button_four.read();
          leds[i] = pgm_read_dword(&(ledarray3[i]));
        }FastLED.delay(60);

        for(int i = 0; i < num_led; i++)
        {
          button_one.read();
          button_two.read();
          button_three.read();
          button_four.read();
          leds[i] = pgm_read_dword(&(ledarray4[i]));
        }FastLED.delay(80);

        for(int i = 0; i < num_led; i++)
        {
          button_one.read();
          button_two.read();
          button_three.read();
          button_four.read();
          leds[i] = pgm_read_dword(&(ledarray3[i]));
        }FastLED.delay(80);

        for(int i = 0; i < num_led; i++)
        {
          button_one.read();
          button_two.read();
          button_three.read();
          button_four.read();
          leds[i] = pgm_read_dword(&(ledarray2[i]));
        }FastLED.delay(80);

        for(int i = 0; i < num_led; i++)
        {
          button_one.read();
          button_two.read();
          button_three.read();
          button_four.read();
          leds[i] = pgm_read_dword(&(ledarray1[i]));
        }FastLED.delay(80);
        remTime = millis();
        isBlinking = false;

        button_one.read();
        button_two.read();
        button_three.read();
        button_four.read();
      }
    }
  }
}