ScriptName SAMS hidden

Bool Function AddAchievement(String id, String name, String description, Int type, Int counterMax, Int counterCurrent) native
Bool Function AddAchievementsFromFile(String path) native
Bool Function RemoveAchievement(String id) global native
Bool Function IncrementAchievement(String id, Int amount) native
Bool Function DecrementAchievement(String id, Int amount) native
Bool Function GetAchievementProgress(String id) native
Bool Function GetAchievementMaximum(String id) native 