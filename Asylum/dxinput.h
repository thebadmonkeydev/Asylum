/*	This file is part of Asylum

	2D Engine Development Project

    Copyright (C) 2009 Michael Kelly

	Asylum is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Foobar is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
*/

/* Multiple include protection */
#ifndef _DXINPUT_H
#define _DXINPUT_H

#include <dinput.h>

//function prototypes
int Init_DirectInput ( HWND );
int Init_Keyboard ( HWND );
void Poll_Keyboard ();
int Key_Down ( int );
void Kill_Keyboard ();
void Poll_Mouse ();
int Init_Mouse ();
int Init_Mouse ( HWND );
int Mouse_Button ( int );
int Mouse_X ();
int Mouse_Y ();
void Kill_Mouse ();

//DirectInput objects, devices, and states
extern LPDIRECTINPUT8 dinput;
extern LPDIRECTINPUTDEVICE8 dimouse;
extern LPDIRECTINPUTDEVICE8 dikeyboard;
extern DIMOUSESTATE mouse_state;

#endif
