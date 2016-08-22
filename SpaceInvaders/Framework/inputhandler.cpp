// COMP710 GP 2D Framework

// This include:
#include "inputhandler.h"

// Local includes:
#include "game.h"
#include "fmod.hpp"

// Library includes:
#include <cassert>

#include <string>
#include <sstream>
#include <iostream>

InputHandler::InputHandler()
: m_pGameController(0)
{

}

InputHandler::~InputHandler()
{
	if (m_pGameController)
	{
		SDL_JoystickClose(m_pGameController);
		m_pGameController = 0;
	}
}

bool 
InputHandler::Initialise()
{
	int numControllesr = SDL_NumJoysticks();
	m_pGameController = SDL_JoystickOpen(0);
	//assert(m_pGameController);

	return (true);
}

void 
InputHandler::ProcessInput(Game& game)
{
	
	// W02.1: Receive Input Events below...
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
	{

		if (e.type == SDL_QUIT)
		{
			game.Quit();
		}
		else if (e.type == SDL_KEYDOWN)
		{
			// W02.3: Tell the game to fire a player bullet...

			if (e.key.keysym.sym == SDLK_LEFT) {
				game.MoveSpaceShipLeft();
			}
			else if (e.key.keysym.sym == SDLK_RIGHT) {
				game.MoveSpaceShipRight();
			}
			else if (e.key.keysym.sym == SDLK_UP) {
				game.MoveSpaceShipUp();
			}
			else if (e.key.keysym.sym == SDLK_DOWN) {
				game.MoveSpaceShipDown();
			}
			else if (e.key.keysym.sym == SDLK_SPACE) {
				game.FireSpaceShipBullet();
			}
		}
		else if (e.type == SDL_KEYUP) {
			if (e.key.keysym.sym == SDLK_UP || e.key.keysym.sym == SDLK_DOWN
				|| e.key.keysym.sym == SDLK_RIGHT || e.key.keysym.sym == SDLK_LEFT) {
				game.ResetMovement();
			}
		}

	}
}
