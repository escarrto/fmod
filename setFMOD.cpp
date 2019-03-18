#include "setFMOD.h"

FMOD::Studio::System* setFMOD::setSystem()
{
	system = NULL;
	FMOD::Studio::System::create(&system);
	return system;
}
FMOD::System* setFMOD::setLowLevelSystem()
{
	lowLevelSystem = NULL;
	system->getLowLevelSystem(&lowLevelSystem);
	return lowLevelSystem;
}

FMOD::Studio::Bank* setFMOD::setMasterBank()
{
	masterBank = NULL;
	system->loadBankFile(Path("Master Bank.bank"), FMOD_STUDIO_LOAD_BANK_NORMAL, &masterBank);
	return masterBank;
}
FMOD::Studio::Bank* setFMOD::setStringBank()
{
	stringsBank = NULL;
	system->loadBankFile(Path("Master Bank.strings.bank"), FMOD_STUDIO_LOAD_BANK_NORMAL, &stringsBank);
	return stringsBank;
}
FMOD::Studio::Bank* setFMOD::setNameBank(const char *nameBank)
{
	Bank = NULL;
	system->loadBankFile((Path(nameBank)), FMOD_STUDIO_LOAD_BANK_NORMAL, &Bank);
	return Bank;
}

void setFMOD::setSoftwareFormat()
{
	lowLevelSystem->setSoftwareFormat(0, FMOD_SPEAKERMODE_5POINT1, 0);
}
void setFMOD::setInitialize()
{
	extraDriverData = NULL;
	system->initialize(32, FMOD_STUDIO_INIT_LIVEUPDATE, FMOD_INIT_PROFILE_ENABLE, extraDriverData);
}
void setFMOD::setSystemUpdate()
{
	system->update();
}
void setFMOD::setSystemRelease()
{
	system->release();
}
void setFMOD::unsetBanks()
{
	Bank->unload();
}
void setFMOD::unsetStringsBank()
{
	stringsBank->unload();
}
void setFMOD::unsetMasterBank()
{
	masterBank->unload();
}
void setFMOD::createEventDescription(String godotEventInstancePath, String godotSetEventNameDescription)
{
	std::string stdSetEventNameDescription = toString(godotSetEventNameDescription);
	std::string stdEventInstancePath = toString(godotEventInstancePath);
	const char *EventInstancePath = stdEventInstancePath.c_str();

	/* Set eventDescription */
	FMOD::Studio::EventDescription *eventDescription = NULL;
	system->getEvent(EventInstancePath, &eventDescription);

	/* Set eventInfo */
	eventInfo event;
	event._eventNameDescription = stdSetEventNameDescription;
	event._eventDescription = eventDescription;

	/* Set Store */
	eventInfoList.push_back(event);
}
void setFMOD::createEventInstance(String godotEventNameDescription)
{
	std::string stdEventNameDescription = toString(godotEventNameDescription);
	int index = findIndex(eventInfoList, stdEventNameDescription);
	
	/* Set eventInfo */
	eventInfo event;
	event = eventInfoList.at(index);
		
	/* Get eventDescription*/
	FMOD::Studio::EventDescription *eventDescription;
	eventDescription = event._eventDescription;

	/* Set eventInstance*/
	FMOD::Studio::EventInstance *eventInstance = NULL;
	eventDescription->createInstance(&eventInstance);

	/* Set Store */
	event._eventInstance = eventInstance;
	eventInfoList.at(index) = event;
}
void setFMOD::start(String godotEventNameDescription)
{
	std::string stdEventNameDescription = toString(godotEventNameDescription);
	int index = findIndex(eventInfoList, stdEventNameDescription);

	/* Set eventInfo */
	eventInfo event;
	event = eventInfoList.at(index);

	/* Get eventInstance*/
	FMOD::Studio::EventInstance *eventInstance;
	eventInstance = event._eventInstance;

	eventInstance->start();
}
void setFMOD::release(String godotEventNameDescription)
{
	std::string stdEventNameDescription = toString(godotEventNameDescription);
	int index = findIndex(eventInfoList, stdEventNameDescription);

	/* Set eventInfo */
	eventInfo event;
	event = eventInfoList.at(index);

	/* Get eventInstance*/
	FMOD::Studio::EventInstance *eventInstance;
	eventInstance = event._eventInstance;

	eventInstance->release();
}
void setFMOD::setBanks(String godotBankList)
{
	std::string rawBankList = toString(godotBankList);
	std::vector<std::string> bankList = setBankList(rawBankList);

	for (std::string strNameBank : bankList)
	{
		const char *Bank = strNameBank.c_str();
		setNameBank(Bank);
	}

}
void setFMOD::setBanksPath(String godotBanksPath)
{
	stdBanksPath = toString(godotBanksPath);
}

int setFMOD::findIndex(std::vector<eventInfo> list, std::string name)
{
	std::vector<eventInfo>::iterator it = std::find_if(list.begin(), list.end(), [&name](const eventInfo &iteratedEvent) { return iteratedEvent._eventNameDescription == name; } );
	int index = std::distance(list.begin(), it);
	return index;
}

const char *setFMOD::Path(const char *fileName)
{
	const char *banksPath = stdBanksPath.c_str();
	char *filePath = (char *)calloc(256, sizeof(char));
	strcat(filePath, banksPath);
	strcat(filePath, fileName);

	return filePath;
}
const char *setFMOD::toConstChar(String godotString)
{
	std::string str = "";
	int length = godotString.length();

	for (int i = 0; i < length; i += 1)
	{
		str += godotString[i];
	}

	const char *chr = str.c_str();
	return chr;
}

std::string setFMOD::toString(String godotString)
{
	std::string str = "";
	int length = godotString.length();

	for (int i = 0; i < length; i += 1)
	{
		str += godotString[i];
	}

	return str;
}
std::vector<std::string> setFMOD::setBankList(std::string rawBankList)
{
	std::string collectBank = "";
	std::string delimiters = "; ,:";
	std::vector<std::string> vecBankList;

	for (int i = 0; i < rawBankList.size(); i += 1)
	{
		if (delimiters.find(rawBankList[i]) == -1)
		{
			collectBank = collectBank + rawBankList[i];
		}
		else
		{
			if (!collectBank.empty())
			{
				vecBankList.push_back(collectBank);
				collectBank.clear();
			}
		}
	}
	vecBankList.push_back(collectBank);

	return vecBankList;
}

void setFMOD::setParameterValue(String godotEventNameDescription, String godotParameterName, float parameterValue)
{
	std::string eventNameDescription = toString(godotEventNameDescription);
	std::string stdParameterName = toString(godotParameterName);
	const char *parameterName = stdParameterName.c_str();
	int index = findIndex(eventInfoList, eventNameDescription);

	eventInfo event;
	event = eventInfoList.at(index);

	/* Get eventInstance*/
	FMOD::Studio::EventInstance *eventInstance;
	eventInstance = event._eventInstance;

	eventInstance->setParameterValue(parameterName, parameterValue);
}

setFMOD::setFMOD() {}

void setFMOD::_bind_methods()
{
	/* FMOD Basic System */
	ClassDB::bind_method(D_METHOD("setSystem"), &setFMOD::setSystem);
	ClassDB::bind_method(D_METHOD("setLowLevelSystem"), &setFMOD::setLowLevelSystem);
	ClassDB::bind_method(D_METHOD("setSoftwareFormat"), &setFMOD::setSoftwareFormat);
	ClassDB::bind_method(D_METHOD("setInitialize"), &setFMOD::setInitialize);
	ClassDB::bind_method(D_METHOD("setMasterBank"), &setFMOD::setMasterBank);
	ClassDB::bind_method(D_METHOD("setStringBank"), &setFMOD::setStringBank);
	ClassDB::bind_method(D_METHOD("setBanks", "bankList"), &setFMOD::setBanks);
	ClassDB::bind_method(D_METHOD("setBanksPath", "Path"), &setFMOD::setBanksPath);
	ClassDB::bind_method(D_METHOD("createEventDescription", "EventInstancePath", "setEventNameDescription"), &setFMOD::createEventDescription);
	ClassDB::bind_method(D_METHOD("createEventInstance", "eventNameDescription"), &setFMOD::createEventInstance);
	ClassDB::bind_method(D_METHOD("start", "eventNameDescription"), &setFMOD::start);
	ClassDB::bind_method(D_METHOD("release", "nameEvent"), &setFMOD::release);
	ClassDB::bind_method(D_METHOD("setSystemUpdate"), &setFMOD::setSystemUpdate);
	ClassDB::bind_method(D_METHOD("setSystemRelease"), &setFMOD::setSystemRelease);
	ClassDB::bind_method(D_METHOD("unsetBanks"), &setFMOD::unsetBanks);
	ClassDB::bind_method(D_METHOD("unsetStringsBank"), &setFMOD::unsetStringsBank);
	ClassDB::bind_method(D_METHOD("unsetMasterBank"), &setFMOD::unsetMasterBank);
	/* FMOD Parameter System */
	ClassDB::bind_method(D_METHOD("setParameterValue", "eventNameDescription", "parameterName", "parameterValue"), &setFMOD::setParameterValue);
}