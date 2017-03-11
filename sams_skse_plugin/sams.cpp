#include "sams.h"
#include "ui.h"
#include "pap.h"
#include "serialize.h"

#include "skse/PluginAPI.h"

#include <fstream>
#include <iostream>

namespace sams
{
	AchievementMap * globalAchievementMap;
	bool isInitialized = false;

	//generic functions
	bool InitializeAchievements()
	{
		if (!isInitialized)
		{
			globalAchievementMap = new AchievementMap();
			isInitialized = true;
		}

		if (!isInitialized)
		{
			return false;
		}

		return true;
	}

	bool IncrementAchievement(std::string id, UInt32 amt)
	{
		Counter * count = &(std::get<3>((*globalAchievementMap)[id]));
		if (count)
		{
			count->second = (count->second >= count->first) ? (count->first) : (count->second + amt);
			return true;
		}
		else
		{
			return false;
		}
	}

	bool DecrementAchievement(std::string id, UInt32 amt)
	{
		Counter * count = &(std::get<3>((*globalAchievementMap)[id]));
		if (count)
		{
			count->second = (count->second >= count->first) ? (count->first) : (count->second - amt);
			return true;
		}
		else
		{
			return false;
		}
	}

	bool AddAchievement(std::string id, std::string name, std::string desc, UInt32 type, UInt32 max, UInt32 cur)
	{
		if (globalAchievementMap->count(id))
		{
			return false;
		}

		//_MESSAGE("%s, %s, %s, %d, %d, %d", id.c_str(), name.c_str(), desc.c_str(), type, max, cur);

		globalAchievementMap->insert(std::pair<std::string, Achievement>(id, Achievement(name, desc, type, Counter(max, cur))));

		if (globalAchievementMap->count(id))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool RemoveAchievement(std::string id)
	{
		if (!(globalAchievementMap->count(id)))
		{
			return false;
		}

		globalAchievementMap->erase(id);

		if (globalAchievementMap->count(id))
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	bool AddAchievementsFromFile(std::string path)
	{
		std::ifstream infile(path);
	
		std::string outstring;

		if (infile.is_open())
		{
			while (std::getline(infile, outstring))
			{
				long int pos = outstring.find("\"id\"") + 6;
				std::string id = outstring.substr(pos, outstring.find("\"", pos) - pos);

				pos = outstring.find("\"name\"") + 8;
				std::string name = outstring.substr(pos, outstring.find("\"", pos) - pos);

				pos = outstring.find("\"description\"") + 15;
				std::string desc = outstring.substr(pos, outstring.find("\"", pos) - pos);

				pos = outstring.find("\"type\"") + 8;
				UInt32 type = std::stoi(outstring.substr(pos, outstring.find("\"", pos) - pos));

				pos = outstring.find("\"max\"") + 7;
				UInt32 max = std::stoi(outstring.substr(pos, outstring.find("\"", pos) - pos));

				pos = outstring.find("\"current\"") + 11;
				UInt32 current = std::stoi(outstring.substr(pos, outstring.find("\"", pos) - pos));

				AddAchievement(id, name, desc, type, max, current);

			}

			infile.close();
			return true;
		}
		else
		{
			return false;
		}
	}

	Counter GetAchievementCounter(std::string id)
	{
		return std::get<3>((*globalAchievementMap)[id]);
	}

	Achievement GetAchievement(std::string id)
	{
		return (*globalAchievementMap)[id];
	}

	//scaleform function thats needs interaction with global map 
	void ScfGetAchievementList::Invoke(Args * args)
	{
		ASSERT((args->numArgs == 1) && (args->args[0].GetType() == GFxValue::kType_Array));
		//ASSERT(args->numArgs == 0);

		GFxValue * outarray = &(args->args[0]);
		//args->movie->CreateArray(&outarray);

		for (auto it = globalAchievementMap->begin(); it != globalAchievementMap->end(); it++)
		{
			GFxValue entryElement;
			args->movie->CreateObject(&entryElement);

			RegisterString(&entryElement, args->movie, "id", it->first.c_str());
			RegisterString(&entryElement, args->movie, "name", std::get<0>(it->second).c_str());
			RegisterString(&entryElement, args->movie, "description", std::get<1>(it->second).c_str());
			RegisterNumber(&entryElement, "type", double(std::get<2>(it->second)));
			RegisterNumber(&entryElement, "max", double(std::get<3>(it->second).first));
			RegisterNumber(&entryElement, "current", double(std::get<3>(it->second).second));

			outarray->PushBack(&entryElement);
		}

		//_MESSAGE("_GEAL_got through the function");

		//args->movie->CreateArray(args->result);

		//args->result = &outarray; //it's not like i wanted this to work or anything, baka!

		//args->args[0] = outarray;
	}


	//serialization callbacks
	void Save(SKSESerializationInterface * intfc)
	{
		sSave(intfc, globalAchievementMap, isInitialized);
	}

	void Load(SKSESerializationInterface * intfc)
	{
		sLoad(intfc, globalAchievementMap, isInitialized);
	}

	void Revert(SKSESerializationInterface * intfc)
	{
		sRevert(intfc, globalAchievementMap, isInitialized);
	}

	bool RegisterPapyrusFunctions(VMClassRegistry* registry)
	{
		registry->RegisterFunction(new NativeFunction2<StaticFunctionTag, bool, BSFixedString, UInt32>("IncrementAchievement", "SAMS", sams::PapIncrementAchievement, registry));
		registry->RegisterFunction(new NativeFunction2<StaticFunctionTag, bool, BSFixedString, UInt32>("DecrementAchievement", "SAMS", sams::PapDecrementAchievement, registry));
		registry->RegisterFunction(new NativeFunction6<StaticFunctionTag, bool, BSFixedString, BSFixedString, BSFixedString, UInt32, UInt32, UInt32>("AddAchievement", "SAMS", sams::PapAddAchievement, registry));
		registry->RegisterFunction(new NativeFunction1<StaticFunctionTag, bool, BSFixedString>("RemoveAchievement", "SAMS", sams::PapRemoveAchievement, registry));
		registry->RegisterFunction(new NativeFunction1<StaticFunctionTag, bool, BSFixedString>("AddAchievementsFromFile", "SAMS", sams::PapAddAchievementsFromFile, registry));
		registry->RegisterFunction(new NativeFunction1<StaticFunctionTag, UInt32, BSFixedString>("GetAchievementProgress", "SAMS", sams::PapGetAchievementProgress, registry));
		registry->RegisterFunction(new NativeFunction1<StaticFunctionTag, UInt32, BSFixedString>("GetAchievementMaximum", "SAMS", sams::PapGetAchievementMaximum, registry));

		return true;
	}

	bool RegisterScaleformFunctions(GFxMovieView * view, GFxValue * root)
	{
		RegisterFunction <ScfIncrementAchievement>(root, view, "IncrementAchievement");
		RegisterFunction <ScfDecrementAchievement>(root, view, "DecrementAchievement");
		RegisterFunction <ScfAddAchievement>(root, view, "AddAchievement");
		RegisterFunction <ScfRemoveAchievement>(root, view, "RemoveAchievement");
		RegisterFunction <ScfAddAchievementsFromFile>(root, view, "AddAchievementsFromFile");
		RegisterFunction <ScfGetAchievementList>(root, view, "GetAchievementList");
		RegisterFunction <ScfGetAchievement>(root, view, "GetAchievement");

		return true;
	}

	bool RegisterSerializationCallbacks(SKSESerializationInterface * intfc, PluginHandle handle)
	{
		intfc->SetUniqueID(handle, 'SAMS');
		intfc->SetRevertCallback(handle, Revert);
		intfc->SetSaveCallback(handle, Save);
		intfc->SetLoadCallback(handle, Load);
		return true;
	}
}