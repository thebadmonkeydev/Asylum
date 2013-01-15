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
#ifndef _PATIENT_H
#define _PATIENT_H

/* System Includes */
#include "asincludes.h"

#include "ASO.h"

class patient :
	public ASO
{
public:
	patient(void);
	~patient(void);

	void draw(LPD3DXSPRITE);
	void Dialogue(void);
};

#endif