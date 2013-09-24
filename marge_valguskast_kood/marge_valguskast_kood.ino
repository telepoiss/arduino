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


const int numReadings = 20;
int readings[numReadings];      // the readings from the analog input
int index = 0;                  // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average



void setup() {
  pinMode(firstPin, OUTPUT);
  pinMode(secondPin, OUTPUT);
  pinMode(switchPin, INPUT); 
  Serial.begin(9600);
  
  // initialize all the readings to 0: 
  for (int thisReading = 0; thisReading < numReadings; thisReading++)
    readings[thisReading] = 0;
}



 void loop() {
   
   // subtract the last reading:
  total= total - readings[index];         
  // read from the sensor:  
  readings[index] = analogRead(sensorPin); 
  // add the reading to the total:
  total= total + readings[index];       
  // advance to the next position in the array:  
  index = index + 1;                    

  // if we're at the end of the array...
  if (index >= numReadings)              
    // ...wrap around to the beginning: 
    index = 0;                           

  // calculate the average:
  average = total / numReadings;         
  // send it to the computer as ASCII digits
   
  delay(1);        // delay in between reads for stability 
   
   //sensorValue = analogRead(sensorPin);
   outputValue = map(average, 0, 1023, 3, 255);
   delay(FADESPEED);

    // print the results to the serial monitor:
    Serial.print("avegage = ");
    Serial.print(average);
    Serial.print("\t sensor = " );                       
    Serial.print(sensorValue);      
    Serial.print("\t output = ");      
    Serial.println(outputValue);
  
  
   
   buttonState = digitalRead(switchPin);
   // kordamööda 6sek delayga
   if (buttonState == HIGH) { 
     analogWrite(firstPin, outputValue);
     analogWrite(secondPin, 0);
     delay(DELAY);
     
     analogWrite(firstPin, 0);
     analogWrite(secondPin, outputValue);
     delay(DELAY);

   }
   //mõlemad korraga
    else if (buttonState == LOW) {
      analogWrite(secondPin, outputValue);
      analogWrite(firstPin, outputValue);
      delay(200);
      
    }

 }

