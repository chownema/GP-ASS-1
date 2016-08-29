// COMP710 GP 2D Framework
#ifndef __GAME_H__
#define __GAME_H__

// Forward Declarations
class BackBuffer;
class InputHandler;
class Sprite;
class PlayerShip;
class AnimEntity;
class bullet;
class Enemy;
class SoundSystem;

#include "SoundSystem.h"
#include <vector>

class Game
{
	//Member Methods:
public:
	static Game& GetInstance();
	static void DestroyInstance();
	~Game();

	bool Initialise();
	bool DoGameLoop();
	void Quit();

	void MovePlayerLeft();
	void MovePlayerRight();
	void MovePlayerUp();
	void MovePlayerDown();

	void StopMovePlayerHorizontal();
	void StopMovePlayerVertical();


	void ResetMovement();
	void FireSpaceShipBullet();

	void SpawnEnemy(int x, int y);
	void SpawnExplosion(int x, int y);



	
protected:
	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);

private:
	Game(const Game& game);
	Game& operator=(const Game& game);
	
	Game();

	//Member Data:
public:

protected:
	static Game* sm_pInstance;
	BackBuffer* m_pBackBuffer;
	InputHandler* m_pInputHandler;
	bool m_looping;

	// Simulation Counters:
	float m_elapsedSeconds;
	float m_lag;
	float m_executionTime;
	int m_lastTime;
	int m_frameCount;
	int m_FPS;
	int m_numUpdates;
	bool m_drawDebugInfo;

	// Game Entities:
	// W02.1: Add a PlayerShip field
	PlayerShip* pPlayerShip;
	// W02.2: Add an alien enemy container field.
	std::vector<Enemy*> pEnemyVector;
	// W02.3: Add a bullet container field.
	std::vector<bullet*> pBulletVector;
	std::vector<AnimEntity*> pExplosionVector;
	
	// Vector Iterators
	std::vector<AnimEntity*>::iterator itExplosion;
	std::vector<Enemy*>::iterator itEnemy;
	std::vector<bullet*>::iterator itBullet;
	// FMOD
	SoundSystem sound;


private:

};

#endif // __GAME_H__
