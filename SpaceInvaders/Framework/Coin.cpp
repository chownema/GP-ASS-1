#include <iostream>
#include "Coin.h"

using namespace std;

Coin::Coin()
{
	timeIsUp = false;
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
Coin::processExistence(int time)
{
	// Take current time
	// Compare time to life span
	if ((time - timeBorn) > lifeSpan) {
		// Animate out
		
		// Set Time is up true
		timeIsUp = true;
	}
	
}
