#include "ui.h"

namespace sams
{
	void ScfIncrementAchievement::Invoke(Args * args)
	{
		ASSERT((args->args[0].GetType() == GFxValue::kType_String) && (args->args[1].GetType() == GFxValue::kType_Number) && (args->numArgs == 2));

		bool out = IncrementAchievement(args->args[0].GetString(), UInt32(args->args[1].GetNumber()));

		args->result->SetBool(out);
	}

	void ScfDecrementAchievement::Invoke(Args * args)
	{
		ASSERT((args->args[0].GetType() == GFxValue::kType_String) && (args->args[1].GetType() == GFxValue::kType_Number) && (args->numArgs == 2));

		bool out = DecrementAchievement(args->args[0].GetString(), UInt32(args->args[1].GetNumber()));

		args->result->SetBool(out);
	}

	void ScfAddAchievement::Invoke(Args * args)
	{
		ASSERT((args->args[0].GetType() == GFxValue::kType_String) && (args->args[1].GetType() == GFxValue::kType_String) && (args->args[2].GetType() == GFxValue::kType_String) && (args->args[3].GetType() == GFxValue::kType_Number) && (args->args[4].GetType() == GFxValue::kType_Number) && (args->args[5].GetType() == GFxValue::kType_Number) && (args->numArgs == 6));

		bool out = AddAchievement(args->args[0].GetString(), args->args[1].GetString(), args->args[2].GetString(), UInt32(args->args[3].GetNumber()), UInt32(args->args[4].GetNumber()), UInt32(args->args[5].GetNumber()));

		args->result->SetBool(out);
	}

	void ScfRemoveAchievement::Invoke(Args * args)
	{
		ASSERT((args->args[0].GetType() == GFxValue::kType_String) && (args->numArgs == 1));

		bool out = RemoveAchievement(args->args[0].GetString());

		args->result->SetBool(out);
	}

	void ScfAddAchievementsFromFile::Invoke(Args * args)
	{
		ASSERT((args->args[0].GetType() == GFxValue::kType_String) && (args->numArgs == 1));

		bool out = AddAchievementsFromFile(args->args[0].GetString());

		args->result->SetBool(out);
	}

	/*void ScfGetAchievementList::Invoke(Args * args)
	{
		ASSERT(args->numArgs == 0);

		for (auto it = globalAchievementMap->begin(); )
	}*/

	void ScfGetAchievement::Invoke(Args * args)
	{
		ASSERT((args->args[0].GetType() == GFxValue::kType_String) && (args->args[1].GetType() == GFxValue::kType_Object) && (args->numArgs == 2));

		GFxValue * entryElement = &(args->args[1]);
		//args->movie->CreateObject(&entryElement);

		Achievement foundach = GetAchievement(args->args[0].GetString());

		RegisterString(entryElement, args->movie, "id", args->args[0].GetString());
		RegisterString(entryElement, args->movie, "name", std::get<0>(foundach).c_str());
		RegisterString(entryElement, args->movie, "description", std::get<1>(foundach).c_str());
		RegisterNumber(entryElement, "type", double(std::get<2>(foundach)));
		RegisterNumber(entryElement, "max", double(std::get<3>(foundach).first));
		RegisterNumber(entryElement, "current", double(std::get<3>(foundach).second));

		//args->result = &entryElement;
	}
}