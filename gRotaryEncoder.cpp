#include "Arduino.h"
#include "gRotaryEncoder.h"

re::re()
{
	_re_init();
}

re::re(int i_pin1, int i_pin2)
{
	// Initialize with user-provided pins
	_p1 = i_pin1;
	_p2 = i_pin2;
	_re_init();
}

bool re::readPins()
{
	// Read the pins, if anything has changed, set the dir and count, return true.
	// Otherwise, return false, clear dir and count (both = 0)
	if (millis() - _lastRead > debounce_timer)
	{
		_lastRead = millis();
		// Debounce timer has expired, check the pins.
		pin1_val = digitalRead(_p1);
		pin2_val = digitalRead(_p2);
		
		if (pin1_val != _last_p1 || pin2_val != _last_p2)
		{
			// Pins have changed.
			if (millis() - _lastDirSet > inactivity_timer)
			{
				// The user hasn't turned the knob in a while, determine initial spinDirection.
				steps = 1;
				_dirSense();
			}
			else
			{
				// spinDirection is assumed to be previous spinDirection
				steps++;
				_lastDirSet = millis();
			}
			
			_last_p1 = pin1_val;
			_last_p2 = pin2_val;
			
			return true;
		}
		else
		{
			// Pin values have not changed.  
			return false;
		}
	}
	else
	{
		steps = 0;
		return false;
	}
}

void re::reset()
{
	steps = 0;
	pin1_val = digitalRead(_p1);
	pin2_val = digitalRead(_p2);
}

void re::_dirSense()
{
	_lastDirSet = millis();
	
	if (_last_p1 == 0 && _last_p2 == 0)
	{
		if (pin1_val== 0 && pin2_val== 1)
		{
		  //counterclockwise
		  spinDirection = 2;					//CCW
		}
		else if (pin1_val== 1 && pin2_val== 1)
		{
		  // clockwise
		  spinDirection = 1;					//CW
		}
		else
		{
		  // unknown
		  spinDirection = 0;					//Unknown
		}
	}
	else if (_last_p1 == 1 && _last_p2 ==1)
	{
		if (pin1_val== 0 && pin2_val== 0)
		{
		  //counterclockwise
		  spinDirection = 2;					//CCW
		}
		else if (pin1_val== 0 && pin2_val== 1)
		{
		  // clockwise
		  spinDirection = 1;					//CW
		}
		else
		{
		  // unknown
		  spinDirection = 0;					//Unknown
		}
	}
	else if (_last_p1 == 0 && _last_p2 ==1)
	{
		if (pin1_val== 1 && pin2_val== 1)
		{
		  //counterclockwise
		  spinDirection = 2;					//CCW
		}
		else if (pin1_val== 0 && pin2_val== 0)
		{
		  // clockwise
		  spinDirection = 1;					//CW
		}
		else
		{
		  // unknown
		  spinDirection = 0;					//Unknown
		}
	}
}

void re::_re_init()
{
	// Initialize the object
	pinMode(_p1, INPUT_PULLUP);
	pinMode(_p2, INPUT_PULLUP);
	pin1_val = digitalRead(_p1);
	pin2_val = digitalRead(_p2);
}