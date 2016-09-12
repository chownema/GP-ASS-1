// COMP710 GP 2D Framework
#ifndef __SOUNDSYSTEM_H__
#define __SOUNDSYSTEM_H__

#include "fmod.hpp"
#include <string>
//typedef FMOD::Sound* SoundClass;

class SoundSystem
{
public:
	// Pointer to the FMOD instance
	FMOD::System *m_pSystem;
	SoundSystem();
	
	// Class methods
	void createSound(FMOD::Sound* *pSound, const char* pFile);
	void playSound(FMOD::Sound* pSound, bool bLoop);
	void releaseSound(FMOD::Sound* pSound);

public:

};

#endif // __SOUNDSYSTEM_H__