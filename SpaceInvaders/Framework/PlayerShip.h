#ifndef PLAYERSHIP_H
#define PLAYERSHIP_H
#include "entity.h"

class PlayerShip : public Entity
{
public:
	PlayerShip(Sprite* sprite, float x, float y, float velocityx, float velocityy, bool dead);
};
#endif