// COMP710 GP 2D Framework
#ifndef __ENTITY_H__
#define __ENTITY_H__

// Forward Declarations:
class BackBuffer;
class Sprite;
class AnimatedSprite;
class AnimEntity;

class Entity
{
	//Member Methods:
public:
	Entity();
	~Entity();

	bool Initialise(Sprite* sprite);
	bool InitialiseAnim(AnimatedSprite* sprite);

	void Process(float deltaTime);
	void ProcessAnim(float deltaTime);
	void Draw(BackBuffer& backBuffer);
	void DrawAnim(BackBuffer& backBuffer);

	void SetDead(bool dead);
	bool IsDead() const;

	bool IsCollidingWith(Entity& e);
	bool IsCollidingWithAnim(AnimEntity& e);

	float GetPositionX();
	float GetPositionY();

	void setX(int x);
	void setY(int y);
	void setAnimX(int x);
	void setAnimY(int y);

	float GetHorizontalVelocity();
	void SetHorizontalVelocity(float x);

	float GetVerticalVelocity();
	void SetVerticalVelocity(float y);

protected:

private:
	Entity(const Entity& entity);
	Entity& operator=(const Entity& entity);

	//Member Data:
public:

protected:
	Sprite* m_pSprite;
	AnimatedSprite* m_pAnimSprite;

	float m_x;
	float m_y;

	float m_velocityX;
	float m_velocityY;

	bool m_dead;

private:

};

#endif //__ENTITY_H__
