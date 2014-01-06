#ifndef _PFPARSER_H
#define _PFPARSER_H

#include <inttypes.h>

uint8_t _pfDataReady;

typedef struct
{
        uint8_t         channel;          // flags
        uint8_t         port;         // number of satelites
        uint8_t         val;         // type of satfix
} PF_DATA_t;

//here you will find the current gps info
extern PF_DATA_t PFData;      // measured position (last gps record)

// this function should be called within the UART RX ISR
extern void pf_parserInit(void);
extern uint8_t pf_parserNewData(void);
extern void pf_parserNewDataClear(void);
extern void pf_parser(uint8_t c);

#endif //_PFPARSER_H
