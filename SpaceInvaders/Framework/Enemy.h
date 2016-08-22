#ifndef ENEMY_H
#define ENEMY_H
#include "entity.h"

class Enemy : public Entity
{
public:
	Enemy(Sprite* sprite, float x, float y, float velocityx, float velocityy, bool dead);
};
#endif