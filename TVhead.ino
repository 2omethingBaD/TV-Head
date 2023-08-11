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
#define button_five_pin 7
#define BAUDRATE 115200
#define num_led 126

CRGB leds[num_led];
EasyButton button_one(button_one_pin);
EasyButton button_two(button_two_pin);
EasyButton button_three(button_three_pin);
EasyButton button_four(button_four_pin);
EasyButton button_five(button_five_pin);
uint8_t pattern_counter = 11;


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
//UwU eye
const long ledarray6[] PROGMEM = {
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
void onB4Press()
{
  pattern_counter = 4;
}
void onB5Press()
{
  pattern_counter = 5;
}


void setup(){                
  FastLED.addLeds<WS2812B, led_pin, GRB>(leds, num_led);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);
  Serial.begin(BAUDRATE);

  button_one.begin();
  button_two.begin();
  button_one.onPressed(onB1Press);
  button_one.onSequence(2, 2000, onB1DPress);
  button_two.onPressed(onB2Press);
  button_two.onSequence(2, 2000, onB2DPress);
  button_three.onPressed(onB3Press);
  button_four.onPressed(onB4Press);
  button_five.onPressed(onB5Press);
}


void loop(){
  button_one.read();
  button_two.read();
  button_three.read();
  button_four.read();
  button_five.read();

  switch (pattern_counter) {
    case 1:
      openEye();
      break;
    case 11:
      blink();
      break;
    case 2:
      squintEye();
      break;
    case 22:
      squint();
      break;
    case 3:
      xEye();
      break;
    case 4:
      UwUEye();
      break;
    case 5:
      closedEye();
      break;
  }
}


//static open eye
void openEye(){
  while(pattern_counter == 1){
    for(int i = 0; i < num_led; i++){
    leds[i] = pgm_read_dword(&(ledarray0[i]));
    button_one.read();
    button_two.read();
    button_three.read();
    button_four.read();
    button_five.read();
  }
  FastLED.delay(80);
  }
}
//static squinted eye
void squintEye(){
  while(pattern_counter == 2){
    for(int i = 0; i < num_led; i++){
    leds[i] = pgm_read_dword(&(ledarray5[i]));
    button_one.read();
    button_two.read();
    button_three.read();
    button_four.read();
    button_five.read();
  }
  FastLED.delay(80);
  }
}
//static X eye
void xEye(){
  while(pattern_counter == 3){
    for(int i = 0; i < num_led; i++){
    leds[i] = pgm_read_dword(&(ledarray7[i]));
    button_one.read();
    button_two.read();
    button_three.read();
    button_four.read();
    button_five.read();
  }
  FastLED.delay(80);
  }
}
//static UwU eye
void UwUEye(){
  while(pattern_counter == 4){
    for(int i = 0; i < num_led; i++){
    leds[i] = pgm_read_dword(&(ledarray6[i]));
    button_one.read();
    button_two.read();
    button_three.read();
    button_four.read();
    button_five.read();
  }
  FastLED.delay(80);
  }
}
//static closed eye
void closedEye(){
  while(pattern_counter == 5){
    for(int i = 0; i < num_led; i++){
    leds[i] = pgm_read_dword(&(ledarray4[i]));
    button_one.read();
    button_two.read();
    button_three.read();
    button_four.read();
    button_five.read();
  }
  FastLED.delay(80);
  }
}
//idle animation /blink animation
void blink(){ 
  while(pattern_counter == 11){
    button_one.read();
    button_two.read();
    button_three.read();
    button_four.read();
    button_five.read();
  for(int i = 0; i < num_led; i++)
  {
    button_one.read();
    button_two.read();
    button_three.read();
    button_four.read();
    button_five.read();
    leds[i] = pgm_read_dword(&(ledarray0[i]));
  }
  FastLED.delay(6000);
  
  for(int i = 0; i < num_led; i++){
    button_one.read();
    button_two.read();
    button_three.read();
    button_four.read();
    button_five.read();
    leds[i] = pgm_read_dword(&(ledarray1[i]));
  }
  FastLED.delay(80);
 
  for(int i = 0; i < num_led; i++){
    button_one.read();
    button_two.read();
    button_three.read();
    button_four.read();
    button_five.read();
    leds[i] = pgm_read_dword(&(ledarray2[i]));
  }
  FastLED.delay(80);
  
  for(int i = 0; i < num_led; i++){
    button_one.read();
    button_two.read();
    button_three.read();
    button_four.read();
    button_five.read();
    leds[i] = pgm_read_dword(&(ledarray3[i]));
  }
  FastLED.delay(80);
  
  for(int i = 0; i < num_led; i++){
    button_one.read();
    button_two.read();
    button_three.read();
    button_four.read();
    button_five.read();
    leds[i] = pgm_read_dword(&(ledarray4[i]));
  }
  FastLED.delay(60);

  for(int i = 0; i < num_led; i++){
    button_one.read();
    button_two.read();
    button_three.read();
    button_four.read();
    button_five.read();
    leds[i] = pgm_read_dword(&(ledarray2[i]));
  }
  FastLED.delay(60);

  for(int i = 0; i < num_led; i++){
    button_one.read();
    button_two.read();
    button_three.read();
    button_four.read();
    button_five.read();
    leds[i] = pgm_read_dword(&(ledarray3[i]));
  }
  FastLED.delay(60);

  for(int i = 0; i < num_led; i++){
    button_one.read();
    button_two.read();
    button_three.read();
    button_four.read();
    button_five.read();
    leds[i] = pgm_read_dword(&(ledarray4[i]));
  }
  FastLED.delay(80);

  for(int i = 0; i < num_led; i++){
    button_one.read();
    button_two.read();
    button_three.read();
    button_four.read();
    button_five.read();
    leds[i] = pgm_read_dword(&(ledarray3[i]));
  }
  FastLED.delay(80);

  for(int i = 0; i < num_led; i++){
    button_one.read();
    button_two.read();
    button_three.read();
    button_four.read();
    button_five.read();
    leds[i] = pgm_read_dword(&(ledarray2[i]));
  }
  FastLED.delay(80);

  for(int i = 0; i < num_led; i++){
    button_one.read();
    button_two.read();
    button_three.read();
    button_four.read();
    button_five.read();
    leds[i] = pgm_read_dword(&(ledarray1[i]));
  }
  FastLED.delay(80);
  button_one.read();
  button_two.read();
  button_three.read();
  button_four.read();
  button_five.read();
  }
}
//tired eye blink animation
void squint(){
  while(pattern_counter == 22){
    button_one.read();
    button_two.read();
    button_three.read();
    button_four.read();
    button_five.read();
  for(int i = 0; i < num_led; i++)
  {
    button_one.read();
    button_two.read();
    button_three.read();
    button_four.read();
    button_five.read();
    leds[i] = pgm_read_dword(&(ledarray5[i]));
  }
  FastLED.delay(6000);
 
  for(int i = 0; i < num_led; i++){
    button_one.read();
    button_two.read();
    button_three.read();
    button_four.read();
    button_five.read();
    leds[i] = pgm_read_dword(&(ledarray1[i]));
  }
  FastLED.delay(80);
  
  for(int i = 0; i < num_led; i++){
    button_one.read();
    button_two.read();
    button_three.read();
    button_four.read();
    button_five.read();
    leds[i] = pgm_read_dword(&(ledarray2[i]));
  }
  FastLED.delay(80);
 
  for(int i = 0; i < num_led; i++){
    button_one.read();
    button_two.read();
    button_three.read();
    button_four.read();
    button_five.read();
    leds[i] = pgm_read_dword(&(ledarray3[i]));
  }
  FastLED.delay(80);
  
  for(int i = 0; i < num_led; i++){
    button_one.read();
    button_two.read();
    button_three.read();
    button_four.read();
    button_five.read();
    leds[i] = pgm_read_dword(&(ledarray4[i]));
  }
  FastLED.delay(60);

  for(int i = 0; i < num_led; i++){
    button_one.read();
    button_two.read();
    button_three.read();
    button_four.read();
    button_five.read();
    leds[i] = pgm_read_dword(&(ledarray2[i]));
  }
  FastLED.delay(60);

  for(int i = 0; i < num_led; i++){
    button_one.read();
    button_two.read();
    button_three.read();
    button_four.read();
    button_five.read();
    leds[i] = pgm_read_dword(&(ledarray3[i]));
  }
  FastLED.delay(60);

  for(int i = 0; i < num_led; i++){
    button_one.read();
    button_two.read();
    button_three.read();
    button_four.read();
    button_five.read();
    leds[i] = pgm_read_dword(&(ledarray4[i]));
  }
  FastLED.delay(80);

  for(int i = 0; i < num_led; i++){
    button_one.read();
    button_two.read();
    button_three.read();
    button_four.read();
    button_five.read();
    leds[i] = pgm_read_dword(&(ledarray3[i]));
  }
  FastLED.delay(80);

  for(int i = 0; i < num_led; i++){
    button_one.read();
    button_two.read();
    button_three.read();
    button_four.read();
    button_five.read();
    leds[i] = pgm_read_dword(&(ledarray2[i]));
  }
  FastLED.delay(80);

  for(int i = 0; i < num_led; i++){
    button_one.read();
    button_two.read();
    button_three.read();
    button_four.read();
    button_five.read();
    leds[i] = pgm_read_dword(&(ledarray1[i]));
  }
  FastLED.delay(80);
  button_one.read();
  button_two.read();
  button_three.read();
  button_four.read();
  button_five.read();
  }
}