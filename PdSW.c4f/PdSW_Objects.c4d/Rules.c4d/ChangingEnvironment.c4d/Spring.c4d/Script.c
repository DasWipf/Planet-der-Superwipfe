#strict
#include _SWE

func OnActivate(){
	ScheduleCall(this, "Grow", RandomX(30, 40), 0);
	ScheduleCall(this, "GrowHeal", 60, 0);
}

func OnDeActivate(){
	ClearScheduleCall(this, "Grow");
	ClearScheduleCall(this, "GrowHeal");
}

func GrowHeal(){
	for(var wipf in FindObjects(Find_Func("IsSuperWipf"))){
		//Am fairsten ist es, alle gleich zu heilen, da OP Panzer mit 100000000000 HP einen unfairen Vorteil beim Heilen hätten
		var max_energy=GetPhysical("Energy", 0, wipf);
		//DoEnergy(Min(GetEnergy(wipf)*100/max_energy, GetEnergy(wipf)10/max_energy), wipf);
		if(GetEnergy(wipf)<max_energy/1000)
			DoEnergy(1, wipf);
	}
	ScheduleCall(this, "GrowHeal", 60, 0);
}

func Grow(){
	var xpos=Random(LandscapeWidth());
	var objids=[GRAS, SWD1, SWD2];
	var objid=objids[Random(GetLength(objids))];
	CreateObject(objid, xpos, 0, NO_OWNER); 
	ScheduleCall(this, "Grow", RandomX(30, 40), 0);
}

public func GetStatChangeMessage(){
	return "Es ist Frühling! Alle Einheiten regenerieren etwas Energie!";
}
