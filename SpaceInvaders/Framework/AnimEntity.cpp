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
, type("")
, a_invunrable(false)
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

	if (this->getType() == "player") {
		// no boundaries ;)
		// right
		if (m_x > 799)
		{
			m_x = -m_pAnimSprite->GetFrameWidth();
		}
		// left
		if (m_x < -m_pAnimSprite->GetFrameWidth())
		{
			m_x = 790;
		}
		// bottom
		if (m_y > 599)
		{
			m_y = 590-m_pAnimSprite->GetHeight();
			
		}
		// top
		if (m_y < -m_pAnimSprite->GetFrameWidth())
		{
			m_y = 590;

		}

		if (m_y < 0 || m_y > 600 -m_pAnimSprite->GetFrameHeight()
			|| m_x < 0 || m_x > 700 - -m_pAnimSprite->GetFrameWidth())
			m_hp -= 1;
			

		// Check if not moving
		if (m_canMove){
			if (m_velocityX == 0 && m_velocityY == 0 && !invunrable) {
				// Set Frame to still
				if (m_direction == "right")
					m_pAnimSprite->SetYDrawPos(0);
				else
					m_pAnimSprite->SetYDrawPos(m_pAnimSprite->GetFrameHeight() * 1);
			}
			else
				m_pAnimSprite->Pause(false);
		}
		else
			m_pAnimSprite->SetYDrawPos(m_pAnimSprite->GetFrameHeight() * 7);
	}
}

void
AnimEntity::Draw(BackBuffer& backBuffer)
{
	assert(m_pAnimSprite);
	m_pAnimSprite->Draw(backBuffer);
}

void
AnimEntity::setCanMove(bool move)
{
	m_canMove = move;
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
	float x1 = GetPositionX()+m_pAnimSprite->GetFrameWidth()/2;
	float y1 = GetPositionY()+m_pAnimSprite->GetFrameHeight()/2;

	// The param entity
	float x2 = e.GetPositionX()+e.m_pAnimSprite->GetFrameWidth() / 2;
	float y2 = e.GetPositionY()+e.m_pAnimSprite->GetFrameWidth() / 2;
	bool collide = false;

	// Distance Collision Variable 
	// averaging out height and width of both entities
	// May be too large for wide entities
	float collision = ((m_pAnimSprite->GetFrameWidth() / 2) + (m_pAnimSprite->GetFrameHeight() / 2) +
		(e.m_pAnimSprite->GetFrameWidth() / 2) + (e.m_pAnimSprite->GetFrameHeight() / 2))/2;

	float actualdistance = sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));

	// If hit
	if (actualdistance < collision)
	{
		return true;
	}
	return (false);
}

bool
AnimEntity::IsDead()
{
	return m_dead;
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

AnimatedSprite* 
AnimEntity::getAnimSprite() {

	return (m_pAnimSprite);
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

void
AnimEntity::setDirection(string direction)
{
	m_direction = direction;
}

string
AnimEntity::getDirection()
{
	return (m_direction);
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


string 
AnimEntity::getType()
{
	return (type);
}
void 
AnimEntity::setType(const string nType)
{
	type = nType;
}

void
AnimEntity::toggleAInvunrability(bool b)
{
	a_invunrable = b;
}

bool
AnimEntity::getAInvunrability()
{
	return a_invunrable;
}

void
AnimEntity::setCanGetCoins(bool coin)
{
	canGetCoin = coin;
}

void
AnimEntity::setCoins(int coins)
{
		m_coins = coins;
}

void
AnimEntity::incrementCoins(int coin)
{
	m_coins += coin;
}

int
AnimEntity::getHP()
{
	return(m_hp);
}

int
AnimEntity::getCoins()
{
	return(m_coins);
}

void
AnimEntity::setHitPoints(int hitPoints)
{
	m_hp = hitPoints;
}