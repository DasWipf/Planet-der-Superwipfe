//Hier Menüs und so rein (für Auswahl)

#strict

func Initialize(){
	ScheduleCall(this, "MakeMenu", 30, 0, 0);
	return(1);
}

func MakeMenu(iPlr){
	var cursor=GetCursor(iPlr);
	CreateMenu(GetID(), cursor, this, C4MN_Extra_Info, "Wetterauswahl", 0, C4MN_Style_Normal, true);
	CreateMenuItems(cursor);
}

func CreateMenuItems(target){
	for(var obj in FindObjects(Find_Func("Is_SuperWipfEnvEffect"))){
	   AddMenuItem(GetName(obj), "ToggleEnvEffect", GetID(obj), target, obj->IsActivated(), target, "asd");
   }
}

protected func ToggleEnvEffect(id objid, target){
	var obj=FindObject(objid);
	if(!obj->IsActivated())
		obj->Activate();
	else
		obj->DeActivate();
	ClearMenuItems(target);
	CreateMenuItems(target);
	return (1);
}
