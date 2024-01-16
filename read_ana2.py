import serial
from datetime import datetime

sensor = "ana2"
serial_port = '/dev/cu.usbmodem146401'
baud_rate = 115200
path = "%s_LOG_%s.txt" % (str(datetime.now()), sensor)
ser = serial.Serial(serial_port, baud_rate)
with open(path, 'w+') as f:
    while True:
        line = ser.readline()
        f.writelines([line.strip(), " t = %s \n " % (datetime.now())])
