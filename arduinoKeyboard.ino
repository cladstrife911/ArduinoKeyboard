#include <Keyboard.h>

int inPin = 2;
int ledPin = 12;
int reading=0;

int outputState = HIGH;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = HIGH;   // the previous reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 10;    // the debounce time; increase if the output flickers

int debounce(int reading);

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(inPin, INPUT_PULLUP); 

  lastButtonState = HIGH;

  delay(5000);
  Keyboard.begin();
}

void loop() {
  reading = digitalRead(inPin);   // read the input pin
  buttonState = debounce(reading);
  digitalWrite(ledPin, outputState);

  if(buttonState==LOW) //LOW means pressed
  {
    Keyboard.print("Hello!");
  }
  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;

  delay(10);
}

int debounce(int inVal)
{
 // If the switch changed, due to noise or pressing:
  if (inVal != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (inVal != buttonState) {
      buttonState = inVal;
      

      // only act when button is released
      /*if (lastButtonState == HIGH) {
        return LOW;
      }*/
    }
  }
  return lastButtonState;
}
