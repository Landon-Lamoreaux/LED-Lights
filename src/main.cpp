
#include <FastLED.h>
#define NUM_LEDS 225
#define DATA_PIN 13
//#define BRIGHTNESS 200   /* Control the brightness of your leds */
#define SATURATION 255   /* Control the saturation of your leds */
int BRIGHTNESS = 150;
int POT_PIN = A1;
int BUTTON_PIN = 5;

CRGB leds[NUM_LEDS];

uint8_t r, g, b;
int potValue = 0;

bool rainbow = true;
int buttonState;
int lastButtonState;

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
        leds[i] = CHSV(i - (j * 2), SATURATION, BRIGHTNESS); /* The higher the value 4 the less fade there is and vice versa */ 
      }
      delay(50); /* Change this to your hearts desire, the lower the value the faster your colors move (and vice versa) */
      BRIGHTNESS = (analogRead(POT_PIN) / 5) % 255;
      FastLED.show();

      // Checking if the button was pressed to change out of rainbow mode.
      lastButtonState = buttonState;
      buttonState = digitalRead(BUTTON_PIN);
      if(buttonState == HIGH && lastButtonState == LOW)
      {
        rainbow = false;
        break;
      }
    }
  }
  else
  {
    // Adjusting the LED color by the value of the potentiometer.
    BRIGHTNESS = 200;
    for (int i = 0; i < NUM_LEDS; i++)
    {
      leds[i] = CHSV(potValue, SATURATION, BRIGHTNESS);
    }
    potValue = (analogRead(POT_PIN) / 4) % 255;  // Reading the poteniometer value.
    FastLED.show();
  }

  // Checking if the button was pressed to change into rainbow mode.
  lastButtonState = buttonState;
  buttonState = digitalRead(BUTTON_PIN);
  if(buttonState == HIGH && lastButtonState == LOW)
  {
    if(rainbow == true)
      rainbow = false;
    else
      rainbow = true;
  }
}