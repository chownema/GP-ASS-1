#ifndef ENEMY_H
#define ENEMY_H
#include "entity.h"

class Enemy : public Entity
{
public:
	Enemy();
	~Enemy();
	void pauseEnemy();
	void resumeEnemy();

// class memebers
public:
	int m_originVVelocity;
	int m_originHVelocity;
	
};
#endif