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
#include <d3d9.h>
#include <d3dx9.h>

/* Project Includes */
#include "dxgraphics.h"

/* Global Variables */
LPDIRECT3D9 d3d = NULL;
LPDIRECT3DDEVICE9 d3ddev = NULL;
LPDIRECT3DSURFACE9 backbuffer = NULL;

/* Initialize Direct3D Resources */
int Init_Direct3D (HWND hwnd, int width, int height, int fullscreen)
{
	//initialize Direct3D
	d3d = Direct3DCreate9 (D3D_SDK_VERSION);

	if (d3d == NULL)
	{
		MessageBox (hwnd, "Error initializing Direct3D", "Error", MB_OK);
		return 0;
	}

	//Set Direct3D presentation parameters
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory (&d3dpp, sizeof (d3dpp));

	d3dpp.Windowed = (!fullscreen);
	d3dpp.SwapEffect = D3DSWAPEFFECT_COPY;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferWidth = width;
	d3dpp.BackBufferHeight = height;
	d3dpp.hDeviceWindow = hwnd;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	//Create trhe Direct3D Device
	d3d->CreateDevice (D3DADAPTER_DEFAULT,
					   D3DDEVTYPE_HAL,
					   hwnd,
					   D3DCREATE_SOFTWARE_VERTEXPROCESSING,
					   &d3dpp,
					   &d3ddev);

	if (d3ddev == NULL)
	{
		MessageBox (hwnd, "Error creating Direct3D device.", "Error", MB_OK);
		return 0;
	}

	//clear the backbuffer to black
	d3ddev->Clear (0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,0), 1.0f, 0);

	//create pointer to the back buffer
	d3ddev->GetBackBuffer (0, 0, D3DBACKBUFFER_TYPE_MONO, &backbuffer);

	return 1;
}

/* Loads a specified bitmap file into memory */
LPDIRECT3DSURFACE9 LoadSurface (char *filename, D3DCOLOR transcolor)
{
	LPDIRECT3DSURFACE9 image = NULL;
	D3DXIMAGE_INFO info;
	HRESULT result;

	//Get width and height from file
	result = D3DXGetImageInfoFromFile (filename, &info);
	if (result != D3D_OK)
		return NULL;

	//Create Surface
	result = d3ddev->CreateOffscreenPlainSurface (info.Width,
												  info.Height,
												  D3DFMT_X8R8G8B8,
												  D3DPOOL_DEFAULT,
												  &image,
												  NULL);

	if (result != D3D_OK)
		return NULL;

	//Load Surface
	result = D3DXLoadSurfaceFromFile (image,
									  NULL,
									  NULL,
									  filename,
									  NULL,
									  D3DX_DEFAULT,
									  transcolor,
									  NULL);

	//make sure file was loaded
	if (result != D3D_OK)
		return NULL;

	return image;
}

LPDIRECT3DTEXTURE9 LoadTexture (char *filename, D3DCOLOR transcolor)
{
	//the texture pointer
	LPDIRECT3DTEXTURE9 texture = NULL;

	//the struct for reading bitmap file info
	D3DXIMAGE_INFO info;

	//standard Windows return value
	HRESULT result;

	//get width and height from bitmap file
	result = D3DXGetImageInfoFromFile (filename, &info);

	if (result != D3D_OK)
		return NULL;

	//create the new texture by loading a bitmap image file
	D3DXCreateTextureFromFileEx (d3ddev,
								 filename,
								 info.Width,
								 info.Height,
								 1,
								 D3DPOOL_DEFAULT,
								 D3DFMT_UNKNOWN,
								 D3DPOOL_DEFAULT,
								 D3DX_DEFAULT,
								 D3DX_DEFAULT,
								 transcolor,
								 &info,
								 NULL,
								 &texture);

	//make sure the bitmap texture was loaded correctly
	if (result != D3D_OK)
		return NULL;

	return texture;
}