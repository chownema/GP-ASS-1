#include <iostream>
#include "Player.h"
#include "sprite.h"

using namespace std;

Player::Player()
{
	m_hp = 100;
};


Player::~Player()
{

};

bool
Player::damagePlayerCheck(int damage)
{
	// Damage player
	m_hp -= damage;
	// Check if dead
	if (this->m_hp <= 0) {
		this->SetDead(true);
	}
	return m_dead;
}

void
Player::setHitPoints(int hitPoints)
{
	m_hp = hitPoints;
}

void
Player::setCoins(int coins)
{
	m_coins = coins;
}