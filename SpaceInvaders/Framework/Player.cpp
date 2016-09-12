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
	if ((time - m_timeHit) > m_iFrameTime && !a_invunrable)
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
Player::setHitFrame()
{
	m_pAnimSprite->SetYDrawPos(m_pAnimSprite->GetFrameHeight()*2);
}
void 
Player::setIFrameTime(float time)
{
	m_iFrameTime = time;
}

bool
Player::getInvunrability()
{
	return (invunrable);
}
