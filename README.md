# zvehhealth
Vehicle on change health callback

# Provides callbacks
```Pawn
forward OnVehicleHealthChanged(vehicleid, Float:oldhealth, Float:newhealth, bool:scriptcall);
```
**scriptcall = true** if vehicle health changed by SetVehicleHealth or RepairVehicle functions.
