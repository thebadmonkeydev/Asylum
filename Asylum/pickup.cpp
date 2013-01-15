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

#include "pickup.h"

pickup::pickup(int x, int y, int newType)
{
	type = newType;

	HRESULT result;
	switch (type)
	{
	case AS_GEM5:
		image = LoadTexture ("purple_gem.bmp", D3DCOLOR_XRGB (255,0,255));

		result = D3DXGetImageInfoFromFile ("purple_gem.bmp", &info);
		if (result != D3D_OK)
		{
			//Error Code
		}
		break;

	case AS_GEM10:
		image = LoadTexture ("red_gem.bmp", D3DCOLOR_XRGB (255,0,255));

		result = D3DXGetImageInfoFromFile ("red_gem.bmp", &info);
		if (result != D3D_OK)
		{
			//Error Code
		}
		break;

	case AS_LIFE:
		image = LoadTexture ("heart.bmp", D3DCOLOR_XRGB (255,0,255));

		result = D3DXGetImageInfoFromFile ("heart.bmp", &info);
		if (result != D3D_OK)
		{
			//Error Code
		}
		break;

	case AS_GEM1:
	default:
		image = LoadTexture ("blue_gem.bmp", D3DCOLOR_XRGB (255,0,255));

		result = D3DXGetImageInfoFromFile ("blue_gem.bmp", &info);
		if (result != D3D_OK)
		{
			//Error Code
		}
		break;
	}

	width = info.Width;
	height = info.Height;
	position = new D3DXVECTOR3 ((float)x, (float)y, 0);
}

pickup::~pickup(void)
{
}

int pickup::getType(void)
{
	return type;
}

void pickup::draw(LPD3DXSPRITE sprite_handler, int Offset)
{
	RECT rect;
	D3DXVECTOR3 temp_position (position->x - Offset, position->y, position->z);

	rect.left = 0;
	rect.top = 0;
	rect.right = rect.left + width;
	rect.bottom = rect.top + height;

	sprite_handler->Draw (image,
						  &rect,
						  NULL,
						  &temp_position,
						  D3DCOLOR_XRGB (255,255,255));
}
