#ifndef PLAYER_H
#define PLAYER_H
#include "AnimEntity.h"

class Player : public AnimEntity
{
public:
	Player();
	~Player();
	bool damagePlayerCheck(int damage, float time);
	
	void setHitFrame();
	void setInvunrability(bool invunrable);
	void setIFrameTime(float time);
	void setCanGetCoins(bool coin);

	bool getInvunrability();
	bool canGetCoins = true;
	
	

// Class members
private:
	float m_iFrameTime;
	int m_timeHit;
};
#endif