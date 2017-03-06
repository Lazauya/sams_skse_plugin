#include "sams.h"

#include "skse/Serialization.h"
namespace sams
{
	void SerializeCPPString(SKSESerializationInterface * intfc, std::string str);
	template<typename T1, typename T2>
	void SerializeBasicPair(SKSESerializationInterface * intfc, std::pair<T1, T2> p);
	void SerializeAchievement(SKSESerializationInterface * intfc, Achievement ach);
	void SerializeAchievementMap(SKSESerializationInterface * intfc, AchievementMap * achmap);

	std::string UnserializeCPPString(SKSESerializationInterface * intfc);
	template<typename T1, typename T2>
	std::pair<T1, T2> UnserializeBasicPair(SKSESerializationInterface * intfc);
	Achievement UnserializeAchievement(SKSESerializationInterface * intfc);
	AchievementMap UnserializeAchievementMap(SKSESerializationInterface * intfc);

	void sSave(SKSESerializationInterface * intfc, AchievementMap * map, bool isInit);
	void sLoad(SKSESerializationInterface * intfc, AchievementMap *& map, bool & isInit);
	void sRevert(SKSESerializationInterface * intfc, AchievementMap *& map, bool & isInit);
}