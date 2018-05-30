import paho.mqtt.publish as publish
import time

while True:
   print("sending msg")
   publish.single("olaaaaaa", "1", hostname="192.168.2.106")
   time.sleep(6)
