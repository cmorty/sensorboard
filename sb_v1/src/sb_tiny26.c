#include "usiTwiSlave.h"
#include <avr/interrupt.h>
#include <string.h>

static uint16_t readADC(uint8_t channel) {
	uint8_t i;
	uint16_t result = 0;
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1);
	ADMUX = channel | (1 << REFS0);
	ADCSRA |= (1 << ADSC);
	while (ADCSRA & (1 << ADSC))
		;
	for (i = 0; i < 4; i++) {
		ADCSRA |= (1 << ADSC);
		while (ADCSRA & (1 << ADSC))
			;
		result += ADCW;
	}
	ADCSRA &= ~(1 << ADEN);
	result /= 4;
	return result;
}

#define ADCN 8
#if ADCN * 2 > TWI_TX_BUFFER_SIZE
#error TXbuffer to small
#endif

static uint8_t map[ADCN] = { 0, 1, 6, 7, 2, 3, 4, 5 };
static uint16_t vals[ADCN];

static uint8_t cbread(uint8_t len){

	if(len == 1 && usiTwiRxBuf[0] == 1){
		usiTwiTxBuf[0] = 1;
		usiTwiTxBuf[1] = ADCN;
		return 2;
	}
	return 0;
}

static uint8_t cbwrite(void){

	memcpy(vals, usiTwiTxBuf, sizeof(vals));
	return sizeof(vals);


}


int main(){
	usiTwiSlaveCB(cbread, cbwrite);
	usiTwiSlaveInit();
	sei();

	for(uint8_t i = 0; i < sizeof(map); i++){
		vals[i] = readADC(map[i]);
	}



}
