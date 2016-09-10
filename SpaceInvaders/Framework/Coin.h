#ifndef COIN_H
#define COIN_H
#include "animentity.h"

class Coin : public AnimEntity
{
public:
	Coin();
	~Coin();
	void setValue(int value);
	void setTimeBorn(float value);
	void setLifeSpan(float lifeSpan);
	void processExistence(float deltaTime);

	

	// class members
public:
	int value;
	float lifeSpan;
	float timeBorn;
};
#endif