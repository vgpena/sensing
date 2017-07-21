import serial
import time
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
# date = datetime.now()
# print(date)
# timestamp2 = time.mktime(date.timetuple()) # DO NOT USE IT WITH UTC DATE
# print(datetime.fromtimestamp(timestamp2))
# print(timestamp2.round())
# 2. send to Teensy
# ser.write(str(date))
# 3. to test, send back w/a char added
# while 1:
#     print(ser.read().rstrip('\n'))
# print(str(int(time.time()))[-8:])
# startTime = str(int(time.time()))[-8:]
# ser.write(startTime)
# file = open("bar.RAW", "w")
# fileData = bytearray()

with open("raw.RAW", "w") as f:
    hadData = False;
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
        # else:
        #     print("done")
        #     break
        # else:
        #     print("wat")
        # else:
        #     print("done")
        #     f.close()
        # print('b')
        # f.close()
        # os.system("./rawToWav.sh raw")
    # if (data != "_"):
    #     f.write(data)
    # else:
    #     print('b')
    #     f.close()
    #     os.system("./rawToWav.sh bar")
    #     break

# while 1:
#     data = ser.read()
#     with open("raw.RAW", "w") as f:
#         if (data != "_"):
#             f.write(data)
#         else:
#             print('b')
#             f.close()
#             os.system("./rawToWav.sh bar")
#             break
    # print(ser.read(24).strip())
    # data = ser.read()
    # # print(data)
    # if data != "_":
    #     file.write(data)
    #     # fileData.append(data)
    #     # print('a');
    # else:
    #     print('b')
    #     file.close()
        # os.system("./rawToWav.sh bar")
