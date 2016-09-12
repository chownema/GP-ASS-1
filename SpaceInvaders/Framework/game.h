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
class SoundClass;
class Coin;
class Parser;
class MenuItem;
class AnimatedSprite;

#include "SoundSystem.h"
#include "InputControls.h"
#include "rapidjson/document.h"
#include <vector>
#include <sstream>
#include <string>

using namespace std;

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

	void MovePlayerLeft(float dist);
	void MovePlayerRight(float dist);
	void MovePlayerUp(float dist);
	void MovePlayerDown(float dist);

	void StopMovePlayerHorizontal();
	void StopMovePlayerVertical();

	void ResetMovement();
	void PauseGame();

	void SpawnEnemy(int direction, int speed);
	void SpawnEnemyLine(int direction, int speed, int length);
	void SpawnExplosion(int x, int y, string direction);
	void SpawnCoin(int x, int y);
	void SpawnPlant();

	void playHitSound();

	void InputRouter(InputControls input);

	// sets up animation settings for a sprite and applies it to an animEntity
	void setupAnimSprite(AnimatedSprite* sprite, string type, AnimEntity* aEntity);

	void ResetGame();

	void setInvincibility();
	
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
	void StartGame();


	

private:
	Game(const Game& game);
	Game& operator=(const Game& game);
	
	Game();

	//Member Data:
public:
	// Used to convert int to strings
	std::stringstream s;

protected:
	// Sounds
	FMOD::Sound* playingBGM;
	FMOD::Sound* menuBGM;
	FMOD::Sound* catHitA;
	FMOD::Sound* catSoundA;
	FMOD::Sound* coinPickUp;


	static Game* sm_pInstance;
	BackBuffer* m_pBackBuffer;
	InputHandler* m_pInputHandler;
	bool m_looping;

	// FSM
	// Game States
	enum m_gameState_e {
		playing = 0, paused, menu, lost, shop
	} y2k;

	// Enemy Patterns
	enum m_enemyState_e {
		line = 0, wave, jaws, random, diagonal
	};

	// enemy attack formation
	int m_enemyState_e = random;

	bool m_programRunning = false;

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

	int m_difficultyIncrease = 0;
	// Amount spawning per second
	int m_spawningAmount;
	bool m_canSpawn;
	bool m_canIncreaseDifficulty;
	int m_increaseDifficulty;
	int m_difficultyCounter;
	int m_spawnCount;
	int m_spawnLimiter;
	int round;
	int offloader;


	// Variables used for the end game screen
	int m_timeSurvived;
	int m_coinsCollected;


	// Menu Entities
	MenuItem* pItemA;
	MenuItem* pItemB;

	// Game Entities:
	Player* pAnimPlayer;
	std::vector<Enemy*> pEnemyVector;
	std::vector<AnimEntity*> pExplosionVector;
	std::vector<Coin*> pCoinVector;
	std::vector<MenuItem*> pPlantsVector;

	// Vector Iterators
	std::vector<AnimEntity*>::iterator itExplosion;
	std::vector<Enemy*>::iterator itEnemy;
	std::vector<Coin*>::iterator itCoin;
	std::vector<MenuItem*>::iterator itPlant;
	// FMOD
	SoundSystem sound;



private:

};

#endif // __GAME_H__
