#include <Keyboard.h>
#include <Mouse.h>
#include <HID.h>

#define KeyToPress KEY_F13

const int buttonPin = 6;     // the number of the pushbutton pin
const int ledPin =  3;      // the number of the LED pin


bool buttonState = false;       
bool prevButtonState = false;        

float gamma = 0.14; // affects the width of peak (more or less darkness)
float beta = 0.5; // shifts the gaussian to be symmetric
float smoothness_pts = 1500;//larger=slower change in brightness

void setup() {

  pinMode(ledPin, OUTPUT);

  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
  Keyboard.begin();

  digitalWrite(ledPin, HIGH);

}

void loop() {
  for (int ii=0;ii<smoothness_pts;ii++){
    float pwm_val = 255.0*(exp(-(pow(((ii/smoothness_pts)-beta)/gamma,2.0))/2.0));
    analogWrite(ledPin,int(pwm_val));
    delay(5);
    Serial.println(int(pwm_val));
    if (ii%10 == 0){
      buttonState = !digitalRead(buttonPin);
      Serial.println(buttonState);
  
       // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
      if (buttonState == HIGH && prevButtonState == LOW) {
        Keyboard.press(KeyToPress);
       Keyboard.releaseAll();
      } 
      prevButtonState =  buttonState;
    }
  }
}
