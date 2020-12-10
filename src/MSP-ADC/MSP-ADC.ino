/*
	MSP-ADC
	Reads analog signal from Luxmeter, converts by ADC, right-shifts 
	the value by 2, then allows the value to be available to a 
	master via I2C protocol.

	AUTHOR:		Seraphendipity
	REPO:		https://github.com/Seraphendipity/RBPi-Luxmeter

	Hardware Required:
	* General
		* MSP-EXP432P401R
		* Micro-USB to USB-A Cord (for upload and power)
		* Computer (for upload, possibly power)
		* AC/DC Adapter (possibly power)
	* Data Measurement
		* PDV-P8001 CdS Photoconductive Photocell
		* Pull-Down Resistor: between 1K Ohms (bright area) to 10K Ohms (dim area)
		* 3 x Wires
	* Data Communication - I2C
		* 2 x Pull-Up Resistors
		* 6 x Wires
		* Master I2C Device (i.e. Raspberry Pi 4)

	Learning References:
	* https://circuitdigest.com/microcontroller-projects/msp430-launchpad-i2c-communication
*/

//___________________________________________________________________________//

// INCLUDES
// Include external libraries for extended functionality.

	// Energia library enabling various hardware communication methods/ 
	#include <Wire.h>

// DEFINITIONS
// Define constants to be used throughout program as global variables.

	// Where this device can be found on the I2C bus.
	#define		SLAVE_ADDRESS		0x10

	// Analog pin that will be read from for the Luxmeter value.
	#define		LUXMETER_PIN		A15

	// Delay between successive reads of luxmeter.
	#define		READ_DELAY			100

// GLOBAL VARIABLES
// A value to be utilized across functions.

	// Stores the value of the luxmeter output.
	int sensorValue = 0;

//___________________________________________________________________________//

void setup() {
// Setup runs once at the start or resetting of the microcontroller.

	// Initialize serial communication at 9600 bits per second:
	Serial.begin(9600);

	// I2C
	// Use Energia's Wire Library Derivative
	// https://energia.nu/guide/libraries/wire/

	// Initiate the device on the I2C communication line as SLAVE_ADDRESS
	Wire.begin(SLAVE_ADDRESS);

	// Register the DataRequestHandler() function to be called when this
	// device is requested data from.
	Wire.onRequest(DataRequestHandler);

}

//___________________________________________________________________________//

void loop() {
// Loop runs indefinitely while the microcontroller is active, after setup()

	// Reads LUXMETER_PIN value, between 0 to 1024.
	sensorValue = analogRead(A15);
	
	// Delay in between reads for stability.
	delay(READ_DELAY);

	// Debug
	//Serial.println(sensorValue);

}

//___________________________________________________________________________//

void DataRequestHandler() {
// DataRequestHandler runs whenever a master requests data from this device.
	
	// Right-shifts the value by 2 in order to give the MSB's, before
	// writing the data via the I2C bus.
	Wire.write(sensorValue >> 2);

	// Debug
	/*
	static int i = 0;
	Serial.print(i++);
	Serial.print(": ");
	Serial.print(sensorValue);
	Serial.print(" | ");
	Serial.println(sensorValue, BIN);
	*/

}

//___________________________________________________________________________//
