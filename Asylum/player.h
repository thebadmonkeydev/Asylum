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
#ifndef _PLAYER_H
#define _PLAYER_H

/* System Includes */
#include "asincludes.h"

#include "pickup.h"

class player :
	public ASO
{
public:
	player(void);
	~player(void);

	void draw(LPD3DXSPRITE sprite_handler, int Offset);
	void move_left();
	void move_right();
	void move();
	void attack();
	void stopAttack();
	void jump();
	void stepBack();
	void stopFall();
	void stopWalk();
	void canJump();
	void stopJump();
	void resetLevel();

	bool hit();			//returns 1 if player is dead, 0 otherwise
	bool isAttacking();
	bool canAttack();
	bool isJumping();
	int getLives();
	int getScore();
	int getWidth();
	int getHeight();

	void pickUp(int type);

protected:
	//graphical information
	LPDIRECT3DTEXTURE9 image_running, image_standing, image_attacking;
	D3DXIMAGE_INFO running_info, standing_info, attacking_info, face_info;
	OnScreenText *out;
	std::stringstream ss;

	//Audio information
	CSound *sswing;
	CSound *sjump;
	CSound *spickup;

	int numAttackingTiles, numStandingTiles, numRunningTiles;

	//player information
	int lives, score;
	bool standing, attacking, jumping;
	int jumpStart, jumpHeight;
	bool cantJump, cantAttack;
	int attackCount, noAttackLength;

	//For displaying text above the player's head
	char *textToOut;
	bool textForOut;
	int textoutCount, textoutTime;

	//For allowing the player to be hit and invulnerable
	//for a short time
	bool isHit, off;
	int blinkCount, blinkTime, offCount, offLength;

	//For controlling the speed and magnitude
	//of the player's attack
	int atStart, atLength;

	//Bonus life for high scores
	int bonusTotal, lastBonus;
};

#endif
