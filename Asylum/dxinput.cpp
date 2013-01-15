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

#include "dxinput.h"

#define BUTTON_DOWN(obj, button) (obj.rgbButtons[button] & 0x80)

LPDIRECTINPUT8 dinput;
LPDIRECTINPUTDEVICE8 dimouse;
LPDIRECTINPUTDEVICE8 dikeyboard;
LPDIRECTINPUTDEVICE8 dijoystick;
DIMOUSESTATE mouse_state;

//keyboard input
char keys[256];

int Init_DirectInput (HWND hwnd)
{
	//initialize DIrectInput object
	HRESULT result = DirectInput8Create (GetModuleHandle (NULL),
										 DIRECTINPUT_VERSION,
										 IID_IDirectInput8,
										 (void**)&dinput,
										 NULL);

	if (result != DI_OK)
		return 0;

	//initialize the mouse
	result = dinput->CreateDevice (GUID_SysMouse, &dimouse, NULL);
	if (result != DI_OK)
		return 0;

	//initialize the keyboard
	result = dinput->CreateDevice (GUID_SysKeyboard, &dikeyboard, NULL);
	if (result != DI_OK)
		return 0;

	//clean return
	return 1;
}

int Init_Mouse (HWND hwnd)
{
	//set the data format for mouse input
	HRESULT result = dimouse->SetDataFormat (&c_dfDIMouse);
	if (result != DI_OK)
		return 0;

	//set the cooperative level
	//this will also hide the mouse pointer
	result = dimouse->SetCooperativeLevel (hwnd,
										   DISCL_EXCLUSIVE | DISCL_FOREGROUND);
	if (result != DI_OK)
		return 0;

	//everything is ohbe kaybe
	return 1;
}

int Mouse_X ()
{
	return mouse_state.lX;
}

int Mouse_Y ()
{
	return mouse_state.lY;
}

int Mouse_Button (int button)
{
	return BUTTON_DOWN (mouse_state, button);
}

void Poll_Mouse ()
{
	dimouse->GetDeviceState (sizeof(mouse_state), (LPVOID)&mouse_state);
}

void Kill_Mouse()
{
	if (dimouse != NULL)
	{
		dimouse->Unacquire();
		dimouse->Release();
		dimouse = NULL;
	}
}

int Init_Keyboard (HWND hwnd)
{
	//set the data format for mouse input
	HRESULT result = dikeyboard->SetDataFormat (&c_dfDIKeyboard);
	if (result != DI_OK)
		return 0;

	//set cooperative level
	result = dikeyboard->SetCooperativeLevel (hwnd,
											  DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	if (result != DI_OK)
		return 0;

	//acquire keyboard
	result = dikeyboard->Acquire ();
	if (result != DI_OK)
		return 0;

	//Everything is cool
	return 1;
}

void Poll_Keyboard ()
{
	dikeyboard->GetDeviceState (sizeof(keys), (LPVOID)&keys);
}

int Key_Down (int key)
{
	return (keys[key] & 0x80);
}

void Kill_Keyboard ()
{
	if (dikeyboard != NULL)
	{
		dikeyboard->Unacquire();
		dikeyboard->Release();
		dikeyboard = NULL;
	}
}
