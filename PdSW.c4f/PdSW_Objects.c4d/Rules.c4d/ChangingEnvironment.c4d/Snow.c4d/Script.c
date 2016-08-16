#strict
#include _SWE

local mat;

func OnActivate(){
	mat=Material("Snow");
	ScheduleCall(this, "Snow", RandomX(5, 10), 0);
}

func OnDeActivate(){
	ClearScheduleCall(this, "Snow");
}

func Snow(){
  var vx = GetWind(0, 3) / 10, vy = 150 - Min(GetMaterialVal("WindDrift", "Material", mat), 100)*3/2;
  InsertMaterial(mat, Random(LandscapeWidth()), 0, vx, vy);
  ScheduleCall(this, "Snow", RandomX(5, 10), 0);
}

func GetStatChange(){
	return [["Walk", 1000*50/100], ["Jump", 1000*50/100], ["Fight", 1000*50/100]];
}

public func GetStatChangeMessage(){
	return "Es schneit! Alle bewegen sich 50% langsamer, kriegen aber 50% weniger Schaden ab!";
}
