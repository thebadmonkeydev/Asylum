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
#ifndef _PICKUP_H
#define _PICKUP_H

/* System Includes */
#include "asincludes.h"

#include "ASO.h"

#define AS_GEM1 1
#define AS_GEM5 5
#define AS_GEM10 10
#define AS_LIFE 100
#define AS_ENEMY 7

class pickup :
	public ASO
{
public:
	pickup(int, int, int);
	~pickup(void);

	int getType();
	void draw(LPD3DXSPRITE, int Offset);

protected:
	int type;
};

#endif
