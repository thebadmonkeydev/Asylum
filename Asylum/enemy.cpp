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

#include "enemy.h"

enemy::enemy(char *bitmapfile, int x, int y, int paceDistance)
{
	image = LoadTexture (bitmapfile, D3DCOLOR_XRGB (255,0,255));

	HRESULT result = D3DXGetImageInfoFromFile (bitmapfile, &info);
	if (result != D3D_OK)
	{
		//Error Code
	}

	//Bitmap control variables
	numTiles = 5;
	width = info.Width / numTiles;
	height = info.Height / 2;

	//animation variables
	position = new D3DXVECTOR3((float)x, (float)y, 0);
	direction = -1;
	movex = 7;
	movey = 5;
	animdelay = 5;
	animcount = 0;
	curframe = 0;
	lastframe = numTiles - 1;
	paceSize = paceDistance;
	paceCount = 0;
}

enemy::~enemy(void)
{
}

void enemy::draw(LPD3DXSPRITE sprite_handler, int Offset)
{
	RECT srcRect;
	int columns = lastframe + 1;
	D3DXVECTOR3 temp_position (position->x - Offset, position->y, position->z);

	if (direction == -1)
	{
		srcRect.left = info.Width - (((curframe % numTiles) + 1) * (info.Width / numTiles));
		srcRect.top = info.Height / 2;
		srcRect.right = srcRect.left + (info.Width / numTiles);
		srcRect.bottom = info.Height;

		sprite_handler->Draw (image,
							  &srcRect,
							  NULL,
							  &temp_position,
							  D3DCOLOR_XRGB (255,255,255));
	}else
	{
		srcRect.left = ((curframe % numTiles) * (info.Width / numTiles));
		srcRect.top = 0;
		srcRect.right = srcRect.left + (info.Width / numTiles);
		srcRect.bottom = info.Height / 2;

		sprite_handler->Draw (image,
							  &srcRect,
							  NULL,
							  &temp_position,
							  D3DCOLOR_XRGB (255,255,255));
	}
}

void enemy::move()
{
	position->y += movey;
	position->x += direction * movex;

	if (++animcount > animdelay)
	{
		//reset the counter
		animcount = 0;

		//check pacing conditions
		if (++paceCount > paceSize)
		{
			direction = direction * -1;
			paceCount = 0;
		}

		//animate the sprite
		if (++curframe > lastframe)
		{
			curframe = 0;
		}
	}
}

void enemy::turn()
{
	direction = direction * -1;
}
