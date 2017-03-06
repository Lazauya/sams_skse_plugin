#include "sams.h"

#include "skse/GameTypes.h"

namespace sams
{
	//papyrus functions
	//bool InitializeAchievements();
	bool PapIncrementAchievement(StaticFunctionTag * base, BSFixedString id, UInt32 amt);
	bool PapDecrementAchievement(StaticFunctionTag * base, BSFixedString id, UInt32 amt);
	bool PapAddAchievement(StaticFunctionTag * base, BSFixedString id, BSFixedString name, BSFixedString desc, UInt32 type, UInt32 max, UInt32 cur);
	bool PapRemoveAchievement(StaticFunctionTag * base, BSFixedString id);
	bool PapAddAchievementsFromFile(StaticFunctionTag * base, BSFixedString path);

	UInt32 PapGetAchievementProgress(StaticFunctionTag * base, BSFixedString id);
	UInt32 PapGetAchievementMaximum(StaticFunctionTag * base, BSFixedString id);
}