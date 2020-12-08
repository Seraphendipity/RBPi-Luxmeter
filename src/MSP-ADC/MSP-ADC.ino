/*
  MSP-ADC
  Reads analog signal from Luxmeter, converts by ADC, 
  then allows the value to be available to a master via
  I2C protocol.
  
  Hardware Required:
  * MSP-EXP432P401R
  * 

  Examples Used:
  

  Learning References:
  https://circuitdigest.com/microcontroller-projects/msp430-launchpad-i2c-communication
*/


// INCLUDES
// Include external libraries for extended functionality.
#include <Wire.h>


// DEFINITIONS
// Define constants to be used throughout program as global variables.
#define LED RED_LED
int val = 0;

void setup() {
  // Setup runs once at the start or resetting of the microcontroller.
  
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600); // msp430g2231 must use 4800
    // initialize the digital pin as an output.
  pinMode(LED, OUTPUT);   

  // I2C: Use Energia's Wire Library Derivative
  // https://energia.nu/guide/libraries/wire/
  Wire.begin(0x10);
  Wire.onRequest(DataRequestHandler);
}

void loop() {
  // Loop runs indefinitely while the microcontroller is active, after setup()
 //   digitalWrite(LED, HIGH);   // turn the LED on (HIGH is the voltage level)
 // delay(5000);               // wait for a second
 // digitalWrite(LED, LOW);    // turn the LED off by making the voltage LOW
 // delay(2000);               // wait for a second
  // read the input on analog pin A3:
  int sensorValue = analogRead(A15);
  // print out the value you read:
  //Serial.println(sensorValue);
  delay(1); // delay in between reads for stability


  // I2C
  /*Wire.beginTransmission(44);  // transmit to device #44 (0x2c)
  Wire.write(byte(0x00));       // sends instruction byte
  Wire.write(val);              // sends potentiometer value byte
  Wire.endTransmission();       // stop transmitting
  val++;                        // increment value
  if (val == 64) {             // if reached 64th position (max)
    val = 0;    // start over from lowest value
  }
  delay(500);
  */
}

void DataRequestHandler() {
  Wire.write(val);
  val++;                        // increment value
  if (val == 64) {             // if reached 64th position (max)
    val = 0;    // start over from lowest value
  }
  
  Serial.print(val);
}
