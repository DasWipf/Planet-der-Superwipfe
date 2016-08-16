#strict

local Controlled_Wipf;

func Initialize(){
	Controlled_Wipf=0;
	Hide();
	return(1);
}

public func Set_Up(wipf){
	Controlled_Wipf=wipf;
	SetOwner(GetOwner(wipf));
	SetVisibility(VIS_Owner());
	SetPosition(GetX(wipf), GetY(wipf));
	SetCursor(GetOwner(wipf), this(), true, true);
	SetAction("Show", wipf);
	SetActionData(256*0+5);
	SetDir(GetDir(wipf));
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
	return Send_WipfCommand("THROW");
}

protected func ControlDig(){
	return Send_WipfCommand("DIG");
}

private func Hide(){
	SetVisibility(VIS_None());
	SetAction("Hide");
}

func Send_WipfCommand(key){
	Controlled_Wipf->SWIP::ActionMenuCommand(key);
	SetCursor(GetOwner(Controlled_Wipf), Controlled_Wipf, true, true);
	Hide();
}
