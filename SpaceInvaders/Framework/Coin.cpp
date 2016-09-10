#include <iostream>
#include "Coin.h"
#include "AnimatedSprite.h"

using namespace std;

Coin::Coin()
{
	m_dead = false;
	lifeSpan = 0.1;
};


Coin::~Coin()
{

};

void
Coin::setValue(int val) 
{
	value = val;
}

void
Coin::setTimeBorn(float val)
{
	timeBorn = val;
}

void
Coin::setLifeSpan(float val)
{
	lifeSpan = val;
}

void
Coin::processExistence(float time)
{
	// Speed up coin over its existence
	m_pAnimSprite->SetFrameSpeed(m_pAnimSprite->GetFrameSpeed() - 0.005);
	// Take current time compare time to life span
	if ((time - timeBorn) > lifeSpan) {
		// Set Time is up true to animate out and remove from container
		m_dead = true;
	}
}
