#RPi Pinouts
# NOTE: Need to run on a seprate thread --
#   https://docs.python.org/2/library/multiprocessing.html
#   https://docs.python.org/2/library/multiprocessing.html
# https://radiostud.io/howto-i2c-communication-rpi/
# https://github.com/suryasundarraj/rpi-series/blob/master/i2c_communication/rpi_i2c.py
#I2C Pins 
#GPIO2 -> SDA
#GPIO3 -> SCL

#Import the Library Required 
from smbus2 import SMBus
import time

# for RPI version 1, use "bus = smbus.SMBus(0)"
with SMBus(1) as bus:

    # This is the address we setup in the Arduino Program
    #Slave Address 1
    sAddress = 0x10

    def writeNumber(value):
        #bus.write_byte(sAddress, value)
        # bus.write_byte_data(address, 0, value)
        return -1

    def readNumber():
        # number = bus.read_byte(address)
        number = bus.read_byte(sAddress)
        return number
        
    # while True:
    # 	#Receives the data from the User
    #     data = raw_input("Enter the data to be sent : ")
    #     data_list = list(data)
    #     for i in data_list:
    #     	#Sends to the Slaves 
    #         writeNumber(int(ord(i)))
    #         time.sleep(.1)

    #     writeNumber(int(0x0A))
    i = 0
    while True:
        #bus.pec = 1
        #Reads data from the Slaves
        sensorValue = readNumber()
        print(str(i) + ": " + str(sensorValue) + " | " + str(bin(sensorValue)))
        i+=1
        #print(readNumber())
        time.sleep(.2)

#End of the Script