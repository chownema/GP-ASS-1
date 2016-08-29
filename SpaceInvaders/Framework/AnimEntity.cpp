#include "AnimEntity.h"
// Local includes:
#include "animatedsprite.h"
#include "backbuffer.h"
#include "logmanager.h"


// Library includes:
#include <cassert>
#include <math.h>
#include <algorithm>

// Size of window put in game h class
const int width = 800;
const int height = 600;

AnimEntity::AnimEntity()
: m_pAnimSprite(0)
, m_x(0.0f)
, m_y(0.0f)
, m_velocityX(0.0f)
, m_velocityY(0.0f)
, m_dead(false)
{

}

AnimEntity::~AnimEntity() {

};

bool
AnimEntity::Initialise(AnimatedSprite* sprite)
{
	assert(sprite);
	m_pAnimSprite = sprite;

	return (true);
}

void
AnimEntity::Process(float deltaTime)
{
	m_pAnimSprite->Process(deltaTime);

	//m_pAnimSprite->SetX(static_cast<int>(m_x));
	//m_pAnimSprite->SetY(static_cast<int>(m_y));

	//// W02.1: Generic position update, based upon velocity (and time).
	//m_x += m_velocityX;
	//m_y += m_velocityY;

	//// W02.1: Boundary checking and position capping.
	//if (m_x > width - 32) {
	//	m_x = width - 32;
	//	m_velocityX = 0;
	//}
	//else if (m_x < 0) {
	//	m_x = 0;

	//}
}

void
AnimEntity::Draw(BackBuffer& backBuffer)
{
	assert(m_pAnimSprite);
	m_pAnimSprite->Draw(backBuffer);
}

bool
AnimEntity::IsCollidingWith(AnimEntity& e)
{


	// this entity
	float x1 = GetPositionX();
	float y1 = GetPositionY();

	// the param entity
	float x2 = e.GetPositionX();
	float y2 = e.GetPositionY();
	bool collide = false;
	int r = 1;
	float r1f = static_cast<int>(r);
	float r2f = static_cast<int>(r);


	//float collision = r1f + r2f;
	float collision = 10;
	// W02.3: Generic Entity Collision routine.
	float actualdistance = sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));

	char buffer[256];
	sprintf(buffer, "%f", actualdistance);
	//LogManager::GetInstance().Log(buffer);

	// W02.3: Does this object collide with the e object?
	if (actualdistance < collision)
	{
		collide = true;
	}
	// W02.3: Create a circle for each entity (this and e).

	// W02.3: Check for intersection.
	// W02.3: Using circle-vs-circle collision detection.

	// W02.3: Return result of collision.
	if (collide == true)
	{
		return(collide);
	}

	return (false); // W02.4 Change return value!

}

void
AnimEntity::SetDead(bool dead)
{
	m_dead = dead;
}

float
AnimEntity::GetPositionX()
{
	return (m_x);
}

float
AnimEntity::GetPositionY()
{
	return (m_y);
}

void
AnimEntity::setX(int x)
{
	m_x = x;
	m_pAnimSprite->SetX(x);
}

void
AnimEntity::setY(int y)
{
	m_y = y;
	m_pAnimSprite->SetY(y);
}


float
AnimEntity::GetHorizontalVelocity()
{
	return (m_velocityX);
}

float
AnimEntity::GetVerticalVelocity()
{
	return (m_velocityY);
}

void
AnimEntity::SetHorizontalVelocity(float x)
{
	m_velocityX = x;
}

void
AnimEntity::SetVerticalVelocity(float y)
{
	m_velocityY = y;
}
