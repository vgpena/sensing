import serial
import datetime
import os

ser = serial.Serial('/dev/tty.usbmodem3352381', 9600)
# count = 0

# os.system("./rawToWav.sh ~/Desktop/YISS")

# while 1:
    # count += 1
    # print(ser.readline())
    # if count % 1000 == 0:
        # ser.write('3')

# 1. get system time
date = datetime.datetime.now()
print(date)
# 2. send to Teensy
ser.write(str(date))
# 3. to test, send back w/a char added
while 1:
    print(ser.read().rstrip('\n'))
