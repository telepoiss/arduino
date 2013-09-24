/*
Marge valguskast Viini
Tõnu Tunnel sept 2013
tonutunnel@gmail.com

Kaks valguskasti mis kordamööda vilguvad.
1Mohm takisti millega saab dimmerdada.
1 switch millega saab vilkumise välja lülitada nii et mõlemad korraga põlevad.
*/


#define FADESPEED 150      // kui on FADE kasutusel siis see on üleminekute kiirus (vähem=kiirem)
#define DELAY 6000         // piltide vahetuse intervall
#define firstPin 3         // esimene valguskast PWM pin
#define secondPin 5        // teine valguskast   PWM pin
const int switchPin = 2;   // lüliti vilkumine/constant on
int buttonState = 0;       // muutuja lüliti seisu hoidmiseks
int sensorPin = A0;        // select the input pin for the potentiometer
int sensorValue = 0;       // variable to store the value coming from the sensor
int outputValue = 0;       // analogväärtus ümber mäpitud  0-255 vahemikku



void setup() {
  pinMode(firstPin, OUTPUT);
  pinMode(secondPin, OUTPUT);
  pinMode(switchPin, INPUT); 
}



 void loop() {
   
   buttonState = digitalRead(switchPin);
   // kordamööda 6sek delayga
   if (buttonState == HIGH) { 
     
       sensorValue = analogRead(sensorPin);
       outputValue = map(sensorValue, 0, 1023, 0, 255);
    
        analogWrite(firstPin, outputValue);
        analogWrite(secondPin, 0);
        
        delay(DELAY); //6sekundit
        
        analogWrite(firstPin, 0);
        analogWrite(secondPin, outputValue);
        
        delay(DELAY); //6sekundit
      }
      else {
    // põlevad mõlemad konstantselt
     analogWrite(firstPin, 255);
     analogWrite(secondPin, 255);
     }
  }
 
  
  /*
 //FADE KOOD KUI TAHAKS ÜHTLASEMALT FADE'ida
   for (int brightness = 0; brightness < 255; brightness++) {
      analogWrite(firstPin, brightness);
      delay(FADESPEED);
    }

    delay(2000);

    for (int brightness = 255; brightness >= 0; brightness--) {
          analogWrite(firstPin, brightness);
          delay(FADESPEED);
    }

    delay(2000);
  */


