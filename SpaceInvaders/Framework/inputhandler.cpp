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
	moveDown = false;
	moveUp = false;
	moveLeft = false;
	moveRight = false;
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
			// Need to fix movement
			if (e.key.keysym.sym == SDLK_LEFT) {
				moveLeft = true;
			}
			if (e.key.keysym.sym == SDLK_RIGHT) {
				moveRight = true;
			}
			if (e.key.keysym.sym == SDLK_UP) {
				moveUp = true;
			}
			if (e.key.keysym.sym == SDLK_DOWN) {
				moveDown = true;
			}
			if (e.key.keysym.sym == SDLK_SPACE) {
				// no shooting only peaceful cat

			}
		}
		else if (e.type == SDL_KEYUP) {
			if (e.key.keysym.sym == SDLK_LEFT) {
				moveLeft = false;
				game.StopMovePlayerHorizontal();
			}
			if (e.key.keysym.sym == SDLK_RIGHT) {
				moveRight = false;
				game.StopMovePlayerHorizontal();
			}
			if (e.key.keysym.sym == SDLK_UP) {
				moveUp = false;
				game.StopMovePlayerVertical();
			}
			if (e.key.keysym.sym == SDLK_DOWN) {
				moveDown = false;
				game.StopMovePlayerVertical();
			}
		}


		if (moveUp)
		{
			game.MovePlayerUp();
		}

		if (moveDown)
		{
			game.MovePlayerDown();
		}

		if (moveLeft)
		{
			game.MovePlayerLeft();
		}

		if (moveRight)
		{
			game.MovePlayerRight();
		}


	}
}
