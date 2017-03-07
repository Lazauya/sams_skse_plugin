#include "pap.h"

namespace sams
{
	bool PapIncrementAchievement(StaticFunctionTag * base, BSFixedString id, UInt32 amt)
	{
		return IncrementAchievement(std::string(id.data), amt);
	}

	bool PapDecrementAchievement(StaticFunctionTag * base, BSFixedString id, UInt32 amt)
	{
		return DecrementAchievement(std::string(id.data), amt);
	}

	bool PapAddAchievement(StaticFunctionTag * base, BSFixedString id, BSFixedString name, BSFixedString desc, UInt32 type, UInt32 max, UInt32 cur)
	{
		return AddAchievement(std::string(id.data), std::string(name.data), std::string(desc.data), type, max, cur);
	}

	bool PapRemoveAchievement(StaticFunctionTag * base, BSFixedString id)
	{
		return RemoveAchievement(std::string(id.data));
	}

	bool PapAddAchievementsFromFile(StaticFunctionTag * base, BSFixedString path)
	{
		return AddAchievementsFromFile(std::string(path.data));
	}

	UInt32 PapGetAchievementProgress(StaticFunctionTag * base, BSFixedString id)
	{
		return GetAchievementCounter(std::string(id.data)).second;
	}

	UInt32 PapGetAchievementMaximum(StaticFunctionTag * base, BSFixedString id)
	{
		return GetAchievementCounter(std::string(id.data)).first;
	}
}