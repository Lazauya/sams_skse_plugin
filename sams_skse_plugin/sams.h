#ifndef samsh
#define samsh

#include <vector>
#include <string>
#include <unordered_map>
#include <utility>

#include "skse/PapyrusVM.h"
#include "skse/PapyrusNativeFunctions.h"

#include "skse/ScaleformCallbacks.h"
#include "skse/Serialization.h"

namespace sams
{
	typedef std::pair<UInt32, UInt32> Counter;
	typedef std::tuple < std::string, std::string, UInt32, Counter > Achievement;
	typedef std::unordered_map < std::string, Achievement > AchievementMap;

	//generic functions
	bool InitializeAchievements();
	bool IncrementAchievement(std::string id, UInt32 amt);
	bool DecrementAchievement(std::string id, UInt32 amt);
	bool AddAchievement(std::string id, std::string name, std::string desc, UInt32 type, UInt32 max, UInt32 cur);
	bool RemoveAchievement(std::string id);
	bool AddAchievementsFromFile(std::string path);
	Counter GetAchievementCounter(std::string id);
	Achievement GetAchievement(std::string id);

	//serialization callbacks
	void Save(SKSESerializationInterface * intfc);
	void Load(SKSESerializationInterface * intfc);
	void Revert(SKSESerializationInterface * intfc);

	bool RegisterPapyrusFunctions(VMClassRegistry* registry);
	bool RegisterScaleformFunctions(GFxMovieView * view, GFxValue * root);
	bool RegisterSerializationCallbacks(SKSESerializationInterface * intfc, PluginHandle handle);
}

#endif samsh