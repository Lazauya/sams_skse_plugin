#include "serialize.h"

namespace sams
{
	const UInt32 SerializationVersion = 0;
	enum
	{
		kTypeAchievementMap,
		kTypeInitialized
	};

	void SerializeCPPString(SKSESerializationInterface * intfc, std::string str)
	{
		const char * tstr = str.c_str();
		UInt32 len = str.length();

		intfc->WriteRecordData(&len, sizeof(UInt32));
		for (UInt32 i = 0; i < len; i++)
		{
			intfc->WriteRecordData(&(tstr[0]), sizeof(char));
		}
	}

	template<typename T1, typename T2>
	void SerializeBasicPair(SKSESerializationInterface * intfc, std::pair<T1, T2> p)
	{
		intfc->WriteRecordData(&(p.first), sizeof(T1));
		intfc->WriteRecordData(&(p.second), sizeof(T2));
	}

	void SerializeAchievement(SKSESerializationInterface * intfc, Achievement ach)
	{
		//SerializeCPPString(intfc, id); //id
		SerializeCPPString(intfc, std::get<0>(ach)); //name
		SerializeCPPString(intfc, std::get<1>(ach)); //desc
		
		intfc->WriteRecordData(&(std::get<2>(ach)), sizeof(UInt32));
		SerializeBasicPair<UInt32, UInt32>(intfc, std::get<3>(ach));
	}

	void SerializeAchievementMap(SKSESerializationInterface * intfc, AchievementMap * achmap)
	{
		intfc->OpenRecord(kTypeAchievementMap, SerializationVersion);

		std::size_t ms = achmap->size();
		intfc->WriteRecordData(&ms, sizeof(std::size_t));

		for (auto it = achmap->begin(); it != achmap->end(); it++)
		{
			SerializeCPPString(intfc, it->first);
			SerializeAchievement(intfc,  it->second);
		}
	}

	std::string UnserializeCPPString(SKSESerializationInterface * intfc)
	{
		UInt32 len;
		intfc->ReadRecordData(&len, sizeof(UInt32));

		std::string outstring;
		for (UInt32 i = 0; i < len; i++)
		{
			char curchar;
			intfc->ReadRecordData(&curchar, sizeof(UInt32));
			outstring.append(&curchar);
		}

		return outstring;
	}

	template<typename T1, typename T2>
	std::pair<T1, T2> UnserializeBasicPair(SKSESerializationInterface * intfc)
	{
		T1 t1;
		T2 t2;
		intfc->ReadRecordData(&t1, sizeof(T1));
		intfc->ReadRecordData(&t2, sizeof(T2));
		
		return std::pair<T1, T2>(t1, t2);
	}

	Achievement UnserializeAchievement(SKSESerializationInterface * intfc)
	{
		std::string name, description;
		UInt32 type;
		Counter counter;

		name = UnserializeCPPString(intfc);
		description = UnserializeCPPString(intfc);
		intfc->ReadRecordData(&type, sizeof(UInt32));
		counter = UnserializeBasicPair<UInt32, UInt32>(intfc);

		return Achievement(name, description, type, counter);
	}

	AchievementMap UnserializeAchievementMap(SKSESerializationInterface * intfc)
	{
		UInt32 ms;
		intfc->ReadRecordData(&ms, sizeof(UInt32));

		AchievementMap outmap;

		for (UInt32 i = 0; i < ms; i++)
		{
			std::string id = UnserializeCPPString(intfc);
			Achievement ach = UnserializeAchievement(intfc);
			outmap.insert(std::pair<std::string, Achievement>(id, ach));
		}

		return outmap;
	}

	void sSave(SKSESerializationInterface * intfc, AchievementMap * map, bool isInit)
	{
		intfc->OpenRecord(kTypeInitialized, SerializationVersion);
		intfc->WriteRecordData(&isInit, sizeof(bool));

		SerializeAchievementMap(intfc, map);
	}

	void sLoad(SKSESerializationInterface * intfc, AchievementMap *& map, bool & isInit)
	{
		UInt32 type, ver, len;
		while (intfc->GetNextRecordInfo(&type, &ver, &len))
		{
			switch (type)
			{
			case kTypeAchievementMap:
				(*map) = UnserializeAchievementMap(intfc);
				break;
			case kTypeInitialized:
				intfc->ReadRecordData(&isInit, sizeof(bool));
				break;
			}
		}
	}
	
	void sRevert(SKSESerializationInterface * intfc, AchievementMap *& map, bool & isInit)
	{
		sLoad(intfc, map, isInit);
	}
}