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

#include "ASO.h"

/*
	Default Constructor
*/
ASO::ASO()
{
}

/*
	Bitmap File Frontend Constructor
*/
ASO::ASO(char *bmpfile, int x, int y)
{
	//Load image and set image attributes
	HRESULT result = D3DXGetImageInfoFromFile (bmpfile, &info);
	if (result != D3D_OK)
	{
		//Error Code
	}

	width = info.Width;
	height = info.Height;

	image = LoadTexture (bmpfile, D3DCOLOR_XRGB (255,0,255));

	//set position
	position = new D3DXVECTOR3((float)x, (float)y, 0);

	//Movemeny properties
	movex = movey = 0;
}

/*
	Destructor
*/
ASO::~ASO(void)
{
	if (image != NULL || image != 0)
		image->Release();
	delete position;
}

/*
	Display Function
*/
void ASO::draw(LPD3DXSPRITE sprite_handler, int Offset)
{
	RECT srcRect;
	D3DXVECTOR3 temp_position (position->x - Offset, position->y, position->z);

	srcRect.left = 0;
	srcRect.top = 0;
	srcRect.right = width;
	srcRect.bottom = height;

	sprite_handler->Draw (image,
						  &srcRect,
						  NULL,
						  &temp_position,
						  D3DCOLOR_XRGB (255,255,255));
}

void ASO::stopFall()
{
}

int ASO::getWidth()
{
	return width;
}

int ASO::getHeight()
{
	return height;
}

int ASO::getX()
{
	return (int)position->x;
}

int ASO::getY()
{
	return (int)position->y;
}

void ASO::setPosition (int x, int y)
{
	position->x = (float)x;
	position->y = (float)y;
}
