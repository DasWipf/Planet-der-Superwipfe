//Bitte diese Wettereffekt-API nutzen!

#strict

local Activated;
local EffectStrength;

func Initialize(){
	Activated=false;
	EffectStrength=0;
	var obj;
	while(obj=FindObject(GetID())){
		RemoveObject(obj);
		EffectStrength++;
	}
	if(!FindObject(SWCE))
		Activate();
	return(1);
}

public func Activate(){
	Activated=true;
	OnActivate();
	StartEffects();
	Message(GetStatChangeMessage(), 0);
}

protected func OnActivate(){
}

public func DeActivate(){
	Activated=false;
	OnDeActivate();
	StopEffects();
}

protected func OnDeActivate(){
}

protected func StartEffects(){
	for(var stat in GetStatChange()){
		for(var obj in FindObjects(Find_Func("IsSuperWipf"))){
			obj->ApplyStatChange(stat);
		}
	}
}

protected func StopEffects(){
	for(var stat in GetStatChange()){
		for(var obj in FindObjects(Find_Func("IsSuperWipf"))){
			obj->UnApplyStatChange(stat);
		}
	}
}

public func IsActivated(){return Activated;}
public func Is_SuperWipfEnvEffect(){return true;}

public func GetStatChange(){return [];}
public func GetStatChangeMessage(){return "";}
