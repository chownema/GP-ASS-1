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
	void setCoins(int coin);
	void incrementCoins(int coin);
	
	int getCoins();
	int getHP();
	
// Class members
private:
	int m_hp;
	int m_coins;
};
#endif