#!/usr/bin/env/python

import os
import paho.mqtt.client as mqtt
from time import sleep
import time
import RPi.GPIO as GPIO

GPIO.setmode(GPIO.BCM)

SleepTimeL = 0.2



GPIO.setup(23, GPIO.OUT)
GPIO.output(23, GPIO.HIGH)
GPIO.setup(24, GPIO.OUT)
GPIO.output(24, GPIO.HIGH)

# The callback for when the client receives a CONNACK response from the server.
def main():
  def on_connect(client, userdata, flags, rc):
	client.subscribe("/Casa/Speakers/#")
  def on_message(client, userdata, msg):
	if msg.topic == "/Casa/Speakers/01/set" :
		if msg.payload == "ON" :
			GPIO.output(23, GPIO.LOW)
			client.publish("/Casa/Speakers/01/status", "ON", qos=0)
			time.sleep(SleepTimeL);
			print "Speaker 01 ON"
		if msg.payload == "OFF" :
			GPIO.output(23, GPIO.HIGH)
			client.publish("/Casa/Speakers/01/status", "OFF", qos=0)
			time.sleep(SleepTimeL);
			print "Speaker 01 OFF"
	if msg.topic == "/Casa/Speakers/02/set" :
		if msg.payload == "ON" :
			GPIO.output(24, GPIO.LOW)
			client.publish("/Casa/Speakers/02/status", "ON", qos=0)
			time.sleep(SleepTimeL);
			print "Speaker 02 ON"
		if msg.payload == "OFF" :
			GPIO.output(24, GPIO.HIGH)
			client.publish("/Casa/Speakers/02/status", "OFF", qos=0)
			time.sleep(SleepTimeL);
			print "Speaker 02 OFF"

	
  client = mqtt.Client()
  client.on_connect = on_connect
  client.on_message = on_message

  client.connect("192.168.2.106", 1883, 60)

  client.loop_forever()

if __name__ == '__main__':
	try:
	  	main()
	except KeyboardInterrupt:
		GPIO.cleanup()
