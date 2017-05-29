#ifndef __CSYSTEM_AUDIO_H
#define __CSYSTEM_AUDIO_H

#include <FMOD/fmod.h>

class CSystemAudio {
public:
	bool InitAudio(int iFrequency = 44100, int iChannels = 32, unsigned int iFlags = 0);
	void CloseAudio();
	void UpdateAudio() { FSOUND_Update(); }
	float GetCPUUsage() { return FSOUND_GetCPUUsage(); }
};
#endif