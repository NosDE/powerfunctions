
#include <stdlib.h>        
#include "PowerFunctions.h"

#define PF_toggle() _toggle ^= 0x8                 
#define PF_CHECKSUM() (0xf ^ _nib1 ^ _nib2 ^ _nib3)

void LED_Init(void)
{
	// set PB2 as output (control of green LED)
	DDRB |= (1<<DDB2);
	LEDGRN_OFF;

}

void PF_init()
{
  LED_Init();
  _channel = 1;
  _toggle = 0;
  IR_DDR |= (1<<IR_PIN_DD);
  IR_PORT &= ~(1<<IR_PIN);
}

// Single output mode PWM
void PF_single_pwm(uint8_t channel, uint8_t output, uint8_t pwm) {
  LEDGRN_ON;
  _channel = channel-1;
  _nib1 = _toggle | _channel;
  _nib2 = SINGLE_OUTPUT | output;
  _nib3 = pwm;
  PF_send();
  PF_toggle();
  LEDGRN_OFF;
}

// Combo PWM mode
void PF_combo_pwm(uint8_t channel, uint8_t blue_speed, uint8_t red_speed)
{
  _channel = channel;
  _nib1 = ESCAPE | _channel;
  _nib2 = blue_speed;
  _nib3 = red_speed;
  PF_send();
}

//
// Private methods
//

// Pause function see "Transmitting Messages" in Power Functions PDF
void PF_pause(uint8_t count)
{
  uint8_t pause = 0;

  if(count == 0) {
    pause = 4 - (_channel + 1);
  } else if(count < 3) { // 1, 2
    pause = 5;
  } else {  // 3, 4, 5
    pause = 5 + (_channel + 1) * 2;
  }
  _delay_us(pause * 77); //MAX_MESSAGE_LENGTH
}

// Send the start/stop bit
void PF_start_stop_bit()
{
  PF_send_bit();
  _delay_us(START_STOP); // Extra pause for start_stop_bit
}

// Send a bit
void PF_send_bit() {
  for(uint8_t i = 0; i < 6; i++) {
    IR_PORT |=  (1<<IR_PIN);
    _delay_us(HALF_PERIOD);
    IR_PORT &= ~(1<<IR_PIN);
    _delay_us(HALF_PERIOD);
  }
}

void PF_send()
{
  uint8_t i, j;
  uint16_t message = _nib1 << 12 | _nib2 << 8 | _nib3 << 4 | PF_CHECKSUM();
  for(i = 0; i < 6; i++)
  {
    PF_pause(i);
    PF_start_stop_bit();
    for(j = 0; j < 16; j++) {
      PF_send_bit();
      _delay_us((0x8000 & (message << j)) != 0 ? HIGH_PAUSE : LOW_PAUSE);
    }
    PF_start_stop_bit();
  }
}
