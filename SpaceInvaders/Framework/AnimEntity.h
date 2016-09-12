#ifndef ANINENTITY_H
#define ANINENTITY_H

// Forward Declarations:
class BackBuffer;
class AnimatedSprite;
class Entity;

#include <string>

class AnimEntity
{
public:
	AnimEntity();
	~AnimEntity();

	bool Initialise(AnimatedSprite* sprite);
	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);

	void SetDead(bool dead);
	bool IsDead();

	float GetPositionX();
	float GetPositionY();

	std::string getType();
	void setType(const std::string type);

	void setDirection(std::string direction);
	std::string getDirection();

	AnimatedSprite* getAnimSprite();

	void setX(int x);
	void setY(int y);

	float GetHorizontalVelocity();
	void SetHorizontalVelocity(float x);

	bool IsCollidingWith(Entity& e);
	bool IsCollidingWithAnim(AnimEntity& e);

	float GetVerticalVelocity();
	void SetVerticalVelocity(float y);

	void setCanMove(bool move);

	// Get and Toggle admin invunrability
	// Player
	void toggleAInvunrability(bool bol);
	bool getAInvunrability();

	void setCanGetCoins(bool coin);
	void setHitPoints(int hp);
	int getCoins();
	int getHP();
	void setCoins(int coin);
	void incrementCoins(int coin);

protected:
	bool canGetCoin = true;
	
	AnimatedSprite* m_pAnimSprite;

	int m_hp;
	int m_coins;

	float m_x;
	float m_y;

	float m_velocityX;
	float m_velocityY;

	bool m_dead;
	bool m_canMove = true;
	std::string m_direction;

	bool invunrable;
	bool a_invunrable = false; // overrides invunrable 

	// type of entity
	std::string type;

};
#endif // __ANINENTITY_H__