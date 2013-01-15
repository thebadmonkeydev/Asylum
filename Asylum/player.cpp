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

#include "player.h"

player::player(void)
{
	//Load the bitmap for the player avatar
	char filename_run[15] = "player_run.bmp";
	char filename_stand[17] = "player_stand.bmp";
	char filename_attack[18] = "player_attack.bmp";
	char filename_face[9] = "face.bmp";

	//Load Textures
	image_running = LoadTexture (filename_run, D3DCOLOR_XRGB (255,0,255));
	image_standing = LoadTexture (filename_stand, D3DCOLOR_XRGB (255,0,255));
	image_attacking = LoadTexture (filename_attack, D3DCOLOR_XRGB (255,0,255));
	image = LoadTexture (filename_face, D3DCOLOR_XRGB (255,0,255));

	//get image information from files
	HRESULT result = D3DXGetImageInfoFromFile (filename_run, &running_info);
	if (result != D3D_OK)
	{
		//Error Code
	}
	result = D3DXGetImageInfoFromFile (filename_stand, &standing_info);
	if (result != D3D_OK)
	{
		//Error Code
	}
	result = D3DXGetImageInfoFromFile (filename_attack, &attacking_info);
	if (result != D3D_OK)
	{
		//Error Code
	}
	result = D3DXGetImageInfoFromFile (filename_face, &face_info);
	if (result != D3D_OK)
	{
		//Error Code
	}

	sswing = LoadSound ("playerSwing.wav");
	//CSound *sjump;
	spickup = LoadSound ("playerPickup.wav");

	//Setup height and width information
	numStandingTiles = 1;
	numAttackingTiles = 1;
	numRunningTiles = 4;
	width = face_info.Width;
	height = face_info.Height;

	//Setup the player movement properties
	position = new D3DXVECTOR3((float)0, (float)(SCREEN_HEIGHT - (SCREEN_HEIGHT / 4)), 0);
	movex = 10;		//because the player will be centered on screen always
	movey = 10;
	lastMoveX = 0;
	lastMoveY = 0;

	jumpHeight = 130;
	jumpStart = 0;

	//Setup the animation
	animdelay = 5;
	animcount = 0;
	curframe = 0;
	lastframe = numRunningTiles - 1;
	direction = 1;		//-1 for left, 1 for right
	cantJump = true;
	attacking = false;
	jumping = false;
	standing = true;

	atStart = (int)position->x;
	atLength = 100;

	out = new OnScreenText ();
	textoutCount = 0;
	textoutTime = 45;
	textForOut = false;
	/* Allocate room for the string. */
	textToOut = (char *)malloc(sizeof(char) * 256);

	score = 0;
	lives = 3;

	isHit = false;
	off = false;

	blinkCount = 0;
	blinkTime = 100;
	offCount = 0;
	offLength = 1;

	bonusTotal = 50;
	lastBonus = 0;

	attackCount = 0;
	noAttackLength = 15;
	cantAttack = false;
}

player::~player(void)
{
	//free output buffers
	if (out != NULL)
		delete out;
}

void player::draw(LPD3DXSPRITE sprite_handler, int Offset)
{
	RECT srcRect;
	int columns = lastframe + 1;
	D3DXVECTOR3 temp_position (position->x - Offset, position->y, position->z);

	if (!off)
	{
		if (direction == -1)
		{
			if (attacking)
			{
				srcRect.left = 0;
				srcRect.top = attacking_info.Height / 2;
				srcRect.right = attacking_info.Width;
				srcRect.bottom = attacking_info.Height;

				sprite_handler->Draw (image_attacking,
									  &srcRect,
									  NULL,
									  &temp_position,
									  D3DCOLOR_XRGB (255,255,255));
			}else if (standing)
			{
				srcRect.left = 0;
				srcRect.top = standing_info.Height / 2;
				srcRect.right = standing_info.Width;
				srcRect.bottom = standing_info.Height;

				sprite_handler->Draw (image_standing,
									  &srcRect,
									  NULL,
									  &temp_position,
									  D3DCOLOR_XRGB (255,255,255));
			}else
			{
				srcRect.left = running_info.Width - (((curframe % numRunningTiles) + 1) * (running_info.Width / numRunningTiles));
				srcRect.top = running_info.Height / 2;
				srcRect.right = srcRect.left + (running_info.Width / numRunningTiles);
				srcRect.bottom = running_info.Height;

				sprite_handler->Draw (image_running,
									  &srcRect,
									  NULL,
									  &temp_position,
									  D3DCOLOR_XRGB (255,255,255));
			}
		}else
		{
			if (attacking)
			{
				srcRect.left = 0;
				srcRect.top = 0;
				srcRect.right = attacking_info.Width;
				srcRect.bottom = attacking_info.Height / 2;

				sprite_handler->Draw (image_attacking,
									  &srcRect,
									  NULL,
									  &temp_position,
									  D3DCOLOR_XRGB (255,255,255));
			}else if (standing)
			{
				srcRect.left = 0;
				srcRect.top = 0;
				srcRect.right = standing_info.Width;
				srcRect.bottom = standing_info.Height / 2;

				sprite_handler->Draw (image_standing,
									  &srcRect,
									  NULL,
									  &temp_position,
									  D3DCOLOR_XRGB (255,255,255));
			}else
			{
				srcRect.left = ((curframe % numRunningTiles) * (running_info.Width / numRunningTiles));
				srcRect.top = 0;
				srcRect.right = srcRect.left + (running_info.Width / numRunningTiles);
				srcRect.bottom = running_info.Height / 2;

				sprite_handler->Draw (image_running,
									  &srcRect,
									  NULL,
									  &temp_position,
									  D3DCOLOR_XRGB (255,255,255));
			}
		}
	}else
	{
	}

	srcRect.left = 0;
	srcRect.top = 0;
	srcRect.right = width;
	srcRect.bottom = height;
	
	sprite_handler->Draw (image,
						  &srcRect,
						  NULL,
						  new D3DXVECTOR3 ((float)10, (float)10, 0),
						  D3DCOLOR_XRGB (255,255,255));

	ss.str ("");
	ss << "Score: " << score;
	out->drawText (sprite_handler, ss.str().c_str(), 10, 65);

	ss.str ("");
	if (lives > 0)
		ss << "X " << lives;
	else
		ss << "X " << 0;

	out->drawText (sprite_handler, ss.str().c_str(), 65, 25);
	

	if (textForOut)
	{
		if (++textoutCount < textoutTime)
			out->drawText (sprite_handler, textToOut, (int)position->x - Offset, (int)position->y - 10);

		if (textoutCount > textoutTime)
		{
			textoutCount = 0;
			textForOut = false;
		}
	}
}

void player::move_left()
{
	//move the sprite
	direction = -1;
	lastframe = numRunningTiles - 1;

	position->x -= movex;

	lastMoveX = -1 * movex;
	lastMoveY = movey;

	standing = false;
	//attacking = false;
	
	if (++animcount > animdelay)
	{
		//reset the counter
		animcount = 0;

		//animate the sprite
		if (++curframe > lastframe)
			curframe = 0;
	}
}

void player::move_right()
{
	//move the sprite
	direction = 1;
	lastframe = numRunningTiles - 1;
	position->x += movex;

	lastMoveX = movex;
	lastMoveY = movey;

	standing = false;
	//attacking = false;
	
	
	if (++animcount > animdelay)
	{
		//reset the counter
		animcount = 0;

		//animate the sprite
		if (++curframe > lastframe)
			curframe = 0;
	}
}

void player::move()
{
	standing = true;
	
	if (attacking)
		if (direction == -1)
			position->x -= movex;
		else
			position->x += movex;

	position->y += movey;

	lastMoveX = 0;
	lastMoveY = movey;

	if (++animcount > animdelay)
	{
		//reset the counter
		animcount = 0;

		//animate the sprite
		if (++curframe > lastframe)
			curframe = 0;
	}

	if (jumping)
		if (position->y <= jumpStart - jumpHeight)
		{
			stopJump();
			jumpStart = 0;
		}		

	if (attacking)
	{
		if (direction == -1)
		{
			if (position->x < atStart - atLength)
			{
				attacking = false;
			}
		}else
		{
			if (position->x > atStart + atLength)
			{
				attacking = false;
			}
		}
	}

	if (isHit)
	{
		if (++blinkCount > blinkTime)
		{
			isHit = false;
			off = false;
			blinkCount = 0;
			offCount = 0;
		}

		if (++offCount > offLength)
		{
			off = !off;
			offCount = 0;
		}
	}

	if (cantAttack)
	{
		if (++attackCount > noAttackLength)
		{
			attackCount = 0;
			cantAttack = false;
		}
	}
}

bool player::isAttacking()
{
	return attacking;
}

void player::attack()
{
	if (cantAttack)
		return;

	if (!attacking)
	{
		attacking = true;
		standing = false;

		atStart = (int)position->x;

		lastframe = numAttackingTiles - 1;
		position->y += movey;

		lastMoveX = 0;
		lastMoveY = movey;

		if (++animcount > animdelay)
		{
			//reset the counter
			animcount = 0;

			//animate the sprite
			if (++curframe > lastframe)
				curframe = 0;
		}

		cantAttack = true;
		PlaySound (sswing);
	}
}

void player::jump()
{
	if (!cantJump && !jumping)
	{
		//attacking = false;
		standing = false;
		jumping = true;
		cantJump = true;

		if (jumpStart == 0)
			jumpStart = (int)position->y;

		lastframe = numAttackingTiles - 1;

		movey = -10;

		position->y += movey;
	}

	if (++animcount > animdelay)
	{
		//reset the counter
		animcount = 0;

		//animate the sprite
		if (++curframe > lastframe)
			curframe = 0;
	}
}

void player::pickUp(int type)
{
	switch (type)
	{
	case AS_ENEMY:
		/* Copy the contents of the string. */
		strcpy_s(textToOut, (sizeof(char) * 2), "7");
		textForOut = true;

		score += AS_ENEMY;
		break;

	case AS_GEM1:
		/* Copy the contents of the string. */
		strcpy_s(textToOut, (sizeof(char) * 2), "1");
		textForOut = true;

		score += AS_GEM1;
		PlaySound (spickup);
		break;
		
	case AS_GEM5:
		/* Copy the contents of the string. */
		strcpy_s(textToOut, (sizeof(char) * 2), "5");
		textForOut = true;

		score += AS_GEM5;
		PlaySound (spickup);
		break;

	case AS_GEM10:
		/* Copy the contents of the string. */
		strcpy_s(textToOut, (sizeof(char) * 3), "10");
		textForOut = true;

		score += AS_GEM10;
		PlaySound (spickup);
		break;

	case AS_LIFE:
		/* Copy the contents of the string. */
		strcpy_s(textToOut, (sizeof(char) * 6), "1-UP!");
		textForOut = true;

		lives++;
		PlaySound (spickup);
		break;
	}

	if (score >= lastBonus + bonusTotal)
	{
		lives++;
		lastBonus = score;
		bonusTotal += bonusTotal;
	}
}

int player::getLives()
{
	return lives;
}

int player::getScore()
{
	return score;
}

void player::stepBack()
{
	position->x -= lastMoveX;
	position->y -= lastMoveY;
}

void player::stopFall()
{
	position->y -= lastMoveY;
}

void player::stopWalk()
{
	position->x -= lastMoveX;
}

int player::getHeight()
{
	return running_info.Height / 2;
}

int player::getWidth()
{
	return running_info.Width / numRunningTiles;
}

bool player::isJumping()
{
	return jumping;
}

void player::canJump()
{
	cantJump = false;
}

void player::stopJump()
{
	jumping = false;
	movey = 10;
}

void player::resetLevel()
{
	delete position;

	position = new D3DXVECTOR3((float)0, (float)(SCREEN_HEIGHT - (SCREEN_HEIGHT / 4)), 0);
}

bool player::hit()
{
	if (!isHit)
	{
		lives--;
		isHit = true;
	}

	if (lives < 0)
		return 1;
	else
 		return 0;
}

void player::stopAttack()
{
	attacking = false;
}

bool player::canAttack()
{
	return !cantAttack;
}
