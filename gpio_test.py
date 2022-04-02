#!/usr/bin/env python3
import gpio
import time

INPUT = 0 
OUTPUT = 1 
LOW = 0 
HIGH = 1 

# Get gpio status
alts = ["IN", "OUT", "ALT2", "ALT3", "ALT4", "ALT5", "ALT6", "OFF"]
gpio.wiringPiSetupPhys()
pinNum = 26
for pin in range(pinNum):
	type = gpio.physPinToGpio(pin+1)
	print("pin={} physPinToGpio={}".format(pin, type))
	if (type == -1): continue
	alt = gpio.getAlt(pin+1)
	print("pin={} getAlt={}".format(pin, alts[alt]))

# Change pin mode
print("Change the pin mode of Pin #3")
pin = 3
alt = gpio.getAlt(pin)
print("pin={} getAlt={}".format(pin, alts[alt]))
gpio.pinMode(pin, OUTPUT)
alt = gpio.getAlt(pin)
print("pin={} getAlt={}".format(pin, alts[alt]))
gpio.pinMode(pin, INPUT)
alt = gpio.getAlt(pin)
print("pin={} getAlt={}".format(pin, alts[alt]))

# Change pin value
print("Change the pin value of Pin #3")
gpio.pinMode(pin, OUTPUT)
for loops in range(10):
	printf("Turn HIGH")
	gpio.digitalWrite(pin, HIGH)
	time.sleep(1)
	printf("Turn LOW")
	gpio.digitalWrite(pin, LOW)
	time.sleep(1)
