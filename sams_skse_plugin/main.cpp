#include "skse/PluginAPI.h"		// super
#include "skse/skse_version.h"	// What version of SKSE is running?
#include <shlobj.h>				// CSIDL_MYCODUMENTS

#include "sams.h"

static PluginHandle					g_pluginHandle = kPluginHandle_Invalid;
static SKSEPapyrusInterface         * g_papyrus = NULL;
       SKSEScaleformInterface		* g_scaleform = NULL;
static SKSESerializationInterface	* g_serialization = NULL;

extern "C"	{

	bool SKSEPlugin_Query(const SKSEInterface * skse, PluginInfo * info)	{	// Called by SKSE to learn about this plugin and check that it's safe to load it
		gLog.OpenRelative(CSIDL_MYDOCUMENTS, "\\My Games\\Skyrim\\SKSE\\sams.log");
		gLog.SetPrintLevel(IDebugLog::kLevel_Error);
		gLog.SetLogLevel(IDebugLog::kLevel_DebugMessage);

		_MESSAGE("SAMS");

		// populate info structure
		info->infoVersion =	PluginInfo::kInfoVersion;
		info->name =		"sams";
		info->version =		1;

		// store plugin handle so we can identify ourselves later
		g_pluginHandle = skse->GetPluginHandle();

		if(skse->isEditor)
		{
			_MESSAGE("loaded in editor, marking as incompatible");

			return false;
		}
		else if(skse->runtimeVersion != RUNTIME_VERSION_1_9_32_0)
		{
			_MESSAGE("unsupported runtime version %08X", skse->runtimeVersion);

			return false;
		}

		g_scaleform = (SKSEScaleformInterface *)skse->QueryInterface(kInterface_Scaleform);
		if (!g_scaleform)
		{
			_MESSAGE("couldn't get scaleform interface");

			return false;
		}

		if (g_scaleform->interfaceVersion < SKSEScaleformInterface::kInterfaceVersion)
		{
			_MESSAGE("scaleform interface too old (%d expected %d)", g_scaleform->interfaceVersion, SKSEScaleformInterface::kInterfaceVersion);

			return false;
		}

		g_serialization = (SKSESerializationInterface *)skse->QueryInterface(kInterface_Serialization);
		if (!g_serialization)
		{
			_MESSAGE("couldn't get serialization interface");

			return false;
		}

		if (g_serialization->version < SKSESerializationInterface::kVersion)
		{
			_MESSAGE("serialization interface too old (%d expected %d)", g_serialization->version, SKSESerializationInterface::kVersion);

			return false;
		}

		// ### do not do anything else in this callback
		// ### only fill out PluginInfo and return true/false

		// supported runtime version
		return true;
	}

	bool SKSEPlugin_Load(const SKSEInterface * skse)	{	// Called by SKSE to load this plugin
		_MESSAGE("SAMS loaded");

		g_papyrus = (SKSEPapyrusInterface *)skse->QueryInterface(kInterface_Papyrus);

		//Check if the function registration was a success...
		bool btest = g_papyrus->Register(sams::RegisterPapyrusFunctions);
		bool ctest = g_scaleform->Register("sams", sams::RegisterScaleformFunctions);
		bool dtest = sams::RegisterSerializationCallbacks(g_serialization, g_pluginHandle);

		if (btest && ctest && dtest) {
			_MESSAGE("Register Succeeded");
			if (sams::InitializeAchievements())
			{
				_MESSAGE("Map initialized");
			}
			else
			{
				_ERROR("Maps not intialized");
				return false;
			}
			
		}
		else
		{
			return false;
		}

		return true;
	}

};