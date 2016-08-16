#strict
#include _SWE

local mat;

func OnActivate(){
	mat=Material("Water");
	ScheduleCall(this, "Rain", RandomX(5, 10), 0);
}

func OnDeActivate(){
	ClearScheduleCall(this, "Rain");
}

func Rain(){
  var vx = GetWind(0, 3) / 10, vy = 150 - Min(GetMaterialVal("WindDrift", "Material", mat), 100)*3/2;
  InsertMaterial(mat, Random(LandscapeWidth()), 0, vx, vy);
  ScheduleCall(this, "Rain", RandomX(5, 10), 0);
}

func GetStatChange(){
	return [["Walk", 1000*80/100], ["Jump", 1000*80/100]];
}

public func GetStatChangeMessage(){
	return "Wir sind alle nass! Bäh!";
}
