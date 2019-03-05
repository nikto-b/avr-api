#include "digitalRegisters.c"

//for counting ports
#define PA 0
#define PB 0
#define PC 0
#define PD 0
#define PE 0
#define PF 0
#define PG 0
#define PH 0
#define PI 0
#define PJ 0
#define PK 0
#define PL 0


#if defined(PORTA)																	//code for using port A
	#pragma message "PORTA found"
	#define setDirA(_state) DDRA=_state												//set direction of port A
	#define setBitDirA(_bit, _state) DDRA=((DDRA&~(_state<<_bit))|_state<<_bit	)	//set direction of bit "_bit" on port A
	#define toggleBitDirA(_bit) DDRA^=_BV(_bit)										//toggle direction of bit "_bit" on port A
	#define setStateA(_state) PORTA=_state											//set state of port A
	#define setBitStateA(_bit, _state)  PORTA = PORTA & ~(1 << _bit) | _state<<_bit	//set bit "_bit" of port A to state "_state"
	#define toggleBitStateA(_bit) PORTA^=_BV(_bit)									//toggle bit "_bit" of port A
	#define getStateA() PINA 														//return state of port A
	#define getStateBitA(_bit) ((PINA>>_bit)&1)										//return state of bit "_bit" of port A
	#define setBytePullupA(_byte) setDirA(~_byte);setStateA(_byte)					//set pullup on pins marked by "_byte" of port A
	#define setPullupA() setBytePullupA(0b11111111)									//set pullup on all pins of port A
	#define setBitPullupA(_bit) setBytePullupA(_BV(_bit))							//set pullup on "_bit" pin of port A
	#undef PA 
	#define PA 1
#endif //if defined(PORTA)

#if defined(PORTB)																	//code for using port B
	#pragma message "PORTB found"
	#define setDirB(_state) DDRB=_state												//set direction of port B
	#define setBitDirB(_bit, _state)  DDRB=((DDRB&~(_state<<_bit))|_state<<_bit	)	//set direction of bit "_bit" on port B
	#define toggleBitDirB(_bit) DDRB^=_BV(_bit)										//toggle direction of bit "_bit" on port B
	#define setStateB(_state) PORTB=_state											//set state of port B
	#define setBitStateB(_bit, _state) PORTB = PORTB & ~(1 << _bit) | _state<<_bit	//set bit "_bit" of port B to state "_state"
	#define toggleBitStateB(_bit) PORTB^=_BV(_bit)									//toggle bit "_bit" of port B
	#define getStateB() PINB 														//return state of port B
	#define getStateBitB(_bit) ((PINA>>_bit)&1)										//return state of bit "_bit" of port B
	#define setBytePullupB(_byte) setDirB(~_byte);setStateB(_byte)					//set pullup on pins marked by "_byte" of port B
	#define setPullupB() setBytePullupB(0b11111111)									//set pullup on all pins of port B
	#define setBitPullupB(_bit) setBytePullupB(_BV(_bit))							//set pullup on "_bit" pin of port B
	#undef PB
	#define PB 1
#endif //if defined(PORTB)

#if defined(PORTC)																	//code for using port C
	#pragma message "PORTC found"
	#define setDirC(_state) DDRC=_state												//set direction of port C
	#define setBitDirC(_bit, _state) DDRC=((DDRC&~(_state<<_bit))|_state<<_bit	)	//set direction of bit "_bit" on port C
	#define toggleBitDirC(_bit) DDRC^=_BV(_bit)										//toggle direction of bit "_bit" on port C
	#define setStateC(_state) PORTC=_state											//set state of port C
	#define setBitStateC(_bit, _state)  PORTC = PORTC & ~(1 << _bit) | _state<<_bit	//set bit "_bit" of port C to state "_state"
	#define toggleBitStateC(_bit) PORTC^=_BV(_bit)									//toggle bit "_bit" of port C
	#define getStateC() PINC 														//return state of port C
	#define getStateBitC(_bit) ((PINC>>_bit)&1)										//return state of bit "_bit" of port C
	#define setBytePullupC(_byte) setDirC(~_byte);setStateC(_byte)					//set pullup on pins marked by "_byte" of port C
	#define setPullupC() setBytePullupC(0b11111111)									//set pullup on all pins of port C
	#define setBitPullupC(_bit) setBytePullupC(_BV(_bit))							//set pullup on "_bit" pin of port C
	#undef PC
	#define PC 1
#endif //if defined(PORTC)

#if defined(PORTD)																	//code for using port D
	#pragma message "PORTD found"
	#define setDirA(_state) DDRA=_state												//set direction of port D
	#define setBitDirD(_bit, _state)  DDRD=((DDRD&~(_state<<_bit))|_state<<_bit	)	//set direction of bit "_bit" on port D
	#define toggleBitDirD(_bit) DDRD^=_BV(_bit)										//toggle direction of bit "_bit" on port D
	#define setStateD(_state) PORTD=_state											//set state of port D
	#define setBitStateD(_bit, _state)  PORTD = PORTD & ~(1 << _bit) | _state<<_bit	//set bit "_bit" of port D to state "_state"
	#define toggleBitStateD(_bit) PORTD^=_BV(_bit)									//toggle bit "_bit" of port D
	#define getStateD() PIND 														//return state of port D
	#define getStateBitD(_bit) ((PIND>>_bit)&1)										//return state of bit "_bit" of port D
	#define setBytePullupD(_byte) setDirD(~_byte);setStateD(_byte)					//set pullup on pins marked by "_byte" of port D
	#define setPullupD() setBytePullupD(0b11111111)									//set pullup on all pins of port D
	#define setBitPullupD(_bit) setBytePullupD(_BV(_bit))							//set pullup on "_bit" pin of port D
	#undef PD
	#define PD 1 
#endif //if defined(PORTD)

#if defined(PORTE)																	//code for using port E
	#pragma message "PORTE found"
	#define setDirE(_state) DDRE=_state												//set direction of port E
	#define setBitDirE(_bit, _state)  DDRE=((DDRE&~(_state<<_bit))|_state<<_bit	)	//set direction of bit "_bit" on port E
	#define toggleBitDirE(_bit) DDRE^=_BV(_bit)										//toggle direction of bit "_bit" on port E
	#define setStateE(_state) PORTE=_state											//set state of port E
	#define setBitStateE(_bit, _state) PORTE = PORTE & ~(1 << _bit) | _state<<_bit	//set bit "_bit" of port E to state "_state"
	#define toggleBitStateE(_bit) PORTE^=_BV(_bit)									//toggle bit "_bit" of port E
	#define getStateE() PINE 														//return state of port E
	#define getStateBitE(_bit) ((PINE>>_bit)&1)										//return state of bit "_bit" of port E
	#define setBytePullupE(_byte) setDirE(~_byte);setStateE(_byte)					//set pullup on pins marked by "_byte" of port E
	#define setPullupE() setBytePullupE(0b11111111)									//set pullup on all pins of port E
	#define setBitPullupE(_bit) setBytePullupE(_BV(_bit))							//set pullup on "_bit" pin of port E
	#undef PE
	#define PE 1
#endif //if defined(PORTE)

#if defined(PORTF)																	//code for using port F
	#pragma message "PORTF found"
	#define setDirF(_state) DDRF=_state												//set direction of port F
	#define setBitDirF(_bit, _state) DDRF=((DDRF&~(_state<<_bit))|_state<<_bit	)	//set direction of bit "_bit" on port F
	#define toggleBitDirF(_bit) DDRF^=_BV(_bit)										//toggle direction of bit "_bit" on port F
	#define setStateF(_state) PORTF=_state											//set state of port F
	#define setBitStateF(_bit, _state)  PORTF = PORTF & ~(1 << _bit) | _state<<_bit	//set bit "_bit" of port A to state "_state"
	#define toggleBitStateF(_bit) PORTF^=_BV(_bit)									//toggle bit "_bit" of port F
	#define getStateF() PINF 														//return state of port A
	#define getStateBitF(_bit) ((PINF>>_bit)&1)										//return state of bit "_bit" of port A
	#define setBytePullupF(_byte) setDirF(~_byte);setStateF(_byte)					//set pullup on pins marked by "_byte" of port F
	#define setPullupF() setBytePullupF(0b11111111)									//set pullup on all pins of port F
	#define setBitPullupF(_bit) setBytePullupF(_BV(_bit))							//set pullup on "_bit" pin of port F
	#undef PF
	#define PF 1
#endif //if defined(PORTF)

#if defined(PORTG)																	//code for using port G
	#pragma message "PORTG found"
	#define setDirG(_state) DDRG=_state												//set direction of port G
	#define setBitDirG(_bit, _state) DDRG=((DDRG&~(_state<<_bit))|_state<<_bit	)	//set direction of bit "_bit" on port G
	#define toggleBitDirG(_bit) DDRG^=_BV(_bit)										//toggle direction of bit "_bit" on port G
	#define setStateG(_state) PORTG=_state											//set state of port G
	#define setBitStateG(_bit, _state)  PORTG = PORTG & ~(1 << _bit) | _state<<_bit	//set bit "_bit" of port G to state "_state"
	#define toggleBitStateG(_bit) PORTG^=_BV(_bit)									//toggle bit "_bit" of port G
	#define getStateG() PING 														//return state of port G
	#define getStateBitG(_bit) ((PING>>_bit)&1)										//return state of bit "_bit" of port G
	#define setBytePullupG(_byte) setDirG(~_byte);setStateG(_byte)					//set pullup on pins marked by "_byte" of port G
	#define setPullupG() setBytePullupG(0b11111111)									//set pullup on all pins of port G
	#define setBitPullupG(_bit) setBytePullupG(_BV(_bit))							//set pullup on "_bit" pin of port G
	#undef PG
	#define PG 1
#endif //if defined(PORTG)

#if defined(PORTH)																	//code for using port H
	#pragma message "PORTH found"
	#define setDirH(_state) DDRH=_state												//set direction of port H
	#define setBitDirH(_bit, _state)  DDRH=((DDRH&~(_state<<_bit))|_state<<_bit	)	//set direction of bit "_bit" on port H
	#define toggleBitDirH(_bit) DDRH^=_BV(_bit)										//toggle direction of bit "_bit" on port H
	#define setStateH(_state) PORTH=_state											//set state of port H
	#define setBitStateH(_bit, _state)  PORTH = PORTH & ~(1 << _bit) | _state<<_bit	//set bit "_bit" of port H to state "_state"
	#define toggleBitStateH(_bit) PORTH^=_BV(_bit)									//toggle bit "_bit" of port H
	#define getStateH() PINH 														//return state of port H
	#define getStateBitH(_bit) ((PINH>>_bit)&1)										//return state of bit "_bit" of port H
	#define setBytePullupH(_byte) setDirH(~_byte);setStateH(_byte)					//set pullup on pins marked by "_byte" of port H
	#define setPullupH() setBytePullupH(0b11111111)									//set pullup on all pins of port H
	#define setBitPullupH(_bit) setBytePullupH(_BV(_bit))							//set pullup on "_bit" pin of port H
	#undef PH 
	#define PH 1
#endif //if defined(PORTH)

#if defined(PORTI)																	//code for using port I
	#pragma message "PORTI found"
	#define setDirI(_state) DDRI=_state												//set direction of port I
	#define setBitDirI(_bit, _state)  DDRI=((DDRI&~(_state<<_bit))|_state<<_bit	)	//set direction of bit "_bit" on port I
	#define toggleBitDirI(_bit) DDRI^=_BV(_bit)										//toggle direction of bit "_bit" on port I
	#define setStateI(_state) PORTI=_state											//set state of port I
	#define setBitStateI(_bit, _state)  PORTI = PORTI & ~(1 << _bit) | _state<<_bit	//set bit "_bit" of port I to state "_state"
	#define toggleBitStateI(_bit) PORTI^=_BV(_bit)									//toggle bit "_bit" of port I
	#define getStateI() PINI 														//return state of port I
	#define getStateBitI(_bit) ((PINI>>_bit)&1)										//return state of bit "_bit" of port I
	#define setBytePullupI(_byte) setDirI(~_byte);setStateI(_byte)					//set pullup on pins marked by "_byte" of port I
	#define setPullupI() setBytePullupI(0b11111111)									//set pullup on all pins of port I
	#define setBitPullupI(_bit) setBytePullupI(_BV(_bit))							//set pullup on "_bit" pin of port I
	#undef PI
	#define PI 1
#endif //if defined(PORTI)

#if defined(PORTJ)																	//code for using port J
	#pragma message "PORTJ found"
	#define setDirJ(_state) DDRJ=_state												//set direction of port J
	#define setBitDirJ(_bit, _state)  DDRJ=((DDRJ&~(_state<<_bit))|_state<<_bit	)	//set direction of bit "_bit" on port J
	#define toggleBitDirJ(_bit) DDRJ^=_BV(_bit)										//toggle direction of bit "_bit" on port J
	#define setStateJ(_state) PORTJ=_state											//set state of port J
	#define setBitStateJ(_bit, _state)  PORTJ = PORTJ & ~(1 << _bit) | _state<<_bit	//set bit "_bit" of port J to state "_state"
	#define toggleBitStateJ(_bit) PORTJ^=_BV(_bit)									//toggle bit "_bit" of port J
	#define getStateJ() PINJ 														//return state of port J
	#define getStateBitJ(_bit) ((PINJ>>_bit)&1)										//return state of bit "_bit" of port J
	#define setBytePullupJ(_byte) setDirJ(~_byte);setStateJ(_byte)					//set pullup on pins marked by "_byte" of port J
	#define setPullupJ() setBytePullupJ(0b11111111)									//set pullup on all pins of port J
	#define setBitPullupJ(_bit) setBytePullupJ(_BV(_bit))							//set pullup on "_bit" pin of port J
	#undef PJ
	#define PJ 1
#endif //if defined(PORTJ)

#if defined(PORTK)																	//code for using port K
	#pragma message "PORTK found"
	#define setDirK(_state) DDRK=_state												//set direction of port K
	#define setBitDirK(_bit, _state)  DDRK=((DDRK&~(_state<<_bit))|_state<<_bit	)	//set direction of bit "_bit" on port K
	#define toggleBitDirK(_bit) DDRK^=_BV(_bit)										//toggle direction of bit "_bit" on port K
	#define setStateK(_state) PORTK=_state											//set state of port K
	#define setBitStateK(_bit, _state)  PORTK = PORTK & ~(1 << _bit) | _state<<_bit	//set bit "_bit" of port K to state "_state"
	#define toggleBitStateK(_bit) PORTK^=_BV(_bit)									//toggle bit "_bit" of port K
	#define getStateK() PINK 														//return state of port K
	#define getStateBitK(_bit) ((PINK>>_bit)&1)										//return state of bit "_bit" of port K
	#define setBytePullupK(_byte) setDirK(~_byte);setStateK(_byte)					//set pullup on pins marked by "_byte" of port K
	#define setPullupK() setBytePullupK(0b11111111)									//set pullup on all pins of port K
	#define setBitPullupK(_bit) setBytePullupK(_BV(_bit))							//set pullup on "_bit" pin of port K
	#undef PK
	#define PK 1
#endif //if defined(PORTK)

#if defined(PORTL)																	//code for using port L
	#pragma message "PORTL found"
	#define setDirL(_state) DDRL=_state												//set direction of port L
	#define setBitDirL(_bit, _state)  DDRL=((DDRL&~(_state<<_bit))|_state<<_bit	)	//set direction of bit "_bit" on port L
	#define toggleBitDirL(_bit) DDRA^=_BV(_bit)										//toggle direction of bit "_bit" on port L
	#define setStateL(_state) PORTA=_state											//set state of port L
	#define setBitStateL(_bit, _state)  PORTL = PORTL & ~(1 << _bit) | _state<<_bit	//set bit "_bit" of port L to state "_state"
	#define toggleBitStateL(_bit) PORTA^=_BV(_bit)									//toggle bit "_bit" of port L
	#define getStateL() PINL														//return state of port L
	#define getStateBitL(_bit) ((PINL>>_bit)&1)										//return state of bit "_bit" of port L
	#define setBytePullupL(_byte) setDirL(~_byte);setStateL(_byte)					//set pullup on pins marked by "_byte" of port L
	#define setPullupL() setBytePullupL(0b11111111)									//set pullup on all pins of port L
	#define setBitPullupL(_bit) setBytePullupL(_BV(_bit))							//set pullup on "_bit" pin of port L
	#undef PL
	#define PL 1
#endif //if defined(PORTL)	

#define NUM_OF_PORTS PA+PB+PC+PD+PE+PF+PG+PH+PI+PJ+PK+PL

void pinMode(uint8_t _pin, uint8_t _state);

int digitalRead(uint8_t _pin);

void digitalWrite(uint8_t _pin, bool _state);


