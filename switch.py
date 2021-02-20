import serial
arduino = serial.Serial('COM5', 115200, timeout=.1)
while True:
    x = input("chanel port:value >")
    if x.upper() == 'Q':
        break
    arduino.write(f"<{x}>".encode())