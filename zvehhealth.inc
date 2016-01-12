/*

	About: vehicle health changed callback
	Author: ziggi

*/

#if !defined _samp_included
	#error "Please include a_samp or a_npc before zvehhealth"
#endif

#if !defined foreach
	#error "Please include foreach before zvehhealth"
#endif

/*
	Defines
*/

#if !defined ZVEHHEALTH_TICKRATE
	#define ZVEHHEALTH_TICKRATE 300
#endif

forward OnVehicleHealthChanged(vehicleid, Float:oldhealth, Float:newhealth, bool:scriptcall);

/*
	Vars
*/

static
	gPlayerVehicleID[MAX_PLAYERS] = {INVALID_VEHICLE_ID, ...},
	Float:gOldHealth[MAX_VEHICLES] = {1000.0, ...},
	Iterator:OccupiedVehicle<MAX_VEHICLES>;


/*
	OnGameModeInit
*/

public OnGameModeInit()
{
	SetTimer("OccupiedVehicleTimer", ZVEHHEALTH_TICKRATE, 1);

	#if defined VHealth_OnGameModeInit
		return VHealth_OnGameModeInit();
	#else
		return 1;
	#endif
}
#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
 
#define OnGameModeInit VHealth_OnGameModeInit
#if defined VHealth_OnGameModeInit
	forward VHealth_OnGameModeInit();
#endif

/*
	OnPlayerStateChange
*/

public OnPlayerStateChange(playerid, newstate, oldstate)
{
	if (newstate == PLAYER_STATE_DRIVER) {
		gPlayerVehicleID[playerid] = GetPlayerVehicleID(playerid);
		Iter_Add(OccupiedVehicle, gPlayerVehicleID[playerid]);
	}

	if (oldstate == PLAYER_STATE_DRIVER && gPlayerVehicleID[playerid] != INVALID_VEHICLE_ID) {
		Iter_Remove(OccupiedVehicle, gPlayerVehicleID[playerid]);
		gPlayerVehicleID[playerid] = INVALID_VEHICLE_ID;
	}

	#if defined VHealth_OnPlayerStateChange
		return VHealth_OnPlayerStateChange(playerid, newstate, oldstate);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerStateChange
	#undef OnPlayerStateChange
#else
	#define _ALS_OnPlayerStateChange
#endif
 
#define OnPlayerStateChange VHealth_OnPlayerStateChange
#if defined VHealth_OnPlayerStateChange
	forward VHealth_OnPlayerStateChange(playerid, newstate, oldstate);
#endif

/*
	OnPlayerDisconnect
*/

public OnPlayerDisconnect(playerid, reason)
{
	if (gPlayerVehicleID[playerid] != INVALID_VEHICLE_ID) {
		Iter_Remove(OccupiedVehicle, gPlayerVehicleID[playerid]);
		gPlayerVehicleID[playerid] = INVALID_VEHICLE_ID;
	}

	#if defined VHealth_OnPlayerDisconnect
		return VHealth_OnPlayerDisconnect(playerid, reason);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif
 
#define OnPlayerDisconnect VHealth_OnPlayerDisconnect
#if defined VHealth_OnPlayerDisconnect
	forward VHealth_OnPlayerDisconnect(playerid, reason);
#endif

/*
	SetVehicleHealth
*/

stock VHealth_SetVehicleHealth(vehicleid, Float:health)
{
	new ret = SetVehicleHealth(vehicleid, health);
	
	if (ret == 1) {
		CallHealthCallback(vehicleid, gOldHealth[vehicleid], health, true);
	}
	
	return ret;
}
#if defined _ALS_SetVehicleHealth
	#undef SetVehicleHealth
#else
	#define _ALS_SetVehicleHealth
#endif
 
#define SetVehicleHealth VHealth_SetVehicleHealth

/*
	RepairVehicle
*/

stock VHealth_RepairVehicle(vehicleid)
{
	new ret = RepairVehicle(vehicleid);
	
	if (ret == 1) {
		CallHealthCallback(vehicleid, gOldHealth[vehicleid], 1000.0, true);
	}

	return ret;
}
#if defined _ALS_RepairVehicle
	#undef RepairVehicle
#else
	#define _ALS_RepairVehicle
#endif
 
#define RepairVehicle VHealth_RepairVehicle

/*
	OccupiedVehicleTimer
*/

forward OccupiedVehicleTimer();
public OccupiedVehicleTimer()
{
	static
		Float:new_health;

	foreach (new vehicleid : OccupiedVehicle) {
		GetVehicleHealth(vehicleid, new_health);

		CallHealthCallback(vehicleid, gOldHealth[vehicleid], new_health, false);
	}
}

/*
	Private functions
*/

static stock CallHealthCallback(vehicleid, &Float:oldhealth, Float:newhealth, bool:scriptcall)
{
	if (newhealth != oldhealth) {
		CallLocalFunction("OnVehicleHealthChanged", "iffi", vehicleid, oldhealth, newhealth, _:scriptcall);
		oldhealth = newhealth;
	}
}
