#include "pap.h"

namespace sams
{
	bool PapIncrementAchievement(StaticFunctionTag * base, BSFixedString id, UInt32 amt)
	{
		return IncrementAchievement(id.data, amt);
	}

	bool PapDecrementAchievement(StaticFunctionTag * base, BSFixedString id, UInt32 amt)
	{
		return DecrementAchievement(id.data, amt);
	}

	bool PapAddAchievement(StaticFunctionTag * base, BSFixedString id, BSFixedString name, BSFixedString desc, UInt32 type, UInt32 max, UInt32 cur)
	{
		return AddAchievement(id.data, name.data, desc.data, type, max, cur);
	}

	bool PapRemoveAchievement(StaticFunctionTag * base, BSFixedString id)
	{
		return RemoveAchievement(id.data);
	}

	bool PapAddAchievementsFromFile(StaticFunctionTag * base, BSFixedString path)
	{
		return AddAchievementsFromFile(path.data);
	}

	UInt32 PapGetAchievementProgress(StaticFunctionTag * base, BSFixedString id)
	{
		return GetAchievementCounter(id.data).second;
	}

	UInt32 PapGetAchievementMaximum(StaticFunctionTag * base, BSFixedString id)
	{
		return GetAchievementCounter(id.data).first;
	}
}