//LCD12864Menu.h

#ifndef _LCD12864MENU_h
#define _LCD12864MENU_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "homephone.h"

class LCD12864Menu
{
private:
	homephone* Screens;

	
public:
	LCD12864Menu(homephone* screens)
	{
		Screens = screens;
	}
	void Init();

	void MoveUp();
	void MoveDown();
	void Next();
	void Back();

	void Execute();
};

#endif