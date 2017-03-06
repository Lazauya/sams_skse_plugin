#ifndef ui
#define ui

#include "sams.h"
#include "skse/ScaleformMovie.h"

#include "skse/ScaleformCallbacks.h"
#include "skse/ScaleformExtendedData.h"

namespace sams
{
	//scaleform function objects
	/*class ScfInitializeAchievements : public GFxFunctionHandler
	{
		virtual void Invoke(Args * args);
	};*/
	class ScfIncrementAchievement : public GFxFunctionHandler
	{
		virtual void Invoke(Args * args);
	};
	class ScfDecrementAchievement : public GFxFunctionHandler
	{
		virtual void Invoke(Args * args);
	};
	class ScfAddAchievement : public GFxFunctionHandler
	{
		virtual void Invoke(Args * args);
	};
	class ScfRemoveAchievement : public GFxFunctionHandler
	{
		virtual void Invoke(Args * args);
	};
	class ScfAddAchievementsFromFile : public GFxFunctionHandler
	{
		virtual void Invoke(Args * args);
	};
	class ScfGetAchievementList : public GFxFunctionHandler
	{
		virtual void Invoke(Args * args);
	};
	class ScfGetAchievement : public GFxFunctionHandler
	{
		virtual void Invoke(Args * args);
	};
}

#endif