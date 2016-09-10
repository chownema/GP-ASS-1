#include <iostream>
#include "Player.h"
#include "sprite.h"

using namespace std;

Player::Player()
{

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
	return (m_dead);
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
