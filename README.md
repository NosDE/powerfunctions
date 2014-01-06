powerfunctions
==============

Serial to Lego PowerFunctions IR Bridge with ATMega-328 (14.74560 MHz).

PORTB.2 = LED (Status - blinks when transmitting data)

PORTB.4 = IR-LED (Transmitter LED)

PORTD.0 = RXD (Data Input 57600 8N1)
PORTD.1 = TXD (not used yet)

Data Format:
Each frame is 6 bytes long

1. Byte = 0x70 (Sync Byte 1)
2. Byte = 0x66 (Sync Byte 2)
3. Byte = 0x01 (PWM Class)
4. Byte = 0x.. (Channel : 0x01 - 0x04)
5. Byte = 0x.. (Output: RED = 0x00, BLUE = 0x01)
6. Byte = 0x.. (PWM-Data : see below...)

PWM-Data:

PWM_FLT 0x00
PWM_FWD1 0x01
PWM_FWD2 0x02
PWM_FWD3 0x03
PWM_FWD4 0x04
PWM_FWD5 0x05
PWM_FWD6 0x06
PWM_FWD7 0x07
PWM_BRK  0x08
PWM_REV7 0x09
PWM_REV6 0x0A
PWM_REV5 0x0B
PWM_REV4 0x0C
PWM_REV3 0x0D
PWM_REV2 0x0E
PWM_REV1 0x0F


Sample:
0x70 0x66 0x01 0x03 0x00 0x07 
Send Forward PWM7 (fastest) to red output on channel 3
