#ifndef ENEMY_H
#define ENEMY_H
#include "animentity.h"

class Enemy : public AnimEntity
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