sketch designed to facilitate basic communication between an arduino MEGA and an esp8266-01. as it was written for a mega with additional hardware serial ports, it does not use software serial, but could probably be easily converted



# arduinoESPhost
use arduino mega to test/interact with an esp8266-01 without flashing esp module

serial keylist : *note this is planned, not necesslaraly current*

0 - send AT. basic test

1 - test toggle your led

2 - show ip address

3 - set operating mode

4 - enable multiple connections

5 - open tcp server

r - reset esp module

c - add wifi info and return command to connect


p - passthrough - a fallback mode, should act as a serial 'mirror,' passing messages from one serial port straight to the other.

b - will attempt to synchronize baudrate of esp by sending the command to update baud over all available baud rates

w - create/configure the esp wireless network
