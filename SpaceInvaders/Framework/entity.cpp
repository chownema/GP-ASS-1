// COMP710 GP 2D Framework

// This include:
#include "entity.h"

// Local includes:
#include "sprite.h"
#include "animatedsprite.h"
#include "backbuffer.h"
#include "logmanager.h"
#include "animentity.h"


// Library includes:
#include <cassert>
#include <math.h>
#include <algorithm>


// Size of window put in game h class
const int width = 800;
const int height = 600;


Entity::Entity()
: m_pSprite(0)
, m_x(0.0f)
, m_y(0.0f)
, m_velocityX(0.0f)
, m_velocityY(0.0f)
, m_dead(false)
{

}

Entity::~Entity()
{

}

bool
Entity::Initialise(Sprite* sprite)
{
	assert(sprite);
	m_pSprite = sprite;

	return (true);
}

bool
Entity::InitialiseAnim(AnimatedSprite* sprite)
{
	assert(sprite);
	m_pAnimSprite = sprite;

	return (true);
}

void 
Entity::Process(float deltaTime)
{

	m_pSprite->SetX(static_cast<int>(m_x));
	m_pSprite->SetY(static_cast<int>(m_y));

	// W02.1: Generic position update, based upon velocity (and time).
	m_x += m_velocityX;
	m_y += m_velocityY;
	
	// W02.1: Boundary checking and position capping.
	//if (m_x > width-32) {
	//	m_x = width-32;
	//	m_velocityX = 0;
	//}
	//else if (m_x < 0) {
	//	m_x = 0;
	//	m_velocityX = 0;
	//}
}

void
Entity::ProcessAnim(float deltaTime)
{
	m_pAnimSprite->Process(deltaTime);
}

void 
Entity::Draw(BackBuffer& backBuffer)
{
	assert(m_pSprite);
	m_pSprite->Draw(backBuffer);
}

void
Entity::DrawAnim(BackBuffer& backBuffer)
{
	assert(m_pAnimSprite);
	m_pAnimSprite->Draw(backBuffer);
}

bool
Entity::IsCollidingWith(Entity& e)
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
Entity::IsCollidingWithAnim(AnimEntity& e)
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
Entity::SetDead(bool dead)
{
	m_dead = dead;
}

float 
Entity::GetPositionX()
{
	return (m_x);
}

float 
Entity::GetPositionY()
{
	return (m_y);
}

void
Entity::setX(int x)
{
	m_x = x;
	m_pSprite->SetX(x);
}

void
Entity::setY(int y)
{
	m_y = y;
	m_pSprite->SetY(y);
}

void
Entity::setAnimX(int x)
{
	m_x = x;
	m_pAnimSprite->SetX(x);
}

void
Entity::setAnimY(int y)
{
	m_y = y;
	m_pAnimSprite->SetY(y);
}


float 
Entity::GetHorizontalVelocity()
{
	return (m_velocityX);
}

float 
Entity::GetVerticalVelocity()
{
	return (m_velocityY);
}

void 
Entity::SetHorizontalVelocity(float x)
{
	m_velocityX = x;
}

void 
Entity::SetVerticalVelocity(float y)
{
	m_velocityY = y;
}
