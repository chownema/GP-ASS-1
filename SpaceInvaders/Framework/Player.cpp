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
	//// Damage player
	//m_hp - damage;
	//// Check if dead
	//if (this->m_hp <= 0) {
	//	this->SetDead(true);
	//}
	//return this->IsDead();
	return true;
}

void
Player::setHitPoints(int hitPoints)
{
	m_hp = hitPoints;
}