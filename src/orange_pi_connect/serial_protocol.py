import time
import serial
ser = serial.Serial('/dev/ttyACM0', 9600) # задействовать последовательный порт

while 1: # бесконечный цикл
ser.readline() # считать последовательные данные, переданные платой Arduino Uno
print (ser.readline()) # напечатать на экране данные, переданные платой Arduino Uno