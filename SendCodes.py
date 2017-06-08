import serial
import sys
import time

print(len(sys.argv))

if len(sys.argv) < 2:
    print("Bra you need to add an arg, THE Code duh")

ser = serial.Serial('/dev/ttyACM0')
stri ="Send:%s\n"%(sys.argv[1]) 
buf = bytes(stri, 'ascii') 
time.sleep(2) #if not working try change this :) #if not working try change this :)
ser.write(buf)
print(buf)

while ser.inWaiting():
    print(ser.readline())
