#ifndef COIN_H
#define COIN_H
#include "animentity.h"

class Coin : public AnimEntity
{
public:
	Coin();
	~Coin();
	void setValue(int value);
	void processExistence(int deltaTime);

	// class members
public:
	int value;
	float lifeSpan;
	float timeBorn;
	bool timeIsUp;
};
#endif