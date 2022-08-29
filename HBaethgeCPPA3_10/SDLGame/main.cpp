#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "enemy.h";
#include "bullet.h";
#include "pickup.h";

using namespace std;


//-------- Global Scope Space --------
//boolean to maintain program loop
bool quit = false;

//deltaTime init() - for frame rate ind.
float deltaTime = 0.0;
int thisTime = 0;
int lastTime = 0;

//set player speed
float playerSpeed = 500.0f;

//movement in the x axis - left or right
float xDir;

//variables used to control integer creep
float pos_X, pos_Y;

//-----enemy information-----
//enemy list variable
vector<Enemy> enemyList;

//-----bullet information-----
vector<Bullet> bulletList;

//create rectangle for the player pos
SDL_Rect playerPos;

//declare sounds
Mix_Chunk* laser;
Mix_Chunk* explosion;
Mix_Music* bgm;

//-------- End Global Scope Space --------

void CreateBullet()
{
	for (int i = 0; i <bulletList.size(); i++)
	{
		if (bulletList[i].active == false)
		{
			//play laser sound
			Mix_PlayChannel(-1, laser, 0);
			bulletList[i].active = true;
			bulletList[i].posRect.x = (pos_X + (playerPos.w / 2));
			bulletList[i].posRect.x = (bulletList[i].posRect.x - (bulletList[i].posRect.w / 2));
			bulletList[i].posRect.y = playerPos.y;
			bulletList[i].pos_X = pos_X;
			bulletList[i].pos_Y = playerPos.y;
			break;
		}
	}
}

//variables for score and lives
//score, lives, and fonts
int playerScore, oldScore, playerLives, oldLives;

//declare font
TTF_Font* font;

//font color
SDL_Color colorP1 = {0, 255, 0, 255};

//create surfaces
SDL_Surface* scoreSurface, *livesSurface;

//create textures
SDL_Texture* scoreTexture, * livesTexture;
SDL_Rect scorePos, livesPos;
string tempScore, tempLives;

void UpdateScore(SDL_Renderer* renderer)
{
	//creating the text
	tempScore = "Player Score: " + std::to_string(playerScore);

	//create render text
	scoreSurface = TTF_RenderText_Solid(font, tempScore.c_str(), colorP1);

	//creating texture
	scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);

	SDL_QueryTexture(scoreTexture, NULL, NULL, &scorePos.w, &scorePos.h);

	SDL_FreeSurface(scoreSurface);

	oldScore = playerScore;
}

void UpdateLives(SDL_Renderer* renderer)
{
	//creating the text
	tempLives = "Player Lives: " + std::to_string(playerLives);

	//create render text
	livesSurface = TTF_RenderText_Solid(font, tempLives.c_str(), colorP1);

	//creating texture
	livesTexture = SDL_CreateTextureFromSurface(renderer, livesSurface);

	SDL_QueryTexture(livesTexture, NULL, NULL, &livesPos.w, &livesPos.h);

	SDL_FreeSurface(livesSurface);

	oldLives = playerLives;
}

//setup pickup
vector<Pickup> pickupList;

int main(int argc, char* argv[])
{
	SDL_Window* window;

	//create a renderer variable
	SDL_Renderer* renderer = NULL;

	SDL_Init(SDL_INIT_EVERYTHING);	//Initialize SDL

	//create an application window with the following settings:
	window = SDL_CreateWindow(
		"Space Game",				//window title
		SDL_WINDOWPOS_UNDEFINED,	//initial x position
		SDL_WINDOWPOS_UNDEFINED,	//initial y position
		1024,						//width, in pixels
		768,						//height, in pixels
		SDL_WINDOW_OPENGL			//flags - see below
	);

	//check to see if window was successfully created
	if (window == NULL)
	{
		//in case the window could not be made
		printf("Could not create window: %s", SDL_GetError());
		return 1;
	}

	//create renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	//background image -- CREATE ------------------------------------------
	//create an SDL surface
	SDL_Surface* surface = IMG_Load("./SDL_Assets/bkgd.png");

	//create a babkgd texture
	SDL_Texture* bkgd;

	//place the surface into the texture
	bkgd = SDL_CreateTextureFromSurface(renderer, surface);

	//free the surface
	SDL_FreeSurface(surface);

	//create rectangles for the background pos
	SDL_Rect bkgdPos;

	//set bkgdPos x, y ,width, and height
	bkgdPos.x = 0;
	bkgdPos.y = 0;
	bkgdPos.w = 1024;
	bkgdPos.h = 768;

	//background image -- CREATE END ------------------------------------------

	//player image -- CREATE ------------------------------------------
	//create an SDL surface
	surface = IMG_Load("./SDL_Assets/player.png");

	//create a babkgd texture
	SDL_Texture* player;

	//place the surface into the texture
	player = SDL_CreateTextureFromSurface(renderer, surface);

	//free the surface
	SDL_FreeSurface(surface);	

	//set bkgdPos x, y ,width, and height
	playerPos.x = 500;
	playerPos.y = 700;
	playerPos.w = 163;
	playerPos.h = 52;

	//player image -- CREATE END ------------------------------------------

	//SDL event to handle input
	SDL_Event event;

	//create bullets and place in list
	for (int i =0; i < 10; i++)
	{
		Bullet tempBullet(renderer, i + 5, i + 5);

		bulletList.push_back(tempBullet);
	}

	//clear enemy list
	enemyList.clear();

	//fill enemy list
	for (int i = 0; i < 6; i++)
	{
		Enemy tempEnemy(renderer);

		enemyList.push_back(tempEnemy);
	}

	//init audio plaback
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	//load laser sound
	laser = Mix_LoadWAV("./SDL_Assets/laser.wav");

	//load explosion sound
	explosion = Mix_LoadWAV("./SDL_Assets/explosion.wav");

	//load and loop background music
	bgm = Mix_LoadMUS("./SDL_Assets/space background.wav");

	//if the music is not playing, play it and loop
	if (!Mix_PlayingMusic())
	{
		Mix_PlayMusic(bgm, -1);
	}

	//init player score, lives and font
	oldScore = 0;
	playerScore = 0;
	oldLives = 0;
	playerLives = 3;

	TTF_Init();
	font = TTF_OpenFont("./SDL_Assets/space_quest/Space Quest.ttf", 20);

	//set up rectangles
	scorePos.x = scorePos.y = 10;
	livesPos.x = 10;
	livesPos.y = 40;

	UpdateScore(renderer);
	UpdateLives(renderer);

	//set up our enum to handle all the game states
	enum GameState {MENU, INSTRUCTIONS, GAME, WIN, LOSE, LEVEL2};

	//variable to track where we are in the game
	GameState gameState = MENU;

	//bool value to allow movement through the individual states
	bool menu, instructions, game, win, lose, level2;

	//clear pickuplist, create pickup, put pickup in list
	pickupList.clear();                   //clear
	Pickup tempPickup(renderer);		  //create
	pickupList.push_back(tempPickup);     //insert

	//basic program loop
	while (!quit)
	{
		switch (gameState)
		{
		case MENU:
			menu = true;
			std::cout << "The Game State is MENU." << endl;
			std::cout << "The I key is for Instructions." << endl;
			std::cout << "Press the S key to start the game." << endl;
			std::cout << "Press the Q key to Quit the game." << endl;
			std::cout << endl;

			//load instructions background
			//create and SDL surface
			surface = IMG_Load("./SDL_Assets/mainmenu.png");

			//place surface into the texture
			bkgd = SDL_CreateTextureFromSurface(renderer, surface);

			//free the surface
			SDL_FreeSurface(surface);

			//background image -- end create

			while (menu)
			{
				//create deltaTime
				thisTime = SDL_GetTicks();
				deltaTime = (float)(thisTime - lastTime) / 1000;
				lastTime = thisTime;

				//check for input
				if (SDL_PollEvent(&event))
				{
					//close window by the window's X button
					if (event.type == SDL_QUIT)
					{
						quit = true;
						menu = false;
						break;
					}

					//look for a keypress
					switch (event.type)
					{
					case SDL_KEYUP:
						//check the SDLKey values and move  change the coords
						switch (event.key.keysym.sym)
						{
						case SDLK_i:
							menu = false;
							gameState = INSTRUCTIONS;
							break;
						case SDLK_s:
							menu = false;
							gameState = GAME;
							break;
						case SDLK_q:
							quit = true;
							menu = false;							
							break;
						default:
								break;
						}
					}//end key up switch
				}//end poll event

				//----- Draw -----
				//Draw Section
				//clear the old buffer
				SDL_RenderClear(renderer);

				//prepare to draw bkgd
				SDL_RenderCopy(renderer, bkgd, NULL, &bkgdPos);

				//draw new info to screen
				SDL_RenderPresent(renderer);

				//----- End Draw -----

			}//ends while menu screen/loop

			break;

		case INSTRUCTIONS:
			instructions = true;
			std::cout << "The Game State is INSTRUCTIONS." << endl;
			std::cout << "Press the S key to start the game." << endl;
			std::cout << "Press the M key to go to the Main Menu." << endl;
			std::cout << "Press the Q key to Quit the game." << endl;
			std::cout << endl;

			//load instructions background
			//create and SDL surface
			surface = IMG_Load("./SDL_Assets/instructions2.png");

			//place surface into the texture
			bkgd = SDL_CreateTextureFromSurface(renderer, surface);

			//free the surface
			SDL_FreeSurface(surface);

			//background image -- end create

			while (instructions)
			{
				//create deltaTime
				thisTime = SDL_GetTicks();
				deltaTime = (float)(thisTime - lastTime) / 1000;
				lastTime = thisTime;

				//check for input
				if (SDL_PollEvent(&event))
				{
					//close window by the window's X button
					if (event.type == SDL_QUIT)
					{
						quit = true;
						instructions = false;
						break;
					}

					//look for a keypress
					switch (event.type)
					{
					case SDL_KEYUP:
						//check the SDLKey values and move  change the coords
						switch (event.key.keysym.sym)
						{
						case SDLK_m:
							instructions = false;
							gameState = MENU;
							break;
						case SDLK_s:
							instructions = false;
							gameState = GAME;
							break;
						case SDLK_q:
							quit = true;
							instructions = false;
							break;
						default:
							break;
						}
					}//end key up switch
				}//end poll event

				//----- Draw -----
				//Draw Section
				//clear the old buffer
				SDL_RenderClear(renderer);

				//prepare to draw bkgd
				SDL_RenderCopy(renderer, bkgd, NULL, &bkgdPos);

				//draw new info to screen
				SDL_RenderPresent(renderer);

				//----- End Draw -----

			}//ends while menu screen/loop
			break;

		case GAME:
		{
			game = true;
			std::cout << "The Game State is GAME" << endl;

			//load game background
			//create and SDL surface
			surface = IMG_Load("./SDL_Assets/bkgd.png");

			//place surface into the texture
			bkgd = SDL_CreateTextureFromSurface(renderer, surface);

			//free the surface
			SDL_FreeSurface(surface);

			//start the game fresh
			enemyList.clear();

			//fill enemy list
			for (int i = 0; i < 6; i++)
			{
				Enemy tempEnemy(renderer);

				enemyList.push_back(tempEnemy);
			}

			//clear pickuplist, create pickup, put pickup in list
			pickupList.clear();                   //clear
			Pickup tempPickup(renderer);		  //create
			pickupList.push_back(tempPickup);     //insert

			//reset player's score and lives
			playerScore = 0;
			playerLives = 3;

			while (game)
			{
				//create deltaTime
				thisTime = SDL_GetTicks();
				deltaTime = (float)(thisTime - lastTime) / 1000;
				lastTime = thisTime;

				//check for input
				if (SDL_PollEvent(&event))
				{
					//close window by by the window's x button
					if (event.type == SDL_QUIT)
					{
						quit = true;
						game = false;
						break;
					}

					switch (event.type)
					{
						//look for a keypress
					case SDL_KEYUP:
						//check the space bar
						switch (event.key.keysym.sym)
						{
						case SDLK_SPACE:
							CreateBullet();
							pickupList[0].Reset();
							break;
						default:
							break;
						}
					}//end switch
				}//end poll event

				//player movement
				//get the keyboard state
				const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

				//check which arrows are pressed
				if (currentKeyStates[SDL_SCANCODE_LEFT])
				{
					xDir = -1;
				}
				else if (currentKeyStates[SDL_SCANCODE_RIGHT])
				{
					xDir = 1;
				}
				else
				{
					xDir = 0;
				}

				//----------------------------UPDATE----------------------------		
				//get new position to move player using direection and deltatime
				pos_X += (playerSpeed * xDir) * deltaTime;

				//move player
				playerPos.x = (int)(pos_X + 0.5f);

				//keep player on screen
				//moving left
				if (playerPos.x < 0)
				{
					playerPos.x = 0;
					pos_X = 0;
				}

				//keep player on screen
				//moving right
				if (playerPos.x > 1024 - playerPos.w)
				{
					playerPos.x = 1024 - playerPos.w;
					pos_X = 1024 - playerPos.w;
				}

				//update bullets
				for (int i = 0; i < bulletList.size(); i++)
				{
					if (bulletList[i].active == true)
					{
						bulletList[i].Update(deltaTime);
					}
				}

				//update pickup
				pickupList[0].Update(deltaTime);

				//update enemy list
				for (int i = 0; i < 6; i++)
				{
					enemyList[i].Update(deltaTime);
				}

				//check for collision of bullets with enemies
				//for loop to scroll through all bullets
				for (int i = 0; i < bulletList.size(); i++)
				{
					//check all the enimies against active bullet
					if (bulletList[i].active == true)
					{
						for (int j = 0; j < enemyList.size(); j++)
						{
							//see if there is a collision between this bullet and this enemy using SDL
							if (SDL_HasIntersection(&bulletList[i].posRect, &enemyList[j].posRect))
							{
								//play explosion sound
								Mix_PlayChannel(-1, explosion, 0);

								//reset the enemy
								enemyList[j].Reset();

								//reset the bullet
								bulletList[i].Reset();

								//give player points
								playerScore += 50;

								//check to see if the player can go to level2
								if (playerScore >= 500)
								{
									game = false;
									gameState = LEVEL2;
								}
							}
						}
					}
				}

				//check for collision with the player and all enemies
				//check all enemies against active bullet
				for (int i = 0; i < enemyList.size(); i++)
				{
					//see if there is a collision between the player and this enemy using SDL
					if (SDL_HasIntersection(&playerPos, &enemyList[i].posRect))
					{
						//play explosion sound
						Mix_PlayChannel(-1, explosion, 0);

						//reset the enemy
						enemyList[i].Reset();

						//take a life away
						playerLives -= 1;

						//check to see if player loses game
						if (playerLives <= 0)
						{
							game = false;
							gameState = LOSE;
						}
					}
				}

				//check for collision with player and pickups
				for (int i = 0; i < pickupList.size(); i++)
				{
					//see if there is a collision between the player and pickup using SDL
					if (SDL_HasIntersection(&playerPos, &pickupList[i].posRect))
					{
						//check to see if this is the lose a life pickup
						//if so, deactivate the pickup and remove a player's life
						//checking for game over
						if (pickupList[i].pickupType == "life")
						{
							//deactivate the pickup
							pickupList[i].DeActivate();

							//play explosion sound
							Mix_PlayChannel(-1, explosion, 0);

							//take away a life
							playerLives -= 1;

							//check to see if player loses
							if (playerLives <= 0)
							{
								game = false;
								gameState = LOSE;
							}
						}
						else if (pickupList[i].pickupType == "bomb")
						{
							//check to see if this is the destroy all enemies pickup
							//if so cycle through enemies and reset them and give player points for each

							//deactivate the pickup
							pickupList[i].DeActivate();

							//play laser sound
							Mix_PlayChannel(-1, laser, 0);

							//cycle through all enemies
							for (int i = 0; i < enemyList.size(); i++)
							{
								//reset the enemy
								enemyList[i].Reset();

								//give player points
								playerScore += 10;
							}

							//check to see if player can go on to level2
							if (playerScore > 500)
							{
								game = false;
								gameState = LEVEL2;
							}
						}
					}
				}

				//update score and lives on screen text
				if (playerScore != oldScore)
				{
					UpdateScore(renderer);
				}

				if (playerLives != oldLives)
				{
					UpdateLives(renderer);
				}

				//----------------------------END UPDATE----------------------------

				//----------------------------DRAW----------------------------		
				//clear the old buffer
				SDL_RenderClear(renderer);

				//prepare to draw bkgd
				SDL_RenderCopy(renderer, bkgd, NULL, &bkgdPos);

				//draw bullets
				for (int i = 0; i < bulletList.size(); i++)
				{
					if (bulletList[i].active == true)
					{
						bulletList[i].Draw(renderer);
					}
				}

				//prepare to draw player
				SDL_RenderCopy(renderer, player, NULL, &playerPos);

				//draw enemy list
				for (int i = 0; i < 6; i++)
				{
					enemyList[i].Draw(renderer);
				}

				//draw pickup
				pickupList[0].Draw(renderer);

				//draw score texture
				SDL_RenderCopy(renderer, scoreTexture, NULL, &scorePos);

				//draw lives texture
				SDL_RenderCopy(renderer, livesTexture, NULL, &livesPos);

				//draw new info to screen
				SDL_RenderPresent(renderer);

				//---------------------------END DRAW-----------------------------

			}//end game loop

			break;
		}
					case LEVEL2:
						level2 = true;
						std::cout << "The Game State is LEVEL 2" << endl;

						//start the game fresh
						enemyList.clear();
						
						//fill enemy list
						for (int i = 0; i < 6; i++)
						{
							Enemy tempEnemy(renderer);

							enemyList.push_back(tempEnemy);
						}

						while (level2)
						{
							//create deltaTime
							thisTime = SDL_GetTicks();
							deltaTime = (float)(thisTime - lastTime) / 1000;
							lastTime = thisTime;

							//check for input
							if (SDL_PollEvent(&event))
							{
								//close window by by the window's x button
								if (event.type == SDL_QUIT)
								{
									quit = true;
									level2 = false;
									break;
								}

								switch (event.type)
								{
									//look for a keypress
								case SDL_KEYUP:
									//check the space bar
									switch (event.key.keysym.sym)
									{
									case SDLK_SPACE:
										CreateBullet();
										break;
									default:
										break;
									}
								}//end switch
							}//end poll event

							//player movement
							//get the keyboard state
							const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

							//check which arrows are pressed
							if (currentKeyStates[SDL_SCANCODE_LEFT])
							{
								xDir = -1;
							}
							else if (currentKeyStates[SDL_SCANCODE_RIGHT])
							{
								xDir = 1;
							}
							else
							{
								xDir = 0;
							}

							//----------------------------UPDATE----------------------------		
							//get new position to move player using direection and deltatime
							pos_X += (playerSpeed * xDir) * deltaTime;

							//move player
							playerPos.x = (int)(pos_X + 0.5f);

							//keep player on screen
							//moving left
							if (playerPos.x < 0)
							{
								playerPos.x = 0;
								pos_X = 0;
							}

							//keep player on screen
							//moving right
							if (playerPos.x > 1024 - playerPos.w)
							{
								playerPos.x = 1024 - playerPos.w;
								pos_X = 1024 - playerPos.w;
							}

							//update bullets
							for (int i = 0; i < bulletList.size(); i++)
							{
								if (bulletList[i].active == true)
								{
									bulletList[i].Update(deltaTime);
								}
							}

							//update enemy list
							for (int i = 0; i < 6; i++)
							{
								enemyList[i].Update(deltaTime);
							}

							//check for collision of bullets with enemies
							//for loop to scroll through all bullets
							for (int i = 0; i < bulletList.size(); i++)
							{
								//check all the enimies against active bullet
								if (bulletList[i].active == true)
								{
									for (int j = 0; j < enemyList.size(); j++)
									{
										//see if there is a collision between this bullet and this enemy using SDL
										if (SDL_HasIntersection(&bulletList[i].posRect, &enemyList[j].posRect))
										{
											//play explosion sound
											Mix_PlayChannel(-1, explosion, 0);

											//reset the enemy
											enemyList[j].Reset();

											//reset the bullet
											bulletList[i].Reset();

											//give player points
											playerScore += 50;

											//check to see if the player wins
											if (playerScore >= 1000)
											{
												level2 = false;
												gameState = WIN;
											}
										}
									}
								}
							}

							//check for collision with the player and all enemies
							//check all enemies against active bullet
							for (int i = 0; i < enemyList.size(); i++)
							{
								//see if there is a collision between the player and this enemy using SDL
								if (SDL_HasIntersection(&playerPos, &enemyList[i].posRect))
								{
									//play explosion sound
									Mix_PlayChannel(-1, explosion, 0);

									//reset the enemy
									enemyList[i].Reset();

									//take a life away
									playerLives -= 1;

									//check to see if player loses game
									if (playerLives <= 0)
									{
										level2 = false;
										gameState = LOSE;
									}
								}
							}

							//update score and lives on screen text
							if (playerScore != oldScore)
							{
								UpdateScore(renderer);
							}

							if (playerLives != oldLives)
							{
								UpdateLives(renderer);
							}

							//----------------------------END UPDATE----------------------------

							//----------------------------DRAW----------------------------		
							//clear the old buffer
							SDL_RenderClear(renderer);

							//prepare to draw bkgd
							SDL_RenderCopy(renderer, bkgd, NULL, &bkgdPos);

							//draw bullets
							for (int i = 0; i < bulletList.size(); i++)
							{
								if (bulletList[i].active == true)
								{
									bulletList[i].Draw(renderer);
								}
							}

							//prepare to draw player
							SDL_RenderCopy(renderer, player, NULL, &playerPos);

							//draw enemy list
							for (int i = 0; i < 6; i++)
							{
								enemyList[i].Draw(renderer);
							}

							//draw score texture
							SDL_RenderCopy(renderer, scoreTexture, NULL, &scorePos);

							//draw lives texture
							SDL_RenderCopy(renderer, livesTexture, NULL, &livesPos);

							//draw new info to screen
							SDL_RenderPresent(renderer);

							//---------------------------END DRAW-----------------------------

						}//end game loop

						break;

		case WIN:
			win = true;
			std::cout << "The Game State is WIN." << endl;
			std::cout << "Press the S key to start the game." << endl;
			std::cout << "Press the M key to go to the Main Menu." << endl;
			std::cout << "Press the Q key to Quit the game." << endl;
			std::cout << endl;

			//load win background
			//create and SDL surface
			surface = IMG_Load("./SDL_Assets/win.png");

			//place surface into the texture
			bkgd = SDL_CreateTextureFromSurface(renderer, surface);

			//free the surface
			SDL_FreeSurface(surface);

			while (win)
			{
				//create deltaTime
				thisTime = SDL_GetTicks();
				deltaTime = (float)(thisTime - lastTime) / 1000;
				lastTime = thisTime;

				//check for input
				if (SDL_PollEvent(&event))
				{
					//close window by the window's X button
					if (event.type == SDL_QUIT)
					{
						quit = true;
						win = false;
						break;
					}

					//look for a keypress
					switch (event.type)
					{
					case SDL_KEYUP:
						//check the SDLKey values and move  change the coords
						switch (event.key.keysym.sym)
						{
						case SDLK_m:
							win = false;
							gameState = MENU;
							break;
						case SDLK_s:
							win = false;
							gameState = GAME;
							break;
						case SDLK_q:
							win = false;
							quit = true;							
							break;
						default:
							break;
						}
					}//end key up switch
				}//end poll event

				//----- DRAW -----
				//clear the old buffer
				SDL_RenderClear(renderer);

				//prepare to draw background
				SDL_RenderCopy(renderer, bkgd, NULL, &bkgdPos);

				//draw new info to the screen
				SDL_RenderPresent(renderer);

				// ----- END DRAW -----
			}//end win screen
			break;

		case LOSE:
			lose = true;
			std::cout << "The Game State is LOSE." << endl;
			std::cout << "Press the S key to start the game." << endl;
			std::cout << "Press the M key to go to the Main Menu." << endl;
			std::cout << "Press the Q key to Quit the game." << endl;
			std::cout << endl;

			//load win background
			//create and SDL surface
			surface = IMG_Load("./SDL_Assets/lose.png");

			//place surface into the texture
			bkgd = SDL_CreateTextureFromSurface(renderer, surface);

			//free the surface
			SDL_FreeSurface(surface);

			while (lose)
			{
				//create deltaTime
				thisTime = SDL_GetTicks();
				deltaTime = (float)(thisTime - lastTime) / 1000;
				lastTime = thisTime;

				//check for input
				if (SDL_PollEvent(&event))
				{
					//close window by the window's X button
					if (event.type == SDL_QUIT)
					{
						quit = true;
						lose = false;
						break;
					}

					//look for a keypress
					switch (event.type)
					{
					case SDL_KEYUP:
						//check the SDLKey values and move  change the coords
						switch (event.key.keysym.sym)
						{
						case SDLK_m:
							lose = false;
							gameState = MENU;
							break;
						case SDLK_s:
							lose = false;
							gameState = GAME;
							break;
						case SDLK_q:
							lose = false;
							quit = true;
							break;
						default:
							break;
						}
					}//end key up switch
				}//end poll event

				//----- DRAW -----
				//clear the old buffer
				SDL_RenderClear(renderer);

				//prepare to draw background
				SDL_RenderCopy(renderer, bkgd, NULL, &bkgdPos);

				//draw new info to the screen
				SDL_RenderPresent(renderer);

				// ----- END DRAW -----
			}//end lose screen
			break;

		}//end switch for gamestate
	}//ends game loop

	//close and destroy the window
	SDL_DestroyWindow(window);

	//clean up
	SDL_Quit();

	return 0;
}//end of program loop                                                                                                                                                                                   