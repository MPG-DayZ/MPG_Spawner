////////////////////////////////////////////////////////////////////
//DeRap: config.bin
//Produced from mikero's Dos Tools Dll version 9.89
//https://mikero.bytex.digital/Downloads
//'now' is Sun Apr 27 14:49:57 2025 : 'file' last modified on Sun Apr 27 14:49:57 2025
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class MPG_Spawner
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data","DZ_Scripts"};
	};
};
class CfgMods
{
	class MPG_Spawner
	{
		dir = "MPG_Spawner";
		picture = "";
		action = "";
		hideName = 1;
		hidePicture = 1;
		name = "MPG_Spawner";
		credits = "Hunterz";
		author = "pafnuty";
		authorID = "76561198022444951";
		version = "1.3";
		extra = 0;
		type = "mod";
		dependencies[] = {"Game","World","Mission"};
		class defs
		{
			class gameScriptModule
			{
				value = "";
				files[] = {"MPG_spawn_zone/Scripts/Common","MPG_Spawner/Scripts/3_Game"};
			};
			class worldScriptModule
			{
				value = "";
				files[] = {"MPG_spawn_zone/Scripts/Common","MPG_Spawner/Scripts/4_World"};
			};
			class missionScriptModule
			{
				value = "";
				files[] = {"MPG_spawn_zone/Scripts/Common","MPG_Spawner/Scripts/5_Mission"};
			};
		};
	};
};
