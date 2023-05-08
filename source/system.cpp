#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <sys/stat.h>
#include <sys/dir.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <algorithm>

#include <nds/ipc.h>
#include <nds.h>
#include <fat.h>

#include <ulib/ulib.h>

#include <microcpp/system.h>
#include <microcpp/vars.h>

#define isRelative(path) \
    path[0] != '/' && \
    !strncmp("nitro:/", path, 5) && !strncmp("fat:/", path, 5)

bool compareFilename(FILELIST a, FILELIST b) {return a.name < b.name;}

namespace System
{
	int currentVramUsed()
	{
		return ulGetTexVramUsedMemory();
	}

	int currentVramFree()
	{
		return ulGetTexVramAvailMemory();
	}

	// This function returns a bizarre number
	int currentPalUsed()
	{
		return ulGetTexPalUsedMemory();
	}

	int currentPalFree()
	{
		return ulGetTexPalAvailMemory();
	}

	int currentVertexFree()
	{
		return ulGetVertexAvailMemory();
	}

	std::string currentDirectory()
	{
		char path[256];
		getcwd(path, 255);
		return path;
	}

	void changeDirectory(const char* dir)
	{
		chdir(dir);
	}

	void remove(const char* dir)
	{
		remove(dir);
	}

	void rename(const char* old, const char* New)
	{
		rename(old, New);
	}

	void makeDirectory(const char* dir)
	{
		mkdir(dir, 777);
	}

	bool fileExists(const char* file)
	{
		struct stat st;
		return stat(file, &st) == 0;
	}

	/*
	int mustSwap(lua_State *L, int dirList, int i) {
		// Special function to sort the final table placing folders first
		int isDir1, isDir2, nameCmp;
		char *name1 = malloc(256*sizeof(char)), *name2 = malloc(256*sizeof(char));
		
		lua_geti(L, dirList, i);
		lua_getfield(L, -1, "isDir");
		isDir1 = lua_toboolean(L, -1);
		lua_getfield(L, -2, "name");
		strcpy(name1, lua_tostring(L, -1));
		lua_pop(L, 3);                      // Removes elem[i], its 'isDir' and its 'name'
		lua_geti(L, dirList, i+1);
		lua_getfield(L, -1, "isDir");
		isDir2 = lua_toboolean(L, -1);
		lua_getfield(L, -2, "name");
		strcpy(name2, lua_tostring(L, -1));
		lua_pop(L, 3);                      // Idem
		
		nameCmp = strcmp(strlwr(name1), strlwr(name2));
		
		// hey guys, you forgot these lines so i added them for you
		free(name1);
		free(name2);
		name1 = NULL;
		name2 = NULL;
		
		return (!isDir1 && isDir2) || ((nameCmp > 0) && (isDir1 == isDir2));
	}
	*/

	std::vector<FILELIST> listDirectory(const char* askedPath, bool skipDotDirs)
	{
		char path[PATH_MAX] = "";
		struct dirent *entry;
		struct stat st;
		DIR *dir;
		// entryName points to the end of the absolute path leading to the folder (and to the start of the name of the entry in the path)
		char *entryName, *end = path + sizeof(path) - 1;
		int i = 1;
		std::vector<FILELIST> dirs, files;
		
		if (isRelative(askedPath) && getcwd(path, sizeof(path)) == NULL)
		{
			FILELIST file;
			file.name = "__ERROR";
			file.isDir = false;
			file.size = 0;
			files.push_back(file);
			return files;
		}
		if (strlen(path) + strlen(askedPath) >= sizeof(path))
		{
			FILELIST file;
			file.name = "__ERROR";
			file.isDir = false;
			file.size = 1;
			files.push_back(file);
			return files;
		}
		strcpy(path + strlen(path), askedPath);
		
		// We will append each entry's name there to the path
		entryName = path + strlen(path);
		
		// Make sure there's a trailing slash
		if (entryName[-1] != '/' && entryName < end)
			*entryName++ = '/';     // Also move the beginning of the entry's name to the right
		
		if ((dir = opendir(askedPath)) == NULL)
		{
			FILELIST file;
			file.name = "__ERROR";
			file.isDir = false;
			file.size = 2;
			files.push_back(file);
			return files;
		}
		
		while ((entry = readdir(dir)) != NULL) {    // Loop through the folder
			if (entryName + strlen(entry->d_name) >= end)
			{
				FILELIST file;
				file.name = "__ERROR";
				file.isDir = false;
				file.size = 3;
				files.push_back(file);
				return files;
			}
			
			strcpy(entryName, entry->d_name);
			
			if (stat(path, &st) != 0)
			{
				FILELIST file;
				file.name = "__ERROR";
				file.isDir = false;
				file.size = 4;
				files.push_back(file);
				return files;
			}
			
			// From now everything is okay

			if (entry->d_name[0] == '.' && skipDotDirs) continue;

			FILELIST file;
			file.name = entry->d_name;
			file.isDir = entry->d_type == DT_DIR;
			file.size = st.st_size;
			if (file.isDir)
				dirs.push_back(file);
			else
				files.push_back(file);

			i++;
		}
		
		closedir(dir);

		/*
		// Now we need to sort the table (we will use modified bubble sorting)
		// We use a custom function to put folders at the top of the table
		while (swapped) {
			swapped = 0;
			
			for (i = 1; i <= nbItems-1; i++) {
				if (mustSwap(L, dirList, i)) {
					lua_geti(L, dirList, i);
					lua_geti(L, dirList, i+1);
					lua_seti(L, dirList, i);
					lua_seti(L, dirList, i+1);
					swapped = 1;
				}
			}
		}
		*/

		std::sort(dirs.begin(), dirs.end(), compareFilename);
		std::sort(files.begin(), files.end(), compareFilename);
		files.insert(files.begin(), dirs.begin(), dirs.end());

		return files;
	}

	void setLedBlinkMode(int mode)
	{
		ledBlink(mode);
	}

	void systemShutDown()
	{
		systemShutDown();
	}

	void systemSleep()
	{
		systemSleep();
	}
}