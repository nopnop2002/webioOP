from flask import Flask, render_template, request
app = Flask(__name__)
import gpio
import opi_pc
#import opi_pc2
#import opi_pc3
#import opi_pc4
#import opi_zero
#import opi_lite2

INPUT = 0 
OUTPUT = 1 
LOW = 0 
HIGH = 1 
DEBUG = 0

PINS = opi_pc.PINS
#PINS = opi_pc2.PINS
#PINS = opi_pc3.PINS
#PINS = opi_pc4.PINS
#PINS = opi_zero.PINS
#PINS = opi_lite2.PINS

#ALTS = [ "IN", "OUT", "ALT5", "ALT4", "ALT0", "ALT1", "ALT2", "ALT3" ]
ALTS = [ "IN", "OUT", "ALT2", "ALT3", "ALT4", "ALT5", "ALT6", "OFF" ]


def readall():
	for i in PINS: 
		pin = PINS[i]['pin']
		alt=gpio.getAlt(pin)
		#if DEBUG == 1: print("i={} pin={} alt={}".format(i, pin, alt))
		value=gpio.digitalRead(pin)
		#if DEBUG == 1: print("pin={} alt={} value={}".format(pin, ALTS[alt], value))
		PINS[i]['mode']=alt
		PINS[i]['smode']=ALTS[alt]
		PINS[i]['value']=value

	for i in PINS: 
		if DEBUG == 1: print("i={} mode={} smode={}".format(i, PINS[i]['mode'], PINS[i]['smode']))

@app.route("/")
def main():
	# For each pin, read the pin state and store it in the pins dictionary:
	templateData = {
		'pins' : PINS
	}
	# Pass the template data into the template main.html and return it to the user
	return render_template('webioOP.html', **templateData)

# change pin mode
@app.route("/changeMode/<int:changePin>/<action>")
def actionMode(changePin, action):
	if DEBUG == 1: print("actionMode: changePin={} action={}".format(changePin, action))
	# Convert the pin from the URL into an integer:
	#cpin = int(changePin)
	pin = PINS[changePin]['pin']

	# Get the device name for the pin being changed:
	deviceName = PINS[changePin]['name']
	if DEBUG == 1: print("pin={} deviceName={}".format(pin, deviceName))
	# If the action part of the URL is "output," execute the code indented below:
	if action == "output":
		# Set the pin output:
		gpio.pinMode(pin, OUTPUT)
		# Save the status message to be passed into the template:
		message = "Turned " + deviceName + " output."
	if action == "input":
		gpio.pinMode(pin, INPUT)
		message = "Turned " + deviceName + " input."

	readall()

	# Along with the pin dictionary, put the message into the template data dictionary:
	templateData = {
		'message' : message,
		'pins' : PINS
	}

	return render_template('webioOP.html', **templateData)


# change output value
@app.route("/changeValue/<int:changePin>/<action>")
def actionValue(changePin, action):
	if DEBUG == 1: print("actionValue: changePin={} action={}".format(changePin, action))
	# Convert the pin from the URL into an integer:
	#cpin = int(changePin)
	pin = PINS[changePin]['pin']

	# Get the device name for the pin being changed:
	deviceName = PINS[changePin]['name']
	if DEBUG == 1: print("pin={} deviceName={}".format(pin, deviceName))
	# If the action part of the URL is "on," execute the code indented below:
	if action == "on":
		# Set the pin high:
		gpio.digitalWrite(pin, HIGH)
		# Save the status message to be passed into the template:
		message = "Turned " + deviceName + " on."
	if action == "off":
		gpio.digitalWrite(pin, LOW)
		message = "Turned " + deviceName + " off."
	if action == "toggle":
		# Read the pin and set it to whatever it isn't (that is, toggle it):
		value=wringpi.digitalRead(pin)
		gpio.digitalWrite(pin, not value)
		message = "Toggled " + deviceName + "."

	readall()

	# Along with the pin dictionary, put the message into the template data dictionary:
	templateData = {
		'message' : message,
		'pins' : PINS
	}

	return render_template('webioOP.html', **templateData)

if __name__ == "__main__":
	gpio.wiringPiSetupPhys()
	readall()
	if DEBUG == 1: app.run(host='0.0.0.0', port=80, debug=True)
	if DEBUG == 0: app.run(host='0.0.0.0', port=80, debug=False)

