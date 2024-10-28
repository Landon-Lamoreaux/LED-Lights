
#include <FastLED.h>
#define NUM_LEDS 100
#define DATA_PIN 13
//#define BRIGHTNESS 200   /* Control the brightness of your leds */
#define SATURATION 255   /* Control the saturation of your leds */
int BRIGHTNESS = 150;
int POT_PIN = A1;
int BUTTON_PIN = 5;

CRGB leds[NUM_LEDS];

uint8_t r, g, b;
int potValue = 0;

bool rainbow = false;
bool colors = false;
bool halloween = true;
bool christmas = false;
int buttonState;
int lastButtonState;

unsigned long lastmillis = 0;

void setup() 
   { 
      // Setting up the button, potentiometer, and LEDs.
      pinMode(BUTTON_PIN, INPUT);
      pinMode(POT_PIN, INPUT);
      FastLED.addLeds<WS2811, DATA_PIN, GRB>(leds, NUM_LEDS);    
      r = g = b = 0;
   }

void loop()
{
  if(rainbow)
  {
    for (int j = 0; j < 255; j++) {
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CHSV(i - (j * 2), SATURATION, 255); /* The higher the value 4 the less fade there is and vice versa */ 
      }
      delay(50); /* Change this to your hearts desire, the lower the value the faster your colors move (and vice versa) */
      BRIGHTNESS = (analogRead(POT_PIN) / 5) % 255;
      FastLED.setBrightness(BRIGHTNESS);
      FastLED.show();

      // Checking if the button was pressed to change out of rainbow mode.
      lastButtonState = buttonState;
      buttonState = digitalRead(BUTTON_PIN);
      if(buttonState == HIGH && lastButtonState == LOW)
      {
        rainbow = false;
        colors = true;
        break;
      }
    }
  }
  else if (colors)
  {
    // Adjusting the LED color by the value of the potentiometer.
    BRIGHTNESS = 200;
    for (int i = 0; i < NUM_LEDS; i++)
    {
      leds[i] = CHSV(potValue, SATURATION, BRIGHTNESS);
    }
    potValue = (analogRead(POT_PIN) / 4) % 255;  // Reading the poteniometer value.
    FastLED.setBrightness(BRIGHTNESS);
    FastLED.show();
  }
  else if(halloween)
  {
    if(millis() - lastmillis <= 500)
    {
      for(int i = 0; i < NUM_LEDS; i++)
      {
        if(i % 3 == 0)
          leds[i] = CRGB(0xFF7A00);
        else if(i % 3 == 1)
          leds[i] = CRGB(0x6BFF00);
        else
          leds[i] = CRGB(0x0061FF);
      }
    }
    if(millis() - lastmillis > 500 && millis() - lastmillis < 1000)
    {
      for(int i = 0; i < NUM_LEDS; i++)
      {
        if(i % 3 == 0)
          leds[i] = CRGB(0x0061FF);
        else if(i % 3 == 1)
          leds[i] = CRGB(0xFF7A00);
        else
          leds[i] = CRGB(0x6BFF00);
      }
    }
    if(millis() - lastmillis >= 1000)
    {
      for(int i = 0; i < NUM_LEDS; i++)
      {
        if(i % 3 == 0)
          leds[i] = CRGB(0x6BFF00);
        else if(i % 3 == 1)
          leds[i] = CRGB(0x0061FF);
        else
          leds[i] = CRGB(0xFF7A00);
      }
    }
    if(millis() - lastmillis >= 1500)
      lastmillis = millis();

    BRIGHTNESS = (analogRead(POT_PIN) / 5) % 255;
    FastLED.setBrightness(BRIGHTNESS);
    FastLED.show();
  }
  else if(christmas)
  {
    for(int i = 0; i < NUM_LEDS - 2; i = i + 3)
    {
      leds[i] = CRGB(0x00B30C);
      // leds[i + 1] = CRGB(0xB3002C);
      leds[i + 1] = CRGB(0x590D01);
      leds[i + 2] = CRGB(0xFFFFFF);
    }

    if(millis() - lastmillis <= 500)
    {
      for(int i = 0; i < NUM_LEDS; i++)
      {
        if(i % 3 == 0)
          leds[i] = CRGB(0x00B30C);
        else if(i % 3 == 1)
          leds[i] = CRGB(0x590D01);
        else
          leds[i] = CRGB(0xFFFFFF);
      }
    }
    if(millis() - lastmillis > 500 && millis() - lastmillis < 1000)
    {
      for(int i = 0; i < NUM_LEDS; i++)
      {
        if(i % 3 == 0)
          leds[i] = CRGB(0xFFFFFF);
        else if(i % 3 == 1)
          leds[i] = CRGB(0x00B30C);
        else
          leds[i] = CRGB(0x590D01);
      }
    }
    if(millis() - lastmillis >= 1000)
    {
      for(int i = 0; i < NUM_LEDS; i++)
      {
        if(i % 3 == 0)
          leds[i] = CRGB(0x590D01);
        else if(i % 3 == 1)
          leds[i] = CRGB(0xFFFFFF);
        else
          leds[i] = CRGB(0x00B30C);
      }
    }
    if(millis() - lastmillis >= 1500)
      lastmillis = millis();

    BRIGHTNESS = (analogRead(POT_PIN) / 5) % 255;
    FastLED.setBrightness(BRIGHTNESS);
    FastLED.show();
  }

  // Checking if the button was pressed to change into rainbow mode.
  lastButtonState = buttonState;
  buttonState = digitalRead(BUTTON_PIN);
  if(buttonState == HIGH && lastButtonState == LOW)
  {
    if(rainbow == true)
      rainbow = false;
    else if(colors)
    {
      halloween = true;
      colors = false;
    }
    else if(halloween)
    {
      christmas = true;
      halloween = false;
    }
    else if(christmas)
    {
      rainbow = true;
      christmas = false;
    }
  }
}