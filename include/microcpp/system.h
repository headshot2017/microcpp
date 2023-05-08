#ifndef MICROCPP_SYSTEM_H
#define MICROCPP_SYSTEM_H

#include <vector>
#include <string>

#include <microcpp/system.h>
#include <microcpp/vars.h>

struct FILELIST
{
	std::string name;
	u32 size;
	bool isDir;
};

namespace System
{
	int currentVramUsed();
	int currentVramFree();
	int currentPalUsed();
	int currentPalFree();
	int currentVertexFree();
	std::string currentDirectory();
	void changeDirectory(const char* dir);
	void remove(const char* dir);
	void rename(const char* old, const char* New);
	void makeDirectory(const char* dir);
	bool fileExists(const char* file);
	std::vector<FILELIST> listDirectory(const char* askedPath, bool skipDotDirs=false);
	void setLedBlinkMode(int mode);
	void systemShutDown();
	void systemSleep();
}

#endif
