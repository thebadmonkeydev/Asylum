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

/* Header file association */
#include "game.h"


//background image
LPDIRECT3DTEXTURE9 back;
LPDIRECT3DTEXTURE9 startScreen;
LPDIRECT3DTEXTURE9 gameoverScreen;
LPDIRECT3DTEXTURE9 winScreen;
LPD3DXSPRITE sprite_handler;

int ScreenOffset;
int scrollBuffer;


//Timing Variable
long start = GetTickCount();

//Sound objects
CSound *playerKilled;
CSound *enemyKilled;
CSound *theme;

//Character objects
player *avatar;
std::vector<enemy*> *enemies;

//Environment Objects
std::vector<ASO*> *blocks;
std::vector<pickup*> *pickups;
door *elevator;


//Level indicator
int level = 1;

//Game function controls
bool isGameOver = false;
bool isGameWon = false;
bool isGameStart = true;

/* Initialize the Game */
int Game_Init (HWND hwnd)
{
	if (!Init_Mouse (hwnd))
	{
		MessageBox (hwnd, "Error Initializing the mouse.", "Error", MB_OK);
		return 0;
	}

	if (!Init_Keyboard (hwnd))
	{
		MessageBox (hwnd, "Error Initializing the keyboard.", "Error", MB_OK);
		return 0;
	}
	playerKilled = LoadSound ("playerKilled.wav");
	enemyKilled = LoadSound ("enemyKilled.wav");

	startScreen = LoadTexture ("gamestart.bmp", D3DCOLOR_XRGB (255,0,255));
	gameoverScreen = LoadTexture ("gameover.bmp", D3DCOLOR_XRGB (255,0,255));
	winScreen = LoadTexture ("gamewin.bmp", D3DCOLOR_XRGB (255,0,255));

	if (startScreen == NULL ||
		gameoverScreen == NULL ||
		winScreen == NULL)
		return 0;

	ScreenOffset = 0;
	scrollBuffer = (int)((3 * SCREEN_WIDTH) / 8);

	//avatar = new player();
	enemies = new std::vector<enemy*> ();
	blocks = new std::vector<ASO*> ();
	pickups = new std::vector<pickup*> ();

	//Initialize First Level
	if (!Load_Level (level))
		return 0;

	return 1;
}

/* Initializes a new Level */
bool Load_Level (int newLevel)
{
	level = newLevel;

	enemies->clear();
	blocks->clear();
	pickups->clear();

	char *blockbit;
	char *enemybit;
	char *backbit;
	
	char *themewav;

	D3DXVECTOR3 *elevPos;

	switch (level)
	{
	case 1:
		if (avatar != NULL)
			avatar = 0;

		ScreenOffset = 0;

		avatar = new player ();

		blockbit = "block1.bmp";
		enemybit = "monster1.bmp";
		backbit = "bkgLevel1.bmp";
		themewav = "theme1.wav";

		//setup terrain and enemies
		for (int i = 0; i < LEVEL_WIDTH / TILE_WIDTH; i++)
		{
			for (int j = 0; j < LEVEL_HEIGHT / TILE_WIDTH; j++)
			{
				if (level1_map[j][i] == 1)
					blocks->push_back (new ASO (blockbit, i * TILE_WIDTH, j * TILE_WIDTH));

				if (level1_map[j][i] > 6)
				{
					switch (level1_map[j][i])
					{
					case 8:
						pickups->push_back (new pickup (i * TILE_WIDTH, j * TILE_WIDTH, AS_GEM5));
						break;
					case 9:
						pickups->push_back (new pickup (i * TILE_WIDTH, j * TILE_WIDTH, AS_GEM10));
						break;
					case 10:
						pickups->push_back (new pickup (i * TILE_WIDTH, j * TILE_WIDTH, AS_LIFE));
						break;
					case 7:
					default:
						pickups->push_back (new pickup (i * TILE_WIDTH, j * TILE_WIDTH, AS_GEM1));
						break;
					}

				}else if (level1_map[j][i] > 1)
					enemies->push_back (new enemy (enemybit, i * TILE_WIDTH, j * TILE_WIDTH, level1_map[j][i]));
			}
		}

		elevPos = new D3DXVECTOR3 ((int)LEVEL_WIDTH - 400, (int)LEVEL_HEIGHT - 250, 0);
		break;

	case 2:
		blockbit = "block1.bmp";
		enemybit = "monster2.bmp";
		backbit = "bkgLevel2.bmp";
		themewav = "theme2.wav";

		//setup terrain and enemies
		for (int i = 0; i < LEVEL_WIDTH / TILE_WIDTH; i++)
		{
			for (int j = 0; j < LEVEL_HEIGHT / TILE_WIDTH; j++)
			{
				if (level2_map[j][i] == 1)
					blocks->push_back (new ASO (blockbit, i * TILE_WIDTH, j * TILE_WIDTH));

				if (level2_map[j][i] > 6)
				{
					switch (level2_map[j][i])
					{
					case 8:
						pickups->push_back (new pickup (i * TILE_WIDTH, j * TILE_WIDTH, AS_GEM5));
						break;
					case 9:
						pickups->push_back (new pickup (i * TILE_WIDTH, j * TILE_WIDTH, AS_GEM10));
						break;
					case 10:
						pickups->push_back (new pickup (i * TILE_WIDTH, j * TILE_WIDTH, AS_LIFE));
						break;
					case 7:
					default:
						pickups->push_back (new pickup (i * TILE_WIDTH, j * TILE_WIDTH, AS_GEM1));
						break;
					}

				}else if (level2_map[j][i] > 1)
					enemies->push_back (new enemy (enemybit, i * TILE_WIDTH, j * TILE_WIDTH, level2_map[j][i]));
			}
		}

		elevPos = new D3DXVECTOR3 ((int)400, (int)LEVEL_HEIGHT - 250, 0);
		break;

	case 3:
		blockbit = "block1.bmp";
		enemybit = "monster3.bmp";
		backbit = "bkgLevel3.bmp";
		themewav = "theme3.wav";

		//setup terrain and enemies
		for (int i = 0; i < LEVEL_WIDTH / TILE_WIDTH; i++)
		{
			for (int j = 0; j < LEVEL_HEIGHT / TILE_WIDTH; j++)
			{
				if (level3_map[j][i] == 1)
					blocks->push_back (new ASO (blockbit, i * TILE_WIDTH, j * TILE_WIDTH));

				if (level3_map[j][i] > 6)
				{
					switch (level3_map[j][i])
					{
					case 8:
						pickups->push_back (new pickup (i * TILE_WIDTH, j * TILE_WIDTH, AS_GEM5));
						break;
					case 9:
						pickups->push_back (new pickup (i * TILE_WIDTH, j * TILE_WIDTH, AS_GEM10));
						break;
					case 10:
						pickups->push_back (new pickup (i * TILE_WIDTH, j * TILE_WIDTH, AS_LIFE));
						break;
					case 7:
					default:
						pickups->push_back (new pickup (i * TILE_WIDTH, j * TILE_WIDTH, AS_GEM1));
						break;
					}

				}else if (level3_map[j][i] > 1)
					enemies->push_back (new enemy (enemybit, i * TILE_WIDTH, j * TILE_WIDTH, level3_map[j][i]));
			}
		}

		elevPos = new D3DXVECTOR3 ((int)LEVEL_WIDTH - 400, (int)LEVEL_HEIGHT - 250, 0);
		break;

	default:
		return 0;
		break;
	}

	if (elevator != NULL)
		elevator = 0;;

	elevator = new door ("elevator.bmp", (int)elevPos->x, (int)elevPos->y);

	HRESULT result = D3DXCreateSprite (d3ddev, &sprite_handler);

	back = LoadTexture (backbit, D3DCOLOR_XRGB (255,0,255));
	if (result != D3D_OK)
		return 0;

	if (back == NULL)
		return 0;

	if (theme != NULL)
		theme->Stop();

	theme = LoadSound (themewav);
	
	
	
	LoopSound (theme);

	delete elevPos;

	return 1;
}

/* THe main game loop */
void Game_Run (HWND hwnd)
{
	if (d3ddev == NULL)
		return;

	if (GetTickCount() - start >= 30)
	{
		Poll_Keyboard();
		start = GetTickCount();

		//check for exit keystroke (esc)
		if (Key_Down(DIK_ESCAPE) || Key_Down(DIK_F4))
				PostMessage(hwnd, WM_QUIT,0,0);

		if (!isGameOver && !isGameWon && !isGameStart)
		{
			/*
				Process Environment
			*/
			elevator->move();

			/*
				Process Player Input
			*/
			avatar->move();

			//Only run left when "only" the left arrow is depressed
			if (Key_Down (DIK_LEFT) && !Key_Down (DIK_RIGHT))
			{
				avatar->move_left();

				//CHeck the bounds of the level
				if (avatar->getX() < 0)
					avatar->setPosition (0, avatar->getY());
			}

			//Only run right when "only" the right arrow is depressed
			if (Key_Down (DIK_RIGHT) && !Key_Down (DIK_LEFT))
			{
				avatar->move_right();

				//Check the bounds of the level
				if (avatar->getX() + avatar->getWidth() > LEVEL_WIDTH)
					avatar->setPosition (LEVEL_WIDTH - avatar->getWidth(), avatar->getY());
			}

			//Attacking input
			if (Key_Down (DIK_SPACE))
			{
				if (avatar->canAttack())
				{
					avatar->stopFall();
					avatar->attack();
				}else
					if (avatar->isAttacking())
						avatar->stopFall();
			}

			//Jumping Input
			if (Key_Down (DIK_UP))
			{
					avatar->jump();
			}

			if (avatar->getX() > ScreenOffset + SCREEN_WIDTH - scrollBuffer)
				ScreenOffset += 10;
			if (ScreenOffset + SCREEN_WIDTH > LEVEL_WIDTH)
				ScreenOffset = LEVEL_WIDTH - SCREEN_WIDTH;

			if (avatar->getX() < scrollBuffer + ScreenOffset)
				ScreenOffset -= 10;
			if (ScreenOffset < 0)
				ScreenOffset = 0;

			if (avatar->getX() < ScreenOffset)
				avatar->setPosition (ScreenOffset, avatar->getY());
			if (avatar->getX() + avatar->getWidth() > ScreenOffset + SCREEN_WIDTH)
				avatar->setPosition (ScreenOffset + SCREEN_WIDTH - avatar->getWidth(), avatar->getY());

			/*
				Process Enemies
			*/
			//Use pacing ranges and oscillate from one side to another
				//For all enemies
					//move enemy
			for (unsigned int i = 0; i < enemies->size(); i++)
				if (enemies->at(i)->getX() < ScreenOffset + SCREEN_WIDTH + enemies->at(i)->getWidth() &&
					enemies->at(i)->getX() > ScreenOffset - enemies->at(i)->getWidth())
						enemies->at(i)->move();
				//end all enemies

			/*
				Process COllisions
			*/
			if (avatar->isAttacking() && Collision (avatar, elevator))
			{
				elevator->open();
			}

			int result;
			std::vector<enemy*>::iterator iter;
			std::vector<pickup*>::iterator pickupIter;

			for (unsigned int i = 0; i < blocks->size(); i++)
			{
				if (blocks->at(i)->getX() < ScreenOffset + SCREEN_WIDTH + blocks->at(i)->getWidth() &&
					blocks->at(i)->getX() > ScreenOffset - blocks->at(i)->getWidth())
				{
					result = Collision (avatar, blocks->at(i));
					switch (result)
					{
					case RIGHT:
						avatar->setPosition (blocks->at(i)->getX() + blocks->at(i)->getWidth(), avatar->getY());
						avatar->stopAttack();
						break;

					case LEFT:
						avatar->setPosition (blocks->at(i)->getX() - avatar->getWidth(), avatar->getY());
						avatar->stopAttack();
						break;

					case BOTTOM:
						avatar->stopJump();
						avatar->setPosition (avatar->getX(), blocks->at(i)->getY() + blocks->at(i)->getHeight());
						break;

					case TOP:
						avatar->canJump();
						avatar->setPosition (avatar->getX(), blocks->at(i)->getY() - avatar->getHeight());
						break;

					default:
						break;

					}
				}

				for (unsigned int j = 0; j < enemies->size(); j++)
				{
					if (enemies->at(j)->getX() < ScreenOffset + SCREEN_WIDTH + enemies->at(j)->getWidth() + 10 &&
						enemies->at(j)->getX() > ScreenOffset - enemies->at(j)->getWidth() - 10)
					{
						result = Collision (enemies->at(j), blocks->at(i));
						switch (result)
						{
						case RIGHT:
							enemies->at(j)->setPosition (blocks->at(i)->getX() + blocks->at(i)->getWidth(), enemies->at(j)->getY());
							break;

						case LEFT:
							enemies->at(j)->setPosition (blocks->at(i)->getX() - enemies->at(j)->getWidth(), enemies->at(j)->getY());
							break;

						case BOTTOM:
							enemies->at(j)->setPosition (enemies->at(j)->getX(), blocks->at(i)->getY() + blocks->at(i)->getHeight());
							break;

						case TOP:
							enemies->at(j)->setPosition (enemies->at(j)->getX(), blocks->at(i)->getY() - enemies->at(j)->getHeight());
							break;

						default:
							break;
						}
					

						if (Collision (avatar, enemies->at(j)))
						{
							iter = enemies->begin();

							if (avatar->isAttacking())
							{
								avatar->pickUp (5);
								enemies->erase (iter + j);
								if (enemyKilled != 0)
									PlaySound (enemyKilled);
							}else
								avatar->hit();
						}
					}
				}
			}

			pickupIter = pickups->begin();
			for (unsigned int i = 0; i < pickups->size(); i++)
			{
				if (pickups->at(i)->getX() < ScreenOffset + SCREEN_WIDTH + pickups->at(i)->getWidth() &&
					pickups->at(i)->getX() > ScreenOffset - pickups->at(i)->getWidth())
						if (Collision (avatar, pickups->at(i)))
						{
							avatar->pickUp (pickups->at(i)->getType());
							pickups->erase (pickupIter + i);
						}
			}
			//Pickup Collisions
				//for all pickups
					//if player collides with pickup
						//player picks item up
						//remove item
					//end if
				//end all pickups
			//Enemy Collisions


			/*
				Game Condition Check
			*/
			//Game is won
			if (elevator->isUsed())
			{
				if (++level <= NUM_LEVELS)
					Load_Level (level);
				else
				{
					StopSound (theme);
					isGameWon = true;
				}
			}

			//Game is lost
			if (avatar->getY() > SCREEN_HEIGHT + avatar->getWidth() || avatar->getLives() < 0)
			{
				isGameOver = true;
				StopSound (theme);
				PlaySound (playerKilled);
			}
		}

		/* Draw the game to the screen */
		if (d3ddev->BeginScene())
		{
			//Clear the backbuffer with background image
			d3ddev->Clear(0, 0, D3DCLEAR_TARGET,D3DCOLOR_XRGB(0,0,0), 1.0F,0);

			sprite_handler->Begin (D3DXSPRITE_ALPHABLEND);
			D3DXVECTOR3 pos ((float)0 - ScreenOffset,0,0);
			RECT rect;

			rect.left = 0;
			rect.top = 0;
			rect.right = rect.left + LEVEL_WIDTH;
			rect.bottom = rect.top + LEVEL_HEIGHT;

			sprite_handler->Draw(back,
								 &rect,
								 NULL,
								 &pos,
								 D3DCOLOR_XRGB (255,255,255));


			//Draw environment first
			for (unsigned int i = 0; i < blocks->size(); i++)
				if (blocks->at(i)->getX() < ScreenOffset + SCREEN_WIDTH + blocks->at(i)->getWidth() &&
					blocks->at(i)->getX() > ScreenOffset - blocks->at(i)->getWidth())
						blocks->at(i)->draw (sprite_handler, ScreenOffset);

			//Draw the pickups next
			for (unsigned int i = 0; i < pickups->size(); i++)
				if (pickups->at(i)->getX() < ScreenOffset + SCREEN_WIDTH + pickups->at(i)->getWidth() &&
					pickups->at(i)->getX() > ScreenOffset - pickups->at(i)->getWidth())
						pickups->at(i)->draw (sprite_handler, ScreenOffset);

			elevator->draw (sprite_handler, ScreenOffset);
			
			//draw enemies
			for (unsigned int i = 0; i < enemies->size(); i++)
			{
				if (enemies->at(i)->getX() < ScreenOffset + SCREEN_WIDTH + enemies->at(i)->getWidth() + 10 &&
					enemies->at(i)->getX() > ScreenOffset - enemies->at(i)->getWidth() - 10)
						enemies->at(i)->draw (sprite_handler, ScreenOffset);
			}

			//draw the player
			if (!(elevator->isClosing() || elevator->isUsed()))
				avatar->draw (sprite_handler, ScreenOffset);

			sprite_handler->End();

			//Stop rendering
			d3ddev->EndScene ();
		}

		//Flip to backbuffer
		d3ddev->Present (NULL,NULL,NULL,NULL);
	}else
	{
		if (isGameWon)
		{
			if (d3ddev->BeginScene())
			{
				//Clear the backbuffer with background image
				d3ddev->Clear(0, 0, D3DCLEAR_TARGET,D3DCOLOR_XRGB(0,0,0), 1.0F,0);

				sprite_handler->Begin (D3DXSPRITE_ALPHABLEND);
				D3DXVECTOR3 pos (0,0,0);
				RECT rect;

				rect.left = 0;
				rect.top = 0;
				rect.right = rect.left + SCREEN_WIDTH;
				rect.bottom = rect.top + SCREEN_HEIGHT;
				
				sprite_handler->Draw(winScreen,
									 &rect,
									 NULL,
									 &pos,
									 D3DCOLOR_XRGB (255,255,255));

				sprite_handler->End();

				//Stop rendering
				d3ddev->EndScene ();

				if (Key_Down (DIK_F2))
				{
					level = 1;
					Load_Level (level);
					isGameStart = true;
					isGameOver = false;
					isGameWon = false;
				}
			}

			//Flip to backbuffer
			d3ddev->Present (NULL,NULL,NULL,NULL);
		}else
		{
			if (isGameOver)
			{
				if (d3ddev->BeginScene())
				{
					//Clear the backbuffer with background image
					d3ddev->Clear(0, 0, D3DCLEAR_TARGET,D3DCOLOR_XRGB(0,0,0), 1.0F,0);

					sprite_handler->Begin (D3DXSPRITE_ALPHABLEND);
					D3DXVECTOR3 pos (0,0,0);
					RECT rect;

					rect.left = 0;
					rect.top = 0;
					rect.right = rect.left + SCREEN_WIDTH;
					rect.bottom = rect.top + SCREEN_HEIGHT;
					
					sprite_handler->Draw(gameoverScreen,
										 &rect,
										 NULL,
										 &pos,
										 D3DCOLOR_XRGB (255,255,255));

					sprite_handler->End();

					//Stop rendering
					d3ddev->EndScene ();

					if (Key_Down (DIK_F2))
					{
						level = 1;
						Load_Level (level);
						isGameStart = true;
						isGameOver = false;
						isGameWon = false;
					}
				}

				//Flip to backbuffer
				d3ddev->Present (NULL,NULL,NULL,NULL);
			}else
			{
				if (isGameStart)
				{
					if (d3ddev->BeginScene())
					{
						//Clear the backbuffer with background image
						d3ddev->Clear(0, 0, D3DCLEAR_TARGET,D3DCOLOR_XRGB(0,0,0), 1.0F,0);

						sprite_handler->Begin (D3DXSPRITE_ALPHABLEND);
						D3DXVECTOR3 pos (0,0,0);
						RECT rect;

						rect.left = 0;
						rect.top = 0;
						rect.right = rect.left + SCREEN_WIDTH;
						rect.bottom = rect.top + SCREEN_HEIGHT;
	
						sprite_handler->Draw(startScreen,
											 &rect,
											 NULL,
											 &pos,
											 D3DCOLOR_XRGB (255,255,255));

						sprite_handler->End();

						//Stop rendering
						d3ddev->EndScene ();

						if (Key_Down (DIK_SPACE))
							isGameStart = false;
					}

					//Flip to backbuffer
					d3ddev->Present (NULL,NULL,NULL,NULL);
				}else
				{
					return;
				}
			}
		}
	}
}

/* Frees resources */
void Game_End(HWND hwnd)
{
	if (avatar != NULL)
		avatar->~player();

	if (blocks != NULL)
	{
		for (unsigned int i = 0; i < blocks->size(); i++)
			delete blocks->at (i);
		delete blocks;
	}

	if (enemies != NULL)
	{
		for (unsigned int i = 0; i < enemies->size(); i++)
			delete enemies->at(i);
		delete enemies;
	}

	sprite_handler->Release();
	back->Release();
	startScreen->Release();
	winScreen->Release();
	gameoverScreen->Release();
}

int Collision(ASO* obj1, ASO* obj2)
{
	RECT rect1, rect2;
	int collisionBuf = 3;

	rect1.left = obj1->getX() + collisionBuf;
	rect1.top = obj1->getY();
	rect1.right = rect1.left + obj1->getWidth() - collisionBuf;
	rect1.bottom = rect1.top + obj1->getHeight() - collisionBuf;

	rect2.left = obj2->getX() + collisionBuf;
	rect2.top = obj2->getY();
	rect2.right = rect2.left + obj2->getWidth() - collisionBuf;
	rect2.bottom = rect2.top + obj2->getHeight() - collisionBuf;

	RECT dest;
	if (IntersectRect (&dest, &rect1, &rect2))
	{
		//if intersecting rectangle is horizontally short
		if (dest.right - dest.left < dest.bottom - dest.top)
		{
			if (dest.left < obj2->getX() + (obj2->getWidth() / 2))
				return LEFT;
			else
				return RIGHT;
		}else
		{
			if (dest.top < obj2->getY() + (obj2->getHeight() / 2))
				return TOP;
			else
				return BOTTOM;
		}
	}else
		return 0;
}

void Game_Over (HWND hwnd)
{
	MessageBox (hwnd, "You Lost!", "Game Over!", MB_OK);
}
