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

#include "dxaudio.h"

CSoundManager *dsound;

int Init_DirectSound( HWND hwnd )
{
	HRESULT result;

	//create DIrectSound manager object
	dsound = new CSoundManager();

	//initialize DirectSound
    result = dsound->Initialize(hwnd, DSSCL_PRIORITY);
    if (result != DS_OK)
        return 0;

	//initialize DirectSound
	result = dsound->SetPrimaryBufferFormat(2,22050,16);
	if (result != DS_OK)
		return 0;

	//return success
	return 1;
}

CSound *LoadSound (char *filename)
{
	HRESULT result;

	//create local reference to wave data
	CSound *wave;

	//attempt to load the wave file
	result = dsound->Create(&wave, filename);
	if (result != DS_OK)
		return NULL;

	//return the wave
	return wave;
}

void PlaySound (CSound *sound)
{
	sound->Play();
}

void LoopSound (CSound *sound)
{
	sound->Play (0, DSBPLAY_LOOPING);
}

void StopSound (CSound *sound)
{
	sound->Stop ();
}
