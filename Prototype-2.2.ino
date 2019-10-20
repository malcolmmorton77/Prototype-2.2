/*
  Smoothing
  Repeatedly reads from an analog input, calculating a running average and
  printing it to the computer. Keeps ten readings in an array and continually
  averages them.
  The circuit:
  - analog sensor (potentiometer will do) attached to analog input 0
  created 22 Apr 2007
  by David A. Mellis  <dam@mellis.org>
  modified 9 Apr 2012
  by Tom Igoe
  This example code is in the public domain.
  http://www.arduino.cc/en/Tutorial/Smoothing
*/
#include <Servo.h>
// Define the number of samples to keep track of. The higher the number, the
// more the readings will be smoothed, but the slower the output will respond to
// the input. Using a constant rather than a normal variable lets us use this
// value to determine the size of the readings array.
const int numReadings = 10;
const int buttonPin = 2;
const int ledPin = 13;

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average
int sig;
int inputPin = A0;

int buttonState = 0;
int minimum;
int maximum;

Servo motor;
void setup() {
      // initialize serial communication with computer:
  Serial.begin(9600);
      // initialize all the readings to 0:
  for (int thisReading = 0; thisReading < numReadings; thisReading++) 
  {
    readings[thisReading] = 0;
  }
  motor.attach(9);

    //this intializes an LED for output
  pinMode(ledPin, OUTPUT);
    //this initializes a button for pin 2
  pinMode(buttonPin, INPUT);
  
}

void loop() {
  
        //reads in a state of the button and augments LED
  buttonState = digitalRead(buttonPin);
  if(buttonState == HIGH)
  {
    for(int i = 0; i < 2; i++)
    {
      digitalWrite(ledPin, HIGH);
      delay(250);
      digitalWrite(ledPin, LOW);
      delay(250);
    }                                 //flashes twice to tell to to relax
    delay(2000);
    minimum = analogRead(inputPin);   //reads the min (unflexed value)
    for(int i = 0; i < 2; i++)
    {
      digitalWrite(ledPin, HIGH);
      delay(250);
      digitalWrite(ledPin, LOW);
      delay(250);
    }
    delay(2000); 
    maximum = analogRead(inputPin);   //reads the max (flexed version)
    delay(1000);
    
    for(int i = 0; i < 3; i++)
    {
      digitalWrite(ledPin, HIGH);
      delay(250);
      digitalWrite(ledPin, LOW);
      delay(250);
    }                                //indicating end of calibration
  }
  
        // subtract the last reading:
  total = total - readings[readIndex];
  
        // read from the sensor:
  readings[readIndex] = analogRead(inputPin);
  
        // add the reading to the total:
  total = total + readings[readIndex];
  
        // advance to the next position in the array:
  readIndex = readIndex + 1;

        // if we're at the end of the array...
  if (readIndex >= numReadings) 
  {
        // ...wrap around to the beginning:
    readIndex = 0;
  }

        // calculate the average:
  average = total / numReadings;
        // send it to the computer as ASCII digits
  Serial.println(average);
  delay(55);        // delay in between reads for stability
  sig = map(average, minimum, maximum, 0, 180);
  motor.write(sig);


}
