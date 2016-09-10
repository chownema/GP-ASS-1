#include "AnimEntity.h"
// Local includes:
#include "animatedsprite.h"
#include "backbuffer.h"
#include "logmanager.h"
#include "entity.h"


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

	m_pAnimSprite->SetX(static_cast<int>(m_x));
	m_pAnimSprite->SetY(static_cast<int>(m_y));

	m_x += m_velocityX;
	m_y += m_velocityY;
}

void
AnimEntity::Draw(BackBuffer& backBuffer)
{
	assert(m_pAnimSprite);
	m_pAnimSprite->Draw(backBuffer);
}

bool
AnimEntity::IsCollidingWith(Entity& e)
{
	// this entity
	float x1 = GetPositionX();
	float y1 = GetPositionY();

	// the param entity
	float x2 = e.GetPositionX();
	float y2 = e.GetPositionY();

	float collision = 15;
	// W02.3: Generic Entity Collision routine.
	float actualdistance = sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
	if (actualdistance < collision)
	{
		return true;
	}
	return (false);
}


bool
AnimEntity::IsCollidingWithAnim(AnimEntity& e)
{
	// This entity
	float x1 = GetPositionX();
	float y1 = GetPositionY();

	// The param entity
	float x2 = e.GetPositionX();
	float y2 = e.GetPositionY();
	bool collide = false;

	// Distance Collision Variable
	float collision = 30;
	float actualdistance = sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));

	// If hit
	if (actualdistance < collision)
	{
		return true;
	}
	return (false);
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
