#ifndef PLAYER_H
#define PLAYER_H
#include "AnimEntity.h"

class Player : public AnimEntity
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