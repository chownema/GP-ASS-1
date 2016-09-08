#include "Enemy.h"

Enemy::Enemy()
{
	
};

Enemy::~Enemy()
{

};


void Enemy::pauseEnemy() // Counter logic?
{
	m_originVVelocity = this->GetVerticalVelocity();
	m_originHVelocity = this->GetHorizontalVelocity();
	this->SetHorizontalVelocity(0);
	this->SetVerticalVelocity(0);
	// CLG
	this->SetHorizontalVelocity(m_originHVelocity);
	this->SetVerticalVelocity(m_originVVelocity);
}
void Enemy::resumeEnemy()
{
	/*this->SetVerticalVelocity(this->m_originVVelocity);
	this->SetHorizontalVelocity(this->m_originHVelocity);*/
}