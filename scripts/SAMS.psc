ScriptName SAMS hidden

Bool Function AddAchievement(String id, String name, String description, Int type, Int counterMax, Int counterCurrent) global native
Bool Function AddAchievementsFromFile(String path) global native
Bool Function RemoveAchievement(String id) global native
Bool Function IncrementAchievement(String id, Int amount) global native
Bool Function DecrementAchievement(String id, Int amount) global native
Bool Function GetAchievementProgress(String id) global native
Bool Function GetAchievementMaximum(String id) global native 