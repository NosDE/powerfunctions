#ifndef _POWERFUNCTIONS_H
#define _POWERFUNCTIONS_H

#ifndef F_CPU
/* Definiere F_CPU, wenn F_CPU nicht bereits vorher definiert 
   (z.B. durch Übergabe als Parameter zum Compiler innerhalb 
   des Makefiles). Zusätzlich Ausgabe einer Warnung, die auf die
   "nachträgliche" Definition hinweist */
#warning "F_CPU war noch nicht definiert, wird nun mit 14745600 definiert"
#define F_CPU 14745600UL     /* Quarz mit 14.745600 Mhz */
#endif

#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


#define IR_PORT     PORTB
#define IR_DDR      DDRB
#define IR_PIN      PORTB4
#define IR_PIN_DD   DDB4


#define LEDGRN_OFF   	PORTB |=  (1<<PORTB2)
#define LEDGRN_ON		PORTB &= ~(1<<PORTB2)
#define LEDGRN_TOGGLE	PORTB ^=  (1<<PORTB2)


#define COMBO_DIRECT_MODE 0x01
#define SINGLE_PIN_CONTINUOUS 0x2
#define SINGLE_PIN_TIMEOUT 0x3
#define SINGLE_OUTPUT 0x4
#define ESCAPE 0x4

#define IR_CYCLES(num) (uint16_t) ((1.0/38000.0) * 1000 * 1000 * num)

#define START_STOP IR_CYCLES(39)
#define HIGH_PAUSE IR_CYCLES(21)
#define LOW_PAUSE IR_CYCLES(10)
#define HALF_PERIOD IR_CYCLES(0.5)
#define MAX_MESSAGE_LENGTH IR_CYCLES(522) // 2 * 45 + 16 * 27

//PWM speed steps
#define PWM_FLT 0x0
#define PWM_FWD1 0x1
#define PWM_FWD2 0x2
#define PWM_FWD3 0x3
#define PWM_FWD4 0x4
#define PWM_FWD5 0x5
#define PWM_FWD6 0x6
#define PWM_FWD7 0x7
#define PWM_BRK 0x8
#define PWM_REV7 0x9
#define PWM_REV6 0xA
#define PWM_REV5 0xB
#define PWM_REV4 0xC
#define PWM_REV3 0xD
#define PWM_REV2 0xE
#define PWM_REV1 0xf

//output
#define RED 0x0
#define BLUE 0x1

extern void PF_init(void);
extern void PF_single_pwm(uint8_t channel, uint8_t output, uint8_t pwm);
extern void PF_combo_pwm(uint8_t channel, uint8_t blue_speed, uint8_t red_speed);

void PF_pause(uint8_t count);
void PF_start_stop_bit(void);
void PF_send_bit(void);
void PF_send(void);
void LED_Init(void);

uint8_t _channel;
uint8_t _nib1, _nib2, _nib3;
uint8_t _toggle;

#endif //_POWERFUNCTIONS_H
