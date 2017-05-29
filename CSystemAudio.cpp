#include "CSystemAudio.h"

void CSystemAudio::CloseAudio()
{
	FSOUND_Close();
}

bool CSystemAudio::InitAudio(int iFrequency, int iChannels, unsigned int iFlags)
{
	if (FSOUND_GetVersion() < FMOD_VERSION)
		return false;

	if (!FSOUND_Init(iFrequency, iChannels, iFlags))
		return false;

	return true;
}
