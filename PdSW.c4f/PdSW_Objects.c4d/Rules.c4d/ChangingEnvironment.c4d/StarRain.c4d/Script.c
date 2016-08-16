#strict
#include _SWE

public func OnActivate(){
	ScheduleCall(this, "Rain_Stars", RandomX(5, 30), 0);
}

public func OnDeActivate(){
	ClearScheduleCall(this, "Rain_Stars");
}

func Rain_Stars(){
	var meteor=CreateObject(_SWM, Random(LandscapeWidth()), -100, NO_OWNER);
	SetXDir(RandomX(-1000, 1000), meteor, 1000);
	//SetYDir(RandomX(1000, 10000), meteor, 100000);
	ScheduleCall(this, "Rain_Stars", RandomX(5, 30), 0);
}

public func GetStatChangeMessage(){
	return "Es regnet Sterne! Sucht einen Unterstand!";
}
