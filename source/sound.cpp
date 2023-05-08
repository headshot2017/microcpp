#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/dir.h>

#include <ulib/ulib.h>
#include <maxmod9.h>

#include <microcpp/sound.h>
#include <microcpp/vars.h>

namespace Sound
{
	// ########## BANKS ##########

	void loadBank(const char* filename)
	{
		struct stat file_status;
		if(stat(filename, &file_status) != 0) return;
		mmInitDefault((char*)filename);
	}

	void unloadBank()
	{
		mmInitDefaultMem((mm_addr)0);
	}

	// ########## MODS ##########

	void loadMod(int mod)
	{
		mmLoad(mod);
	}

	void unloadMod(int mod)
	{
		mmUnload(mod);
	}

	void startMod(int mod, int mode)
	{
		mmStart(mod, (mode == 0) ? MM_PLAY_LOOP : MM_PLAY_ONCE);
	}

	void pause()
	{
		mmPause();
	}

	void resume()
	{
		mmResume();
	}

	void stop()
	{
		mmStop();
	}

	void setPosition(int pos)
	{
		mmPosition(pos);
	}

	bool isActive()
	{
		return mmActive();
	}

	void startJingle(int mod)
	{
		mmJingle(mod);
	}

	void setModVolume(int vol)
	{
		mmSetModuleVolume(vol);
	}

	void setJingleVolume(int vol)
	{
		mmSetJingleVolume(vol);
	}

	void setModTempo(int tempo)
	{
		mmSetModuleTempo(tempo);
	}

	void setModPitch(int pitch)
	{
		mmSetModulePitch(pitch);
	}

	// ########## SFX ##########

	void loadSFX(int sfx)
	{
		mmLoadEffect(sfx);
	}

	void unloadSFX(int sfx)
	{
		mmUnloadEffect(sfx);
	}

	mm_sfxhand startSFX(int sfx) // mm_sfxhand is also u16
	{
		return mmEffect(sfx);
	}

	void setSFXVolume(mm_sfxhand handle, int vol)
	{
		mmEffectVolume(handle, vol);
	}

	void setSFXPanning(mm_sfxhand handle, int pan)
	{
		mmEffectPanning(handle, pan);
	}

	void setSFXPitch(mm_sfxhand handle, int pitch)
	{
		mmEffectPanning(handle, pitch);
	}

	void setSFXScalePitch(mm_sfxhand handle, int factor)
	{
		mmEffectScaleRate(handle, factor);
	}

	void stopSFX(mm_sfxhand handle)
	{
		mmEffectCancel(handle);
	}

	void releaseSFX(mm_sfxhand handle)
	{
		mmEffectRelease(handle);
	}

	void stopAllSFX()
	{
		mmEffectCancelAll();
	}
}
