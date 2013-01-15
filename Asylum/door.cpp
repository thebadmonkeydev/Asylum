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

#include "door.h"

door::door(char *filename, int x, int y)
{
	HRESULT result = D3DXGetImageInfoFromFile (filename, &info);
	if (result != D3D_OK)
	{
		//Error Code
	}

	image = LoadTexture (filename, D3DCOLOR_XRGB (255,0,255));

	//image properties
	numTiles = 10;

	width = info.Width / numTiles;
	height = info.Height;
	lastframe = numTiles - 1;
	curframe = 0;
	animdelay = 5;
	animcount = 0;

	movex = 0;
	movey = 0;

	position = new D3DXVECTOR3 ((float)x, (float)y, 0);

	opening = false;
	closing = false;
	used = false;
}

door::~door()
{
	//free image memory
	if (image != NULL)
	{
		image->Release();
		delete image;
	}

	//free vector memory
	if (position != NULL)
		delete position;
}

void door::move()
{
	if (opening)
		if (++animcount > animdelay)
		{
			//reset the counter
			animcount = 0;

			//animate the sprite
			if (closing)
				curframe--;
			else
				curframe++;

			if (curframe == lastframe)
				closing = true;
			else if (curframe < 0)
			{
				closing = false;
				opening = false;
				used = true;
			}
		}else{}
	else
		curframe = 0;
}

void door::draw(LPD3DXSPRITE sprite_handler, int Offset)
{
	RECT rect;
	D3DXVECTOR3 temp_position ((float)position->x - Offset, (float)position->y, position->z);

	if (!opening)
	{
		rect.left = 0;
		rect.top = 0;
		rect.right = rect.left + width;
		rect.bottom = rect.top + height;

		sprite_handler->Draw (image,
							  &rect,
							  NULL,
							  &temp_position,
							  D3DCOLOR_XRGB (255,255,255));
	}else
	{
		rect.left = ((curframe % numTiles) * width);
		rect.top = 0;
		rect.right = rect.left + width;
		rect.bottom = height;

		sprite_handler->Draw (image,
							  &rect,
							  NULL,
							  &temp_position,
							  D3DCOLOR_XRGB (255,255,255));
	}
}

void door::open()
{
	opening = true;
}

bool door::isClosing()
{
	return closing;
}

bool door::isUsed()
{
	return used;
}
