// COMP710 GP 2D Framework

// This include:
#include "inputhandler.h"

// Local includes:
#include "game.h"
#include "fmod.hpp"
#include "InputControls.h"

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
	select = false;
	//assert(m_pGameController);
	jump = false;
	z = false;
	d = false;
	i = false;
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
				select = true;
			}
			if (e.key.keysym.sym == SDLK_p) {
				game.PauseGame();
			}
			if (e.key.keysym.sym == SDLK_x) {
				jump = true;
			}
			if (e.key.keysym.sym == SDLK_z) {
				z = true;
			}
			if (e.key.keysym.sym == SDLK_i) {
				i = true;
			}
			if (e.key.keysym.sym == SDLK_d) {
				d = true;
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
			if (e.key.keysym.sym == SDLK_x) {
				jump = false;
			}
			if (e.key.keysym.sym == SDLK_z) {
				z = false;
			}
			if (e.key.keysym.sym == SDLK_i) {
				i = false;
			}
			if (e.key.keysym.sym == SDLK_d) {
				d = false;
			}
		}

		
		if (moveUp)
		{
			game.InputRouter(InputControls::pMoveUp);
		}

		if (moveDown)
		{
			game.InputRouter(InputControls::pMoveDown);
		}

		if (moveLeft)
		{
			game.InputRouter(InputControls::pMoveLeft);
		}

		if (moveRight)
		{
			game.InputRouter(InputControls::pMoveRight);
		}

		if (jump)
		{
			if (moveUp)
			{
				game.InputRouter(InputControls::pJumpUp);
			}

			if (moveDown)
			{
				game.InputRouter(InputControls::pJumpDown);
			}

			if (moveLeft)
			{
				game.InputRouter(InputControls::pJumpLeft);
			}

			if (moveRight)
			{
				game.InputRouter(InputControls::pJumpRight);
			}
		}

		if (select)
		{
			game.InputRouter(InputControls::mSelect);
			select = false;
		}

		if (z)
		{
			game.InputRouter(InputControls::dMenu);
			z = false;
		}

		if (d)
		{
			// die
			game.InputRouter(InputControls::aDie);
		}

		if (i)
		{
			// invincibility
			game.InputRouter(InputControls::aInvincibility);
			i = false;
		}

	}
}
