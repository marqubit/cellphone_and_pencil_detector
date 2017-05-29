#ifndef __CSOUND_H
#define __CSOUND_H

#include "CSystemAudio.h"

class CSound : public CSystemAudio {
private:
	int iChannel;
	char *Dato;
	FSOUND_SAMPLE *Sample;

public:
	CSound();
	void FreeSound();
	bool LoadSound(const char *FileName);
	void Play_Sound();
	void StopSound();
	void SetSoundPaused(bool bActivo = true);
	void SetSoundVolume(int iVol = 128);
	void SetSoundLoop(bool bActivo = true);
	void SetSoundMute(bool bActivo = true);
	void SetSoundPanning(int iPan);
	void SetSoundSurround(bool bActivo = true);
	bool IsSoundPlaying();
	int GetSoundVolume();
	int GetSoundMute();
	int GetSoundPanning();
	int GetSoundLoop();
	int GetSoundPaused();
	int GetSoundSurround();

};

#endif