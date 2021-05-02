

/*
Physical buttons for Google Meet
Including launch / end meeting; Mute/Unmute; Video On/Off
*/

#include <Keyboard.h>
#include <Bounce2.h>

// constants won't change. They're used here to set pin numbers:
const int mutePin = 9;    // Button for Mute/Unmute
const int onPin = 8; // Button for On/Off
const int vidPin = 7; // Button for Video Mute

const int muteLed = 10;      // Led for Mute
const int onLed = 16; // Led for on/off
const int vidLed = 14; // Led for Video Mute

// Variables will change:
int muteState = LOW;        // the current state of the output pin
int vidState = LOW;         // the current state of the output pin
int onState = LOW;         // the current state of the output pin
                   
// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

Bounce m = Bounce(); // Instantiate a Bounce object for mute
Bounce v = Bounce(); // Instantiate a Bounce object for video
Bounce o = Bounce(); // Instantiate a Bounce object for on

void setup() {

/*
  pinMode(mutePin, INPUT_PULLUP);
  pinMode(onPin, INPUT_PULLUP);
  pinMode(vidPin, INPUT_PULLUP);
*/

  //Setup Input Pins
  m.attach(mutePin, INPUT_PULLUP);
  o.attach(onPin, INPUT_PULLUP);
  v.attach(vidPin, INPUT_PULLUP);

  m.interval(50); // Use a debounce interval of 50 milliseconds
  o.interval(50); // Use a debounce interval of 50 milliseconds
  v.interval(50); // Use a debounce interval of 50 milliseconds

  //Setup LED pins
  pinMode(muteLed, OUTPUT);
  pinMode(onLed, OUTPUT);
  pinMode(vidLed, OUTPUT);

  // set initial LED state
  digitalWrite(muteLed, muteState);
  digitalWrite(onLed, onState);
  digitalWrite(vidLed, vidState);
}

void loop() {

/*
    Serial.print(digitalRead(mutePin));
    Serial.print(digitalRead(vidPin));
    Serial.print(digitalRead(onPin));
    delay(1000);
*/
   m.update(); // Update the Bounce instance

   if ( m.fell() ) { 
     togMute();
   }

   o.update(); // Update the Bounce instance
   
   if ( o.fell() ) { 
     togOn();
   }

   v.update(); // Update the Bounce instance
   
   if ( v.fell() ) { 
     togVid();
   }

}

//Toggle the Mute command and LED
void togMute() {
      // only toggle the LED if the new button state is HIGH
        if (muteState == HIGH) {
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.write('s');          
        Keyboard.releaseAll();
          } else {
       Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_LEFT_SHIFT);
       Keyboard.write('a');          
       Keyboard.releaseAll();
          }
        muteState = !muteState;

  // set the LED:
    digitalWrite(muteLed, muteState);
//  digitalWrite(ledPina, ledState);

}

void togVid() {
      if (vidState == HIGH) {
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.write('g');
        Keyboard.releaseAll();
          } else {
       Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_LEFT_SHIFT);
       Keyboard.write('h');          
       Keyboard.releaseAll();
          }
        vidState = !vidState;

  // set the LED:
  digitalWrite(vidLed, vidState);
  Serial.print("ToggleVid");
  Serial.print(onState);
}

void togOn() {
      
  if (onState == HIGH) {
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.write('f');          
    Keyboard.releaseAll();
   vidState = LOW;
   muteState = LOW;
    
      } else {
        //Activate using TAB to get to the "Join" button, then SPACE
   Keyboard.write(9);          
   Keyboard.write(9);
   Keyboard.write(9);       
   Keyboard.write(9);          
   Keyboard.write(9);
   Keyboard.write(9);        
   Keyboard.write(9);          
   Keyboard.write(9);
   Keyboard.write(9); 
   Keyboard.write(32);              
   vidState = HIGH;
   muteState = HIGH;
      }
    onState = !onState;
  Serial.print("ToggleOn");
  Serial.print(onState);


  // set the LED:
  digitalWrite(onLed, onState);
  digitalWrite(vidLed, vidState);
  digitalWrite(muteLed, muteState);
}
