#define F_CPU 14745600UL     /* Quarz mit 14.74560 Mhz */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <stdlib.h>
#include <inttypes.h>
#include <util/delay.h>

#include "PowerFunctions.h"
#include "usart.h"
#include "pfparser.h"

PF_DATA_t PFData;

void long_delay(uint16_t ms)
{
    for(; ms>0; ms--) _delay_ms(1);
}

int main (void)
{

   PF_init();
   
   pf_parserInit();
   usart_init(57600);
   sei();
	
   long_delay(500);

	while (1)
	{
      
      if(pf_parserNewData() == 1) {
         PF_single_pwm(PFData.channel, PFData.port, PFData.val);
         pf_parserNewDataClear();
      }
      
	}

	return 0;
}
