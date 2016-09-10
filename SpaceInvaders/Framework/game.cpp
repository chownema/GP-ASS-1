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
#include "Coin.h"
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
#include <stdio.h>
#include <sstream>
#include "fmod.hpp"

// Static Members:
Game* Game::sm_pInstance = 0;
TextureManager* texture = 0;
const int width = 800;
const int height = 600;
int playerSpeed = 5;
int comparisonTime = 0;

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

	// Load player data
	const Value& playerJson = Parser::GetInstance().document["player"];
	int HEALTH = playerJson["health"].GetInt();
	playerSpeed = playerJson["speed"].GetInt();
	// Set player data on player object
	AnimatedSprite* playerSprite = m_pBackBuffer->CreateAnimatedSprite(playerJson["sprite_loc"].GetString());
	pAnimPlayer = new Player();
	pAnimPlayer->Initialise(playerSprite);
	playerSprite->SetFrameSpeed(playerJson["frame_speed"].GetFloat());
	playerSprite->SetFrameWidth(playerJson["frame_width"].GetInt());
	playerSprite->SetFrameHeight(playerJson["frame_height"].GetInt());
	playerSprite->SetNumOfFrames(playerJson["num_frames"].GetInt());
	playerSprite->SetLooping(playerJson["looping"].GetBool());
	pAnimPlayer->setX(width / 2);
	pAnimPlayer->setY(height / 2);
	
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
		// GameState dictactes process and draw functions

		// Playing State
		if (m_gameState == m_gameState_e::playing) {
			while (m_lag >= stepSize)
			{
				Process(stepSize);
				m_lag -= stepSize;
				++m_numUpdates;
			}
			Draw(*m_pBackBuffer);
		}
		// Paused State
		else if (m_gameState == m_gameState_e::paused) {
			while (m_lag >= stepSize)
			{
				ProcessPauseState(stepSize);
				m_lag -= stepSize;
				++m_numUpdates;
			}
			Draw(*m_pBackBuffer);
			
		}
		// Game Over State
		else if (m_gameState == m_gameState_e::lost) {

		}
		// Menu State
		else if (m_gameState == m_gameState_e::menu) {

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
	
	// Spawn Enemy on a timer
	comparisonTime++;
	if (0==comparisonTime % 10) {
		int x = (0 + (rand() % (int)(3 - 0 + 1)));
		SpawnEnemy(x);
	}

	// Spawn Coins on a timer
	if (0 == comparisonTime % 100) {
		int x = (0 + (rand() % (int)(width - 0 + 1)));
		int y = (0 + (rand() % (int)(height - 0 + 1)));
		SpawnCoin(x, y);
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
		if (ene->IsCollidingWithAnim(*pAnimPlayer)) {
			// Damage player and set dead if no hp left
			pAnimPlayer->damagePlayerCheck(25);
			// Create animation hit effect
			SpawnExplosion(x, y);
		}
		// if out of bounds remove enemy
		else 
		if (x > width + 20 || x < -20 || y > height + 20
			|| y < -20) {
				delete *itEnemy;
				itEnemy = pEnemyVector.erase(itEnemy);
				SpawnExplosion(x, y);
		}
		else
			itEnemy++;
	}
	
	// Update player
	//pPlayer->Process(deltaTime);
	pAnimPlayer->Process(deltaTime);

	// Process Explosions
	for (int i = 0; i < pExplosionVector.size(); i++)
	{
		pExplosionVector[i]->Process(deltaTime);
	}

	// Process Coins
	for (itCoin = pCoinVector.begin(); itCoin < pCoinVector.end();)
	{
		Coin* coin = *itCoin;
		coin->Process(deltaTime);
		coin->processExistence(m_executionTime + 0.5);
		
		int x = coin->GetPositionX();
		int y = coin->GetPositionY();
		// If collision Collect coin and remove it
		if (pAnimPlayer->IsCollidingWithAnim(**itCoin)) {
			delete *itCoin;
			itCoin = pCoinVector.erase(itCoin);
			SpawnExplosion(x, y);
		}
		else
			itCoin++;
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

}


void 
Game::Draw(BackBuffer& backBuffer)
{
	++m_frameCount;

	backBuffer.Clear();

	// Draw enemies
	for (int i = 0; i < pEnemyVector.size(); i++) {
		pEnemyVector[i]->Draw(backBuffer);
	}

	// Draw Explosions
	for (int i = 0; i < pExplosionVector.size(); i++) {
		pExplosionVector[i]->Draw(backBuffer);
	}

	// Draw Coins
	for (int i = 0; i < pCoinVector.size(); i++) {
		pCoinVector[i]->Draw(backBuffer);
	}

	// Draw Player
	pAnimPlayer->Draw(backBuffer);

		

	/* Draw text according to gamestate */
		

	// Score Text Char
	char time[100];
	sprintf(time, "%d", int(m_executionTime + 0.5));

	// Health Text Char
	stringstream s;
	s << pAnimPlayer->m_hp;
	string healthString = "Health " + s.str();
	const char* healthChar = healthString.c_str();

	// Coin Text Char
	s << m_frameCount;
	string coinString = "FPS " + s.str();
	const char* coinChar = coinString.c_str();
		
	SDL_Color colour = { 0, 0, 0, 255 };
	// Draw Score Text
	m_pBackBuffer->DrawTextOnScreen(colour, "AmaticSC-Regular.ttf", time, 40, width-425, 0);
	// Draw Health Text
	m_pBackBuffer->DrawTextOnScreen(colour, "AmaticSC-Regular.ttf", healthChar, 40, width - 800, 0);
	// Draw Coins Text
	m_pBackBuffer->DrawTextOnScreen(colour, "AmaticSC-Regular.ttf", coinChar, 40, width - 200, 0);
	// Draw FPS
	//m_pBackBuffer->DrawTextOnScreen(colour, "AmaticSC-Regular.ttf", coinChar, 40, width - 800, 0);

	backBuffer.Present();
}

void 
Game::Quit()
{
	m_looping = false;
}

/* Input Methods */

// Routes all the input commands to check
// State and Input to determine what the player
// Can or cannot do
void
Game::InputRouter(InputControls input) {
	// Evaluate string input
	if (m_gameState == m_gameState_e::playing) {
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
}

/* Player movements */

void 
Game::MovePlayerLeft()
{
	pAnimPlayer->SetHorizontalVelocity(-playerSpeed);
}

void
Game::MovePlayerRight()
{
	pAnimPlayer->SetHorizontalVelocity(playerSpeed);
}

void
Game::MovePlayerUp()
{
	pAnimPlayer->SetVerticalVelocity(-playerSpeed);
}

void
Game::MovePlayerDown()
{
	pAnimPlayer->SetVerticalVelocity(playerSpeed);
}

/* Stop movement methods */

void
Game::StopMovePlayerHorizontal()
{
	pAnimPlayer->SetHorizontalVelocity(0);

}

void
Game::StopMovePlayerVertical()
{
	pAnimPlayer->SetVerticalVelocity(0);
}

void
Game::ResetMovement()
{
	pAnimPlayer->SetHorizontalVelocity(0);
	pAnimPlayer->SetVerticalVelocity(0);
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
	const Value& enemyJson = Parser::GetInstance().document["enemy"];
	int MAX_SPEED = enemyJson["max_speed"].GetInt();
	int MIN_SPEED = enemyJson["min_speed"].GetInt();
	string SPRITE_LOC = enemyJson["sprite_loc"].GetString();
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

void
Game::SpawnCoin(int x, int y)
{
	const Value& coinJson = Parser::GetInstance().document["coin"];
	AnimatedSprite* coinSprite = m_pBackBuffer->CreateAnimatedSprite(coinJson["sprite_loc"].GetString());
	Coin* e = new Coin();
	e->setLifeSpan(coinJson["life_span"].GetFloat());
	e->setTimeBorn(m_executionTime + 0.5);
	e->Initialise(coinSprite);
	coinSprite->SetFrameSpeed(coinJson["frame_speed"].GetFloat());
	coinSprite->SetFrameWidth(coinJson["frame_width"].GetInt());
	coinSprite->SetFrameHeight(coinJson["frame_height"].GetInt());
	coinSprite->SetNumOfFrames(coinJson["num_frames"].GetInt());
	coinSprite->SetLooping(coinJson["looping"].GetBool());

	e->setX(x);
	e->setY(y);
	
	pCoinVector.push_back(e);
}

float RandomFloat(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}