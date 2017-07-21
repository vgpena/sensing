import serial
import time
import os

ser = serial.Serial('/dev/tty.usbmodem3352381', 9600)

with open("raw.RAW", "w") as f:
    hadData = False;
    print("waiting for recording to finish")
    while 1:
        if ser.in_waiting > 0:
            if hadData == False:
                print("receiving data")
                hadData = True
        if hadData and ser.in_waiting == 0:
            print("done")
            break
        else:
            data = ser.read()
            f.write(data)
    f.close()
    print("converting file")
    os.system("./rawToWav.sh raw")
