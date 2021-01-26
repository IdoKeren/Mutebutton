#include <Keyboard.h>
#include <Mouse.h>
#include <HID.h>
#define Key KEY_F13

const int buttonPin = 6;     // the number of the pushbutton pin
const int ledPin =  3;      // the number of the LED pin

bool buttonState = false;       
bool prevButtonState = false;        

void setup() {

  pinMode(ledPin, OUTPUT);

  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
  Keyboard.begin();

  digitalWrite(ledPin, HIGH);

}

void loop() {
  buttonState = !digitalRead(buttonPin);
  Serial.println(buttonState);
  
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH && prevButtonState == LOW) {
    Keyboard.press(Key);
    Keyboard.releaseAll();
  } 
  delay(50);

  prevButtonState =  buttonState;
}
