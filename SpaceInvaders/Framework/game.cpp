// COMP710 GP 2D Framework

// This includes:
#include "game.h"

// Local includes:
#include "backbuffer.h"
#include "inputhandler.h"
#include "logmanager.h"
#include "sprite.h"
#include "PlayerShip.h"
#include "bullet.h"
#include "Enemy.h"
#include "texture.h"
#include "math.h"
#include "AnimEntity.h"
#include "AnimatedSprite.h"
#include "SoundSystem.h"


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
	//// Intit FMOD object
	//FMOD_RESULT System_Create(FMOD::System **system);
	////System::init(,,);
	////FSOUND_Init(44100, 32, 0);
	//FMOD_RESULT result;
	//FMOD::System *system = NULL;

	//result = FMOD::System_Create(&system);      // Create the main system object.
	//if (result != FMOD_OK)
	//{
	//	printf("FMOD error! (%d) %s\n", result, "error 1");
	//	exit(-1);
	//}

	//result = system->init(512, FMOD_INIT_NORMAL, 0);    // Initialize FMOD.
	//if (result != FMOD_OK)
	//{
	//	printf("FMOD error! (%d) %s\n", result, "error ");
	//	exit(-1);
	//}

	// Fmod Init
	




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


	// W02.1: Load the player ship sprite.
	// For example: Sprite* pPlayerSprite = m_pBackBuffer->CreateSprite("assets\\playership.png");
	Sprite* pPlayerSprite = m_pBackBuffer->CreateSprite("assets\\playership.png");
	assert(pPlayerSprite);
	// W02.1: Create the player ship instance.
	pPlayerShip = new PlayerShip(pPlayerSprite, 0.0f, 500.0f, 0.0f, 0.0f, false);
	pPlayerShip->setX(500);
	pPlayerShip->Initialise(pPlayerSprite);
	
	// W02.2: Spawn four rows of 14 alien enemies.
	//int x = 40;
	//int y = 0;

	// test enemy for collision
	//SpawnEnemy(pPlayerShip->GetPositionX(), pPlayerShip->GetPositionY()-49);
	//
	//for (int i = 0; i < 3; i++) {
	//	for (int j = 0; j < 13; j++) {
	//		SpawnEnemy(x, y);
	//		x += 55;
	//	}
	//	y += 50;
	//	x = 40;
	//}
	
	
	// W02.2: Fill the container with these new enemies.
	m_lastTime = SDL_GetTicks();
	m_lag = 0.0f;

	// Create a sample sound
	//SoundClass soundSample;
	//sound.createSound(&soundSample, "sounds\\drumloop.wav");

	//// Play the sound, with loop mode
	//sound.playSound(soundSample, true);

	// Do something meanwhile...

	// Release the sound
	//sound.releaseSound(soundSample);

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

		while (m_lag >= stepSize)
		{
			Process(stepSize);

			m_lag -= stepSize;

			++m_numUpdates;
		}
		
		Draw(*m_pBackBuffer);
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
		int x = (40 + (rand() % (int)(700 - 40 + 1)));
		SpawnEnemy(x, 0);
	}

	// Frame Counter:
	if (m_elapsedSeconds > 1)
	{
		m_elapsedSeconds -= 1;
		m_FPS = m_frameCount;
		m_frameCount = 0;
	}

	// Update the game world simulation:
	
	for (itEnemy = pEnemyVector.begin(); itEnemy < pEnemyVector.end();)
	{
		Enemy* ene = *itEnemy;
		ene->Process(deltaTime);
		if (pPlayerShip->IsCollidingWith(**itEnemy)) {
			int x = ene->GetPositionX();
			int y = ene->GetPositionY();
			
			delete *itEnemy;
			itEnemy = pEnemyVector.erase(itEnemy);
			SpawnExplosion(x, y);
			hitCount++;
		}
		else
			itEnemy++;
	}

	// W02.3: Process each bullet in the container.
	
	// W02.1: Update player...
	pPlayerShip->Process(deltaTime);

	//for (itExplosion = pExplosionVector.begin(); itExplosion < pExplosionVector.end();)
	//{
	//	AnimEntity* ex = *itExplosion;
	//	ex->Process(deltaTime);
	//}
	for (int i = 0; i < pExplosionVector.size(); i++)
	{
		pExplosionVector[i]->Process(deltaTime);
	}

	


	

	//itEnemy = pEnemyVector.begin();
	//itBullet = pBulletVector.begin();
	//
	//bool hitEnemy = false;
	//for (itBullet = pBulletVector.begin(); itBullet < pBulletVector.end();)
	//{
	//	for (itEnemy = pEnemyVector.begin(); itEnemy < pEnemyVector.end();)
	//	{
	//		bullet* bull = *itBullet;
	//		Enemy* ene = *itEnemy;
	//		if (bull->IsCollidingWith(**itEnemy)) {
	//			bull->SetVerticalVelocity(0);
	//			itEnemy = pEnemyVector.erase(itEnemy);
	//			hitEnemy = true;
	//		}
	//		else
	//			itEnemy++;
	//	}
	//	if (hitEnemy) {
	//		itBullet = pBulletVector.erase(itBullet);
	//		hitEnemy = false;
	//	}
	//	else
	//		itBullet++;
	//}
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


		// W02.3: Draw all bullets in container...
		for (int i = 0; i < pBulletVector.size(); i++) {
			pBulletVector[i]->Draw(backBuffer);
		}

		for (int i = 0; i < pExplosionVector.size(); i++) {
			pExplosionVector[i]->Draw(backBuffer);
		}

		// W02.1: Draw the player ship...
		pPlayerShip->Draw(backBuffer);
	

	backBuffer.Present();
}

void 
Game::Quit()
{
	m_looping = false;
}

void 
Game::MoveSpaceShipLeft()
{
	// W02.1: Tell the player ship to move left.
	pPlayerShip->SetHorizontalVelocity(-5);
}

// W02.1: Add the method to tell the player ship to move right...
void
Game::MoveSpaceShipRight()
{
	// W02.1: Tell the player ship to move Right.
	pPlayerShip->SetHorizontalVelocity(5);
}

void
Game::MoveSpaceShipUp()
{
	// W02.1: Tell the player ship to move Right.
	pPlayerShip->SetVerticalVelocity(-5);
}

void
Game::MoveSpaceShipDown()
{
	// W02.1: Tell the player ship to move Right.
	pPlayerShip->SetVerticalVelocity(5);
}

void
Game::ResetMovement()
{
	pPlayerShip->SetHorizontalVelocity(0);
	pPlayerShip->SetVerticalVelocity(0);
}


// W02.3: Space a Bullet in game.
void 
Game::FireSpaceShipBullet()
{



	//// W02.3: Load the player bullet sprite.      
	//Sprite*	bulletSprite = m_pBackBuffer->CreateSprite("assets\\bullet.png");

	//// W02.3: Create a new bullet object.
	//bullet* b = new bullet();
	//b->Initialise(bulletSprite);
	//int x = pPlayerShip->GetPositionX();
	//int y = pPlayerShip->GetPositionY();
	//

	//b->setX(x);
	//b->setY(y);
	//// W02.3: Set the bullets vertical velocity.
	//b->SetVerticalVelocity(-10);
	//// W02.3: Add the new bullet to the bullet container.
	//pBulletVector.push_back(b);
	
}

// W02.2: Spawn a Enemy in game.
void 
Game::SpawnEnemy(int x, int y)
{
	// W02.2: Load the alien enemy sprite file.
	Sprite* enemySprite = m_pBackBuffer->CreateSprite("assets\\alienenemy.png");

	// W02.2: Create a new Enemy object.
	Enemy* e = new Enemy(enemySprite, x, y, 0.0f, 0.0f, false);
	e->Initialise(enemySprite);
	e->setX(x);
	e->setY(y);
	int speed = 1 + (rand() % (int)(10 - 1 + 1));
	e->SetVerticalVelocity(speed);

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