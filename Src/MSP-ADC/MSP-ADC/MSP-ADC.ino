/*
  AnalogReadSerial
  Reads an analog input on pin A3, prints the result to the serial monitor.
  Attach the center pin of a potentiometer to pin A3, and the outside pins to ~3V and ground.
  
  Hardware Required:
  * MSP-EXP430G2 LaunchPad
  * 10-kilohm Potentiometer
  * hook-up wire

  This example code is in the public domain.
*/
// most launchpads have a red LED
#define LED RED_LED
// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600); // msp430g2231 must use 4800
    // initialize the digital pin as an output.
  pinMode(LED, OUTPUT);   
}

// the loop routine runs over and over again forever:
void loop() {
 //   digitalWrite(LED, HIGH);   // turn the LED on (HIGH is the voltage level)
 // delay(5000);               // wait for a second
 // digitalWrite(LED, LOW);    // turn the LED off by making the voltage LOW
 // delay(2000);               // wait for a second
  // read the input on analog pin A3:
  int sensorValue = analogRead(A15);
  // print out the value you read:
  Serial.println(sensorValue);
  delay(1); // delay in between reads for stability
}
