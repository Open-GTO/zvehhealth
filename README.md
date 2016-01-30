# zvehhealth
Vehicle on change health callback

# Provides callbacks
```Pawn
forward OnVehicleHealthChanged(vehicleid, Float:oldhealth, Float:newhealth, bool:scriptcall);
```
**scriptcall = true** if vehicle health changed by SetVehicleHealth or RepairVehicle functions.

# Provides constants
```Pawn
ZVEHHEALTH_TICKRATE 300
```

# Usage
```Pawn
public OnVehicleHealthChanged(vehicleid, Float:oldhealth, Float:newhealth, bool:scriptcall)
{
	if (scriptcall) {
		printf("Vehicle health has been changed (SetVehicleHealth, RepairVehicle).");
	} else {
		printf("Vehicle health has been changed (crashed).");
	}

	printf("Vehicleid: %d. Old: %f, new: %f.", vehicleid, oldhealth, newhealth);
}
```
