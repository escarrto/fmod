#ifndef GODOT_setFMOD_H
#define GODOT_setFMOD_H

#include "scene/main/node.h"
#include "../../core/ustring.h"
#include "api/lowlevel/inc/fmod.hpp"
#include "api/lowlevel/inc/fmod_common.h"
#include "api/studio/inc/fmod_studio.hpp"
#include "api/studio/inc/fmod_studio_common.h"
#include <algorithm>
#include <vector>

struct eventInfo
{
	std::string _eventNameDescription;
	FMOD::Studio::EventDescription *_eventDescription;
	FMOD::Studio::EventInstance *_eventInstance;
};

class setFMOD : public Node 
{
	GDCLASS(setFMOD, Node);

protected:

	/* FMOD Basic System */
	static void _bind_methods();
	void *extraDriverData;
	const char *banksPath;

	FMOD::Studio::System *system;
	FMOD::System* lowLevelSystem;

	FMOD::Studio::Bank* masterBank;
	FMOD::Studio::Bank* stringsBank;
	FMOD::Studio::Bank* Bank;

	std::string stdBanksPath;
	std::vector<eventInfo> eventInfoList;
	
public:
	FMOD::Studio::System *setSystem();
	FMOD::System *setLowLevelSystem();
	
	FMOD::Studio::Bank *setMasterBank();
	FMOD::Studio::Bank *setStringBank();
	FMOD::Studio::Bank *setNameBank(const char *nameBank);

	void setSoftwareFormat();
	void setInitialize();
	void setSystemUpdate();
	void setSystemRelease();
	void unsetBanks();
	void unsetStringsBank();
	void unsetMasterBank();

	void createEventDescription(String godotEventInstancePath, String godotSetEventNameDescription);
	void createEventInstance(String godotEventNameDescription);
	void start(String godotEventNameDescription);
	void release(String godotEventNameDescription);
	void setBanks(String godotBankList);
	void setBanksPath(String godotBanksPath);

	int findIndex(std::vector<eventInfo> list, std::string name);

	const char *Path(const char *fileName);
	const char *toConstChar(String godotString);

	std::string toString(String godotString);
	std::vector<std::string> setBankList(std::string rawBankList);

	/* FMOD Parameter System */
	void setParameterValue(String godotEventNameDescription, String godotParameterName, float parameterValue);
	
	setFMOD();
};
#endif