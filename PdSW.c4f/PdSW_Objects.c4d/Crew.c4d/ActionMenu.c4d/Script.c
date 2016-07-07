#strict

local Controlled_Wipf;
local Menu_Slots;

func Initialize(){
	Controlled_Wipf=0;
	Menu_Slots=[["UP", 0, 0], ["LEFT", 0, 1], ["DOWN", 0, 2], ["RIGHT", 0, 3], ["CENTER", 0, 4]];
	Hide();
	return(1);
}

private func Get_Slot_Index(pos){
	var l=GetLength(Menu_Slots);
	for(var i=0; i<l; i++){
		if(Menu_Slots[i][0] S= pos){
			return (i);
		}
	}
	return (-1);
}

public func Set_Up(wipf, objects){
	Controlled_Wipf=wipf;
	SetOwner(GetOwner(wipf));
	SetVisibility(VIS_Owner());
	//SetPosition(GetX(wipf), GetY(wipf));
	SetCursor(GetOwner(wipf), this(), true, true);
	SetAction("Show", wipf);
	SetActionData(256*0+5);
	SetDir(GetDir(wipf));
	if(GetDir()!=DIR_Right()){
		var l=GetLength(Menu_Slots);
		for(var i=0; i<l; i++){
			if(Menu_Slots[i][0] S= "LEFT"){
				Menu_Slots[i][2]=3;
			}
			else if(Menu_Slots[i][0] S= "RIGHT")
				Menu_Slots[i][2]=1;
		}
	}
	else{
		var l=GetLength(Menu_Slots);
		for(var i=0; i<l; i++){
			if(Menu_Slots[i][0] S= "LEFT")
				Menu_Slots[i][2]=1;
			else if(Menu_Slots[i][0] S= "RIGHT")
				Menu_Slots[i][2]=3;
		}
	}
	var l=GetLength(objects);
	for(var i=0; i<l; i++)
		SetUp_Obj(objects[i][1], objects[i][0]);
}

public func SetUp_Obj(obj_id, pos){
	var slot_index=Get_Slot_Index(pos);
	if(slot_index==-1){
		Message("Fehler: Ungültiger Aktionsmenüslot %s für %i", this(), pos, obj_id);
		return (0);
	}
	var obj=CreateObject(obj_id, 0, 0, GetOwner(this()));
	Menu_Slots[slot_index][1]=obj;
	obj->Show(this(), Menu_Slots[slot_index][2]);
}

protected func ControlLeft(){
	return Send_WipfCommand("LEFT");
}

protected func ControlRight(){
	return Send_WipfCommand("RIGHT");
}

protected func ControlDown(){
	return Send_WipfCommand("DOWN");
}

protected func ControlUp(){
	return Send_WipfCommand("UP");
}

protected func ControlThrow(){
	return Send_WipfCommand("CENTRE");
}

protected func ControlDig(){
	return Send_WipfCommand("DIG");
}

private func Hide(){
	SetVisibility(VIS_None());
	SetAction("Hide");
	var l=GetLength(Menu_Slots);
	for(var i=0; i<l; i++){
		if(Menu_Slots[i][1]){
			RemoveObject(Menu_Slots[i][1]);
			Menu_Slots[i][1]=0;
		}
	}
}

func Send_WipfCommand(key){
	if(GetDir()!=DIR_Right()){
		if(key=="LEFT")
			key="RIGHT";
		else
		if(key=="RIGHT")
			key="LEFT";
	}
	var slot_index=Get_Slot_Index(key);
	if(slot_index==-1){
		Message("Fehler: Ungültiger Aktionsmenüslot %s", this(), key);
	}
	Controlled_Wipf->SWIP::ActionMenuCommand(GetID(Menu_Slots[slot_index][1]));
	SetCursor(GetOwner(Controlled_Wipf), Controlled_Wipf, true, true);
	Hide();
}
