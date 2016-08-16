#strict
#include SWIP

public func InitVars(){
	PowerJump_Vel=5000;
	ActionMenu_Entries=[["LEFT", SAMK, "Kick"], ["RIGHT", SAMB, "Bite"], ["UP", SAMH, "Headsmash"]];
}


protected func Headsmash_Call(){
	Message("*Kopfstoß*", this());
	var target=FindObject2(Find_Distance(10), Find_OCF(OCF_CrewMember), Find_Hostile(GetOwner()));
	if(target){
		DoEnergy(-GetAttackDamage(50, target), target);
		var xdelta=GetX(target)-GetX();
		var ydelta=GetY(target)-GetY();
		var sqrln=xdelta*xdelta+ydelta*ydelta;
		sqrln*=1000000;
		sqrln=Sqrt(sqrln);
		SetXDir(xdelta*10000/sqrln, target, 1000);
		SetYDir(ydelta*10000/sqrln-5000, target, 1000);
	}
}
