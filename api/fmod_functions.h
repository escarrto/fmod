#pragma once
#include "studio/inc/fmod_studio.hpp"

FMOD::Studio::System *setSystem()
{
	FMOD::Studio::System* system = NULL;
	FMOD::Studio::System::create(&system);
	return system;
}

FMOD::System *setLowLevelSystem(FMOD::Studio::System *system)
{
	FMOD::System* lowLevelSystem = NULL;
	system->getLowLevelSystem(&lowLevelSystem);
	return lowLevelSystem;
}

void setSoftwareFormat(FMOD::System *lowLevelSystem)
{
	lowLevelSystem->setSoftwareFormat(0, FMOD_SPEAKERMODE_5POINT1, 0);
}

void setInitialize(FMOD::Studio::System *system, void *extraDriverData)
{
	system->initialize(32, FMOD_STUDIO_INIT_LIVEUPDATE, FMOD_INIT_PROFILE_ENABLE, extraDriverData);
}

FMOD::Studio::Bank *setMasterBank(FMOD::Studio::System *system)
{
	FMOD::Studio::Bank* masterBank = NULL;
	system->loadBankFile(Common_MediaPath("Master Bank.bank"), FMOD_STUDIO_LOAD_BANK_NORMAL, &masterBank);
	return masterBank;
}

FMOD::Studio::Bank *setStringBank(FMOD::Studio::System *system)
{
	FMOD::Studio::Bank* stringsBank = NULL;
	system->loadBankFile(Common_MediaPath("Master Bank.strings.bank"), FMOD_STUDIO_LOAD_BANK_NORMAL, &stringsBank);
	return stringsBank;
}

FMOD::Studio::Bank *setMenuBank(FMOD::Studio::System *system)
{
	FMOD::Studio::Bank* menuBank = NULL;
	system->loadBankFile(Common_MediaPath("UI_Menu.bank"), FMOD_STUDIO_LOAD_BANK_NORMAL, &menuBank);
	return menuBank;
}

FMOD::Studio::EventDescription *setCancelDescription(FMOD::Studio::System *system)
{
	FMOD::Studio::EventDescription* cancelDescription = NULL;
	system->getEvent("event:/UI/Okay", &cancelDescription);
	return cancelDescription;
}

FMOD::Studio::EventDescription *setMySoundDescription(FMOD::Studio::System *system)
{
	FMOD::Studio::EventDescription* mySoundDescription = NULL;
	system->getEvent("event:/MySound", &mySoundDescription);
	return mySoundDescription;
}

FMOD::Studio::EventInstance *setEventInstance(FMOD::Studio::EventDescription *cancelDescription)
{
	FMOD::Studio::EventInstance* eventInstance = NULL;
	cancelDescription->createInstance(&eventInstance);
	return eventInstance;
}

void start(FMOD::Studio::EventInstance *eventInstance)
{
	eventInstance->start();
}

void release(FMOD::Studio::EventInstance *eventInstance)
{
	eventInstance->release();
}

void updateSystem(FMOD::Studio::System *system)
{
	system->update();
}

void unload(FMOD::Studio::Bank *nameBank)
{
	nameBank->unload();
}

void releaseSystem(FMOD::Studio::System *system)
{
	system->release();
}

