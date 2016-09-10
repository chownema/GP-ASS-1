#ifndef PLAYER_H
#define PLAYER_H
#include "AnimEntity.h"

class Player : public AnimEntity
{
public:
	Player();
	~Player();
	bool damagePlayerCheck(int damage, float time);
	void setHitPoints(int hp);
	void setCoins(int coin);
	void incrementCoins(int coin);
	void setHitFrame();
	void setInvunrability(bool invunrable);
	void setIFrameTime(float time);

	int getCoins();
	int getHP();
	bool getInvunrability();
	

// Class members
private:
	int m_hp;
	int m_coins;
	float m_iFrameTime;
	int m_timeHit;
	bool invunrable;
};
#endif