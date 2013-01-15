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

/* System Includes */
#include "asincludes.h"

/* Project Includes */
#include "game.h"

/* Window event callback function */
LRESULT WINAPI WinProc (HWND hWnd,
						UINT msg,
						WPARAM wParam,
						LPARAM lParam )
{
	switch (msg)
	{
	case WM_QUIT:
	case WM_DESTROY:
		//Release the Direct3D device
		if (d3ddev != NULL)
			d3ddev->Release();

		//Release the Direct3d object
		if (d3d != NULL)
			d3d->Release();

		//Call the "front-end"shutdown function
		Game_End(hWnd);

		//Tell Windows to kill this program
		PostQuitMessage (0);

		return 0;
	}

	return DefWindowProc (hWnd, msg, wParam, lParam);
}

/* Helper function to setup the window properties */
ATOM MyRegisterClass (HINSTANCE hInstance)
{
	//Create the window class structure
	WNDCLASSEX wc;
	wc.cbSize = sizeof (WNDCLASSEX);

	//Fill the structure
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC) WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor (NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH) GetStockObject (BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = APPTITLE;
	wc.hIconSm = NULL;

	//Setup the window with the clss info
	return RegisterClassEx (&wc);
}

/* Entry Point for the Windows program */
int WINAPI WinMain (HINSTANCE hInstance,
					HINSTANCE hPrevInstance,
					LPSTR lpCmdLine,
					int nShowCmd)
{
	MSG msg;
	HWND hWnd;

	//register class
	MyRegisterClass (hInstance);

	//setup the screen in windowed or fullscreen?
	DWORD style;
	if (FULLSCREEN)
		style = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP;
	else
		style = WS_OVERLAPPED;

	//create new window
	hWnd = CreateWindow (APPTITLE,
						 APPTITLE,
						 style,
						 CW_USEDEFAULT,
						 CW_USEDEFAULT,
						 SCREEN_WIDTH,
						 SCREEN_HEIGHT,
						 NULL,
						 NULL,
						 hInstance,
						 NULL);

	//was there an error creating the window?
	if (!hWnd)
		return FALSE;

	//display the window
	ShowWindow (hWnd, nShowCmd);
	UpdateWindow (hWnd);

	if (!Init_Direct3D (hWnd, SCREEN_WIDTH, SCREEN_HEIGHT, FULLSCREEN))
	{
		MessageBox (hWnd, "Error Initializing Direct3D.", "Error", MB_OK);
		return 0;
	}

	if (!Init_DirectSound (hWnd))
	{
		MessageBox (hWnd, "Error Initializing DirectSound.", "Error", MB_OK);
		return 0;
	}

	if (!Init_DirectInput (hWnd))
	{
		MessageBox (hWnd, "Error Initializing DirectInput.", "Error", MB_OK);
		return 0;
	}

	//Initialize the game
	if (!Game_Init (hWnd))
	{
		MessageBox (hWnd, "Error initializing the game.", "Error", MB_OK);
		return 0;
	}

	ShowCursor (false);

	//main message loop
	int done = 0;

	while (!done)
	{
		if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
		{
			//look for quit message
			if (msg.message == WM_QUIT)
				done = 1;

			//decode and pass the message
			TranslateMessage (&msg);
			DispatchMessage (&msg);
		}
		else
			//process game loop (prevents running after window is closed)
			Game_Run (hWnd);
	}

	return msg.wParam;
}
