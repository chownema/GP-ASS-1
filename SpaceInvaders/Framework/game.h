// COMP710 GP 2D Framework
#ifndef __GAME_H__
#define __GAME_H__

// Forward Declarations
class BackBuffer;
class InputHandler;
class Sprite;
class Player;
class AnimEntity;
class Enemy;
class SoundSystem;
class Coin;
class Parser;
class MenuItem;

#include "SoundSystem.h"
#include "InputControls.h"
#include <vector>
#include <sstream>

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
	void PauseGame();

	void SpawnEnemy(int direction);
	void SpawnExplosion(int x, int y);
	void SpawnCoin(int x, int y);

	void InputRouter(InputControls input);


	
protected:
	// Draw and Process methods for their own respective GameStates
	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);
	// Menu
	void ProcessMenuState(float deltaTime);
	void DrawMenuState(BackBuffer& backBuffer);
	// Pause Menu
	void ProcessPauseState(float deltaTime);
	void DrawPauseState(BackBuffer& backBuffer);
	// Game over
	void ProcessGameOverState(float deltaTime);
	void DrawGameOverState(BackBuffer& backBuffer);
	
	void resumeInit();

private:
	Game(const Game& game);
	Game& operator=(const Game& game);
	
	Game();

	//Member Data:
public:
	// Used to convert int to strings
	std::stringstream s;

protected:
	static Game* sm_pInstance;
	BackBuffer* m_pBackBuffer;
	InputHandler* m_pInputHandler;
	bool m_looping;

	// FSM
	// Game States
	enum m_gameState_e {
		playing = 0, paused, menu, lost, shop
	} y2k;

	// Simulation Counters:
	float m_elapsedSecondsTotal;
	float m_elapsedSeconds;
	float m_lag;
	float m_executionTime;
	int m_lastTime;
	int m_frameCount;
	int m_FPS;
	int m_numUpdates;
	bool m_drawDebugInfo;
	int m_gameState = menu; // set init value for start of game

	// Menu Entities
	MenuItem* pItemA;
	MenuItem* pItemB;

	// Game Entities:
	Player* pAnimPlayer;
	std::vector<Enemy*> pEnemyVector;
	std::vector<AnimEntity*> pExplosionVector;
	std::vector<Coin*> pCoinVector;
	
	// Vector Iterators
	std::vector<AnimEntity*>::iterator itExplosion;
	std::vector<Enemy*>::iterator itEnemy;
	std::vector<Coin*>::iterator itCoin;
	// FMOD
	SoundSystem sound;



private:

};

#endif // __GAME_H__
