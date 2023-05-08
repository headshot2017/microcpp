#ifndef MICROCPP_SOUND_H
#define MICROCPP_SOUND_H

#include <maxmod9.h>

namespace Sound
{
	// ########## BANKS ##########

	void loadBank(const char* filename);
	void unloadBank();

	// ########## MODS ##########

	void loadMod(int mod);
	void unloadMod(int mod);
	void startMod(int mod, int mode);
	void pause();
	void resume();
	void stop();
	void setPosition(int pos);
	bool isActive();
	void startJingle(int mod);
	void setModVolume(int vol);
	void setJingleVolume(int vol);
	void setModTempo(int tempo);
	void setModPitch(int pitch);

	// ########## SFX ##########

	void loadSFX(int sfx);
	void unloadSFX(int sfx);
	mm_sfxhand startSFX(int sfx);
	void setSFXVolume(mm_sfxhand handle, int vol);
	void setSFXPanning(mm_sfxhand handle, int pan);
	void setSFXPitch(mm_sfxhand handle, int pitch);
	void setSFXScalePitch(mm_sfxhand handle, int factor);
	void stopSFX(mm_sfxhand handle);
	void releaseSFX(mm_sfxhand handle);
	void stopAllSFX();
}

#endif
