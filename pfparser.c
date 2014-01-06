#include <inttypes.h>
#include "pfparser.h"
#include <avr/io.h>
#include <stdbool.h>


// pf protocol parser state machine
#define PFSTATE_IDLE      0
#define PFSTATE_SYNC1     1
#define PFSTATE_SYNC2     2
#define PFSTATE_CLASS     3
#define PFSTATE_CHANNEL   4
#define PFSTATE_PORT      5
#define PFSTATE_DATA_RDY  6

// pf protocoll identifier
#define PF_CLASS_PWM   0x01

#define PF_SYNC1_CHAR  0x70
#define PF_SYNC2_CHAR  0x66



void pf_parserInit(void) {
   _pfDataReady = 0;
   PFData.channel = 0;
   PFData.port = 0;
   PFData.val = 0;
}

uint8_t pf_parserNewData(void)
{
  if (_pfDataReady == 1)
   return 1;
  else
   return 0;
}

void pf_parserNewDataClear(void)
{
  _pfDataReady = 0;
}

// this function should be called within the UART RX ISR
void pf_parser(uint8_t c)
{
        //LEDGRN_TOGGLE;
		static uint8_t pfstate = PFSTATE_IDLE;

        if (_pfDataReady == 0) {
			switch(pfstate)
			{
					case PFSTATE_IDLE: // check 1st sync byte
							if (c == PF_SYNC1_CHAR) pfstate = PFSTATE_SYNC1;
							else pfstate = PFSTATE_IDLE; // out of synchronization
							break;

					case PFSTATE_SYNC1: // check 2nd sync byte
							//LEDGRN_TOGGLE;
							if (c == PF_SYNC2_CHAR) pfstate = PFSTATE_SYNC2;
							else pfstate = PFSTATE_IDLE; // out of synchronization
							break;

					case PFSTATE_SYNC2: // check msg class to be NAV
							if (c == PF_CLASS_PWM) pfstate = PFSTATE_CLASS;
							else pfstate = PFSTATE_IDLE; // unsupported message class
							break;


					case PFSTATE_CLASS: // 1st message length byte
							PFData.channel = c;
							pfstate = PFSTATE_CHANNEL;
							break;

					case PFSTATE_CHANNEL: // 1st message length byte
							PFData.port = c;
							pfstate = PFSTATE_PORT;
							break;

					case PFSTATE_PORT: // 1st message length byte
							PFData.val = c;
							 _pfDataReady = 1;
							pfstate = PFSTATE_IDLE;
							break;

					default: // unknown pf state
							pfstate = PFSTATE_IDLE;
							break;
			}
		}

}


