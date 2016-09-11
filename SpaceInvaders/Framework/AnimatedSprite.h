#ifndef __ANIMATEDSPRITE_H__
#define __ANIMATEDSPRITE_H__

#include "sprite.h"

class BackBuffer;
class Texture;
class entity;

#include <vector>

class AnimatedSprite : public Sprite
{
	// Methods:
public:
	AnimatedSprite();
	~AnimatedSprite();

	bool Initialise(Texture& texture);
	void AddFrame(int x);

	void Process(float deltaTime);
	void Draw(BackBuffer& backbuffer);

	void SetFrameSpeed(float f);
	void SetFrameWidth(int w);
	void SetFrameHeight(int h);
	void SetNumOfFrames(int f);
	void SetYDrawPos(int y);

	int GetFrameHeight();
	int GetFrameWidth();
	int GetCurrentFrame();
	int GetNumOfFrames();
	float GetFrameSpeed();
	int getYDrawPos();

	void Pause(bool pause);
	bool IsPaused();

	bool IsAnimating();
	void StartAnimating();

	bool IsLooping();
	void SetLooping(bool b);

protected:

private:

	// Fields:
public:

protected:
	// W02.4: Add a field, the container for frame coordinates.
	std::vector<int*> pAnimatedSpriteVector;
	std::vector<AnimatedSprite*>::iterator itAnimatedSprite;

	float m_frameSpeed;
	int m_frameWidth;
	int m_frameHeight;
	int yDrawPos;

	float m_timeElapsed;
	int m_currentFrame;
	int m_numOfFrames;

	bool m_paused;
	bool m_loop;
	bool m_animating;

private:

};

#endif // __ANIMATEDSPRITE_H__