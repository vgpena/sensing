import serial
ser = serial.Serial('/dev/tty.usbmodem3352381', 9600)
#print(ser)
count = 0

while 1:
    # count += 1
    # print(ser.readline())
    # if count % 1000 == 0:
        ser.write('3')
