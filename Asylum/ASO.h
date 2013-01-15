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
#ifndef _ASO_H
#define _ASO_H

/* System Includes */
#include "asincludes.h"

class ASO
{
public:
	ASO();
	ASO(char *, int, int);
	~ASO(void);
	virtual void draw (LPD3DXSPRITE sprite_handler, int Offset);
	virtual void stopFall ();
	virtual void setPosition (int,int);

	virtual int getWidth();
	virtual int getHeight();
	virtual int getX();
	virtual int getY();

protected:
	LPDIRECT3DTEXTURE9 image;
	D3DXVECTOR3 *position;
	//Position and physical properties of the caveman sprite
	D3DXIMAGE_INFO info;
	int width, height;
	int movex, movey;
	int lastMoveX, lastMoveY;

	//Animation variables
	int animdelay, animcount;
	int curframe, lastframe;
	int direction;
};

#endif
