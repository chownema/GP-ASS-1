#include <iostream>
#include "Enemy.h"
#include "sprite.h"

Enemy::Enemy(Sprite* Sprite, float X, float Y, float Velocityx, float Velocityy, bool Dead)
{
	
	m_pSprite = Sprite;
	m_dead = Dead;
	m_y = Y;
	m_x = X;
	m_velocityY = Velocityy;
	m_velocityX = Velocityx;
	
};
