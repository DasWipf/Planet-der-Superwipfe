/*-- Superwipf --*/

#strict 2
#include HZCK

func ContextSpezialisieren(object pCaller)
{
	[Spezialisieren|Image=WIPF]
	if(GetID(pCaller)!=SPWF)
	{
		PlayerMessage(GetController(pCaller),"Dein Wipf kann nicht weiter spezialisiert werden!", pCaller);
		return(1);
	}
	CreateMenu(SPWF,pCaller,pCaller,0,"Spezialisieren",0,1);
	AddMenuItem("Kampfwipf", "Change", KAWF, pCaller);
	AddMenuItem("Speedwipf", "Change", SDWF, pCaller);
	return(1);
}

func Change(id wipf)
{
	var clk = CreateObject(wipf, 0, 10,GetOwner());
	MakeCrewMember(clk,GetOwner());
	SetCursor(GetOwner(), clk);
	RemoveObject();
	return(1);
}


public func ControlSpecial(object pCaller)
{
	return(1);
}

