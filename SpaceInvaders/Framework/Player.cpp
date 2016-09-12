#include <iostream>
#include "Player.h"
#include "sprite.h"
#include "AnimatedSprite.h"

using namespace std;

Player::Player()
{
	invunrable = false;
	m_timeHit = 0;
};


Player::~Player()
{

};

bool
Player::damagePlayerCheck(int damage, float time)
{
	if (m_timeHit == 0) {
		m_timeHit = time;
		// Damage player
		m_hp -= damage;
	}
	if ((time - m_timeHit) > m_iFrameTime)
	{
		// Set to normal
		invunrable = false;
		// Check if dead
		if (this->m_hp < 1) {
			return true;
		}
		// reset time hit
		m_timeHit = 0;
	}
	else 
	{
		// Set unhittable
		invunrable = true;
		
	}
	return (m_dead);
}

void
Player::setInvunrability(bool invunrability)
{
	invunrable = invunrability;
}

void
Player::setHitPoints(int hitPoints)
{
	m_hp = hitPoints;
}

void
Player::setHitFrame()
{
	m_pAnimSprite->SetYDrawPos(m_pAnimSprite->GetFrameHeight()*2);
}
void 
Player::setIFrameTime(float time)
{
	m_iFrameTime = time;
}

void
Player::setCoins(int coins)
{
	m_coins = coins;
}

void 
Player::incrementCoins(int coin)
{
	m_coins += coin;
}

int
Player::getHP()
{
	return(m_hp);
}

int
Player::getCoins()
{
	return(m_coins);
}

bool
Player::getInvunrability()
{
	return (invunrable);
}
