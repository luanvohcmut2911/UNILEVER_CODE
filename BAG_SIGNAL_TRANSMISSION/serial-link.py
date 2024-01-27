import serial
import time
import sys

if __name__ == "__main__":
    
    if(len(sys.argv) != 2 or (sys.argv[1]!='on' and sys.argv[1] != 'off')):
        print("Need one argument for on/off signal")
        sys.exit(1)
        
    ser = serial.Serial("/dev/ttyACM0", 9600, timeout=1)

    ser.setDTR(False)
    time.sleep(1)
    ser.flushInput()
    ser.setDTR(True)
    time.sleep(2)   
    signal = sys.argv[1]
    try:
        while True:
            print('Telling the Arduino to start blinking...')
            if(signal == 'on'):
                ser.write(b'1') ## tin hieu cho dong co bat dau chay
            else:
                ser.write(b'0') ## tin hieu cho dong co dung lai

            # read to get the acknowledgement from the Arduino
            while True:
                ack = ser.read()
                if ack == b'A':
                    break
            print('Arduino sent back %s' % ack)
    except KeyboardInterrupt:
        sys.exit(1)

    
