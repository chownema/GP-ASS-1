// COMP710 GP 2D Framework

// This includes:
#include "game.h"

// Local includes:
#include "backbuffer.h"
#include "inputhandler.h"
#include "logmanager.h"
#include "sprite.h"
#include "Player.h"
#include "Enemy.h"
#include "texture.h"
#include "math.h"
#include "AnimEntity.h"
#include "AnimatedSprite.h"
#include "SoundSystem.h"
#include "Parser.h"
#include "InputControls.h"

// Library includes:
#include <cassert>
#include <SDL.h>
#include <vector>
#include <Windows.h>
#include "fmod.hpp"

// Static Members:
Game* Game::sm_pInstance = 0;
TextureManager* texture = 0;
const int width = 800;
const int height = 600;
int bulletSpeed = 5;
int comparisonTime = 0;

int hitCount = 0;

Game&
Game::GetInstance()
{
	if (sm_pInstance == 0)
	{ 
		sm_pInstance = new Game();
	}

	assert(sm_pInstance);

	return (*sm_pInstance);
}

void 
Game::DestroyInstance()
{
	delete sm_pInstance; 
	sm_pInstance = 0;
}

Game::Game()
: m_pBackBuffer(0)
, m_pInputHandler(0)
, m_looping(true)
, m_executionTime(0)
, m_elapsedSeconds(0)
, m_frameCount(0)
, m_FPS(0)
, m_numUpdates(0)
, m_lastTime(0)
, m_lag(0)
{
	
}

Game::~Game()
{
	delete m_pBackBuffer;
	m_pBackBuffer = 0;
}

bool 
Game::Initialise()
{
	// Load in data
	Parser::GetInstance().loadInFile("data.ini");
	
	m_pBackBuffer = new BackBuffer();
	if (!m_pBackBuffer->Initialise(width, height))
	{
		LogManager::GetInstance().Log("BackBuffer Init Fail!");
		return (false);
	}

	m_pInputHandler = new InputHandler();
	if (!m_pInputHandler->Initialise())
	{
		LogManager::GetInstance().Log("InputHandler Init Fail!");
		return (false);
	}

	// Set enemy variables
	int MAX_SPEED = Parser::GetInstance().enemyDoc["max_speed"].GetInt();
	int MIN_SPEED = Parser::GetInstance().enemyDoc["min_speed"].GetInt();
	string SPRITE_LOC = Parser::GetInstance().enemyDoc["sprite_loc"].GetString();
	Sprite* pPlayerSprite = m_pBackBuffer->CreateSprite("assets\\playership.png");
	assert(pPlayerSprite);
	// W02.1: Create the player ship instance.
	pPlayer = new Player();
	pPlayer->Initialise(pPlayerSprite);
	pPlayer->setX(width / 2);
	pPlayer->setY(height / 2);
	
	m_lastTime = SDL_GetTicks();
	m_lag = 0.0f;

	//// Create a sample sound
	//SoundClass soundSample;
	//sound.createSound(&soundSample, "sounds\\drumloop.wav");

	//// Play the sound, with loop mode
	//sound.playSound(soundSample, true);

	//// Do something meanwhile...

	//// Release the sound
	////sound.releaseSound(soundSample);



	return (true);
}

bool 
Game::DoGameLoop()
{

	const float stepSize = 1.0f / 60.0f;

	assert(m_pInputHandler);
	m_pInputHandler->ProcessInput(*this);
	
	if (m_looping)
	{
		int current = SDL_GetTicks();
		float deltaTime = (current - m_lastTime) / 1000.0f;
		m_lastTime = current;

		m_executionTime += deltaTime;

		m_lag += deltaTime;
		// GameState dictactes process and drawn

		// Playing State
		if (m_gameState == 0) {
			while (m_lag >= stepSize)
			{
				Process(stepSize);
				m_lag -= stepSize;
				++m_numUpdates;
			}
			Draw(*m_pBackBuffer);
		}
		// Paused State
		else if (m_gameState == 1) {
			while (m_lag >= stepSize)
			{
				ProcessPauseState(stepSize);
				m_lag -= stepSize;
				++m_numUpdates;
			}
			Draw(*m_pBackBuffer);
			
		}
		// Quit State
		else if (m_gameState == 2) {

		}
		// Menu State
		else if (m_gameState == 3) {

		}
	}

	SDL_Delay(1);
	return (m_looping);
}

void 
Game::Process(float deltaTime)
{
	
	// Count total simulation time elapsed:
	m_elapsedSeconds += deltaTime;
	
	comparisonTime++;
	if (0==comparisonTime % 10) {
		int x = (0 + (rand() % (int)(3 - 0 + 1)));
		SpawnEnemy(x);
	}

	// Frame Counter:
	if (m_elapsedSeconds > 1)
	{
		m_elapsedSeconds -= 1;
		m_FPS = m_frameCount;
		m_frameCount = 0;
	}

	// Update the game world simulation:

	// Process Enemies with Player
	for (itEnemy = pEnemyVector.begin(); itEnemy < pEnemyVector.end();)
	{
		Enemy* ene = *itEnemy;
		ene->Process(deltaTime);
		int x = ene->GetPositionX();
		int y = ene->GetPositionY();
		// If collision end game and kill player
		if (pPlayer->IsCollidingWith(**itEnemy)) {
			// Damage player and set dead if no hp left
		}
		// if out of bounds remove enemy
		else if (x > width + 20 || x < -20 || y > height + 20
			|| y < -20) {
				delete *itEnemy;
				itEnemy = pEnemyVector.erase(itEnemy);
				SpawnExplosion(x, y);
				hitCount++;
		}
		else
			itEnemy++;
	}
	
	// Update player
	pPlayer->Process(deltaTime);

	for (int i = 0; i < pExplosionVector.size(); i++)
	{
		pExplosionVector[i]->Process(deltaTime);
	}

	// If player is dead set game state to OVER

	
}

void
Game::resumeInit() {
	for (itEnemy = pEnemyVector.begin(); itEnemy < pEnemyVector.end();)
	{
		Enemy* ene = *itEnemy;
		ene->resumeEnemy();
		itEnemy++;
	}
}

void
Game::ProcessPauseState(float deltaTime)
{

	// Count total simulation time elapsed:
	m_elapsedSeconds += deltaTime;

	// Frame Counter:
	if (m_elapsedSeconds > 1)
	{
		m_elapsedSeconds -= 1;
		m_FPS = m_frameCount;
		m_frameCount = 0;
	}

	// Process Enemies with Player
	for (itEnemy = pEnemyVector.begin(); itEnemy < pEnemyVector.end();)
	{
		Enemy* ene = *itEnemy;
		ene->pauseEnemy();
		itEnemy++;
	}

	// Update player
	pPlayer->Process(deltaTime);

	for (int i = 0; i < pExplosionVector.size(); i++)
	{
		pExplosionVector[i]->Process(deltaTime);
	}
}


void 
Game::Draw(BackBuffer& backBuffer)
{
	++m_frameCount;

	backBuffer.Clear();
	
	// W02.2: Draw all enemy aliens in container...
		for (int i = 0; i < pEnemyVector.size(); i++) {
			pEnemyVector[i]->Draw(backBuffer);
		}

		for (int i = 0; i < pExplosionVector.size(); i++) {
			pExplosionVector[i]->Draw(backBuffer);
		}

		// W02.1: Draw the player ship...
		pPlayer->Draw(backBuffer);


		// Draw text according to gamestate
		SDL_Color colour = { 0, 0, 0, 255 };
		m_pBackBuffer->DrawTextOnScreen(colour, "AmaticSC-Regular.ttf", "Game Over", 24, 100, 100);
	

	backBuffer.Present();
}

void 
Game::Quit()
{
	m_looping = false;
}

/* Input Methods */

void
Game::InputRouter(InputControls input) {
	// Evaluate string input
	switch (input){
	case InputControls::pMoveUp:
		MovePlayerUp();
		break;
	case InputControls::pMoveDown:
		MovePlayerDown();
		break;
	case InputControls::pMoveLeft:
		MovePlayerLeft();
		break;
	case InputControls::pMoveRight:
		MovePlayerRight();
		break;
	}
}

/* Player movements */

void 
Game::MovePlayerLeft()
{
	// W02.1: Tell the player ship to move left.
	pPlayer->SetHorizontalVelocity(-5);
}

// W02.1: Add the method to tell the player ship to move right...
void
Game::MovePlayerRight()
{
	// W02.1: Tell the player ship to move Right.
	pPlayer->SetHorizontalVelocity(5);
}

void
Game::MovePlayerUp()
{
	// W02.1: Tell the player ship to move Right.
	pPlayer->SetVerticalVelocity(-5);
}

void
Game::MovePlayerDown()
{
	// W02.1: Tell the player ship to move Right.
	pPlayer->SetVerticalVelocity(5);
}

/* Reset movement methods */

void
Game::StopMovePlayerHorizontal()
{
	// W02.1: Tell the player ship to move left.
	pPlayer->SetHorizontalVelocity(0);
}

void
Game::StopMovePlayerVertical()
{
	// W02.1: Tell the player ship to move Right.
	pPlayer->SetVerticalVelocity(0);
}

void
Game::ResetMovement()
{
	pPlayer->SetHorizontalVelocity(0);
	pPlayer->SetVerticalVelocity(0);
}


// W02.3: Space a Bullet in game.
void 
Game::PauseGame()
{
	if (m_gameState == playing)
		m_gameState = paused;
	else {
		m_gameState = playing;
		resumeInit();
	}	
}

// W02.2: Spawn a Enemy in game.
void 
Game::SpawnEnemy(int direction)
{	
	int x = 0;
	int y = 0;
	// Set enemy variables
	int MAX_SPEED = Parser::GetInstance().enemyDoc["max_speed"].GetInt();
	int MIN_SPEED = Parser::GetInstance().enemyDoc["min_speed"].GetInt();
	string SPRITE_LOC = Parser::GetInstance().enemyDoc["sprite_loc"].GetString();
	// W02.2: Load the alien enemy sprite file.
	Sprite* enemySprite = m_pBackBuffer->CreateSprite(SPRITE_LOC.c_str());

	// W02.2: Create a new Enemy object.
	Enemy* e = new Enemy();
	e->Initialise(enemySprite);
	int speed = MIN_SPEED + (rand() % (int)(MAX_SPEED - MIN_SPEED + 1));
	if (direction == 0){ // up
		y = 0;
		x = 0 + (rand() % (int)(width - 0 + 1));
		e->setX(x);
		e->setY(y);
		e->SetVerticalVelocity(speed);
	}
	else if (direction == 1){ // down
		y = height;
		x = 0 + (rand() % (int)(width - 0 + 1));
		e->setX(x);
		e->setY(y);
		e->SetVerticalVelocity(-speed);
	}
	else if (direction == 2){ // left
		x = 0;
		y = 0 + (rand() % (int)(height - 0 + 1));
		e->setX(x);
		e->setY(y);
		e->SetHorizontalVelocity(speed);
	}
	else if (direction == 3){ // right
		x = width;
		y = 0 + (rand() % (int)(height - 0 + 1));
		e->setX(x);
		e->setY(y);
		e->SetHorizontalVelocity(-speed);
	}

	// W02.2: Add the new Enemy to the enemy container.
	pEnemyVector.push_back(e);
}

// W02.2: Spawn a Explosion in game.
void
Game::SpawnExplosion(int x, int y)
{
	// W02.2: Load the alien enemy sprite file.
	AnimatedSprite* explosionSprite = m_pBackBuffer->CreateAnimatedSprite("AnimationAssets\\explosion.png");

	// W02.2: Create a new Enemy object.
	AnimEntity* e = new AnimEntity();
	e->Initialise(explosionSprite);
	explosionSprite->SetFrameSpeed(0.4f);
	explosionSprite->SetFrameWidth(64);
	explosionSprite->SetFrameHeight(64);
	explosionSprite->SetNumOfFrames(4);

	e->setX(x);
	e->setY(y);
	int speed = 1 + (rand() % (int)(10 - 1 + 1));
	e->SetVerticalVelocity(speed);

	// W02.2: Add the new Enemy to the enemy container.
	pExplosionVector.push_back(e);
}

float RandomFloat(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}