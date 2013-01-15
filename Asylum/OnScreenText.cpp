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

#include "OnScreenText.h"

OnScreenText::OnScreenText()
{
	//Load the bitmap
	text_image = LoadTexture ("text.bmp", D3DCOLOR_XRGB (255,0,255));
	HRESULT result = D3DXGetImageInfoFromFile ("text.bmp", &text_info);
	if (result != D3D_OK)
	{
		//Error Code
	}

	//Setup drawing properties
	coloumns = 16;
	rows = 16;

	charWidth = text_info.Width / coloumns;
	charHeight = text_info.Height / rows;
	charSpacing = -6;
}

OnScreenText::~OnScreenText()
{
	text_image->Release();
}

void OnScreenText::drawText(LPD3DXSPRITE sprite_handler, const char *text, int x, int y)
{
	RECT srcRect;
	D3DXVECTOR3 *position = new D3DXVECTOR3 ((float) x, (float) y, 0);

	//Loop through C-String
	int i = 0;

	while (text[i] != '\0')
	{
		srcRect.left = (((int)text[i]) % 16) * charWidth;
		srcRect.top = (((int)text[i]) / 16) * charHeight;
		srcRect.bottom = srcRect.top + charHeight;
		srcRect.right = srcRect.left + charWidth;

		sprite_handler->Draw (text_image, &srcRect, NULL, position, D3DCOLOR_XRGB (0, 0, 0));
		position->x = position->x + charWidth + charSpacing;
		i++;
	}

	delete position;
}
