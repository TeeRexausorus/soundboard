import serial
from playsound import playsound

if __name__ == '__main__':
    with serial.Serial('/dev/cu.usbserial-14340', 9600) as ser:
        print("connected to usb")
        while True:
            received_char = str(ser.readline().decode('ascii'))
            final_char = received_char.rstrip('\r\n')
            if final_char == 'A':
                playsound("sound/Turret_turret_disabled_6_fr.wav")
            if final_char == 'B':
                playsound("sound/call-911-now_1.mp3")
            if final_char == 'C':
                playsound("sound/sound-yeah.mp3")
    print("nope")