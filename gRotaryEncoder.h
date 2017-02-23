/*
 *  gRotaryEncoder.h
 *
 */
#ifndef gRotaryEncoder_h
#define gRotaryEncoder_h

#include "Arduino.h"

class re
{
  public:
    re();
	re(int, int);					// Init with user-pins
	//re(int, int, int, int);		// Init with user pins and timers
	bool 		readPins();
	void 		reset();
	uint32_t  	steps = 0;
	uint32_t	count = 0;			// an alias for steps.
	uint8_t 	spinDirection = 0;
	uint8_t 	pin1_val = 0;
	uint8_t 	pin2_val = 0;
	uint16_t 	debounce_timer = 3;
	uint16_t 	inactivity_timer = 150;
  private:
	void 		_re_init();
	void 		_dirSense();
	uint32_t 	_p1 = D5;
	uint32_t 	_p2 = D6;
	uint32_t 	_last_p1 = 0;
	uint32_t 	_last_p2 = 0;
	uint32_t 	_lastRead = 0;
	uint32_t 	_lastDirSet = 0;
};


#endif
