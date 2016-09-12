// This include
#include "SoundSystem.h"
#include "logmanager.h"



SoundSystem::SoundSystem()
{
	if (FMOD::System_Create(&m_pSystem) != FMOD_OK)
	{
		// Report Error
		LogManager::GetInstance().Log("FMOD Init Fail!");
		return;
	}

	int driverCount = 0;
	m_pSystem->getNumDrivers(&driverCount);

	if (driverCount == 0)
	{
		// Report Error
		LogManager::GetInstance().Log("FMOD driver Init Fail!");
		return;
	}

	// Initialize our Instance with 36 Channels
	m_pSystem->init(36, FMOD_INIT_NORMAL, 0);
}


void 
SoundSystem::createSound(FMOD::Sound* *pSound, const char* pFile)
{
	m_pSystem->createSound(pFile, FMOD_DEFAULT, 0, pSound);
}

void 
SoundSystem::playSound(FMOD::Sound* pSound, bool bLoop)
{
	
	if (!bLoop)
		pSound->setMode(FMOD_LOOP_OFF);
	else
	{
		pSound->setMode(FMOD_LOOP_NORMAL);
		pSound->setLoopCount(-1);
	}
	
	// might need a channel for the last args
	m_pSystem->playSound(pSound, 0, false, 0);
}

void 
SoundSystem::releaseSound(FMOD::Sound* pSound)
{
	pSound->release();
}