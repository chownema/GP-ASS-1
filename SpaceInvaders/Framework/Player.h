#ifndef PLAYER_H
#define PLAYER_H
#include "entity.h"

class Player : public Entity
{
public:
	Player();
	~Player();
	bool damagePlayerCheck(int damage);
	void setHitPoints(int hp);

// Class members
public:
	int m_hp;
	int m_coins;
};
#endif