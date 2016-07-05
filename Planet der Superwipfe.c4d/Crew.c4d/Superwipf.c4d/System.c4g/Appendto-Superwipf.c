#strict 2
#appendto SPWF

func ContextSpezialisieren(object pCaller)
{
	[Spezialisieren|Image=SPWF]
	CreateMenu(SPWF,pCaller,pCaller,0,"Spezialisieren",0,1);
	AddMenuItem("Kampfwipf", "Change", KAWF, pCaller);
	AddMenuItem("Speedwipf", "Change", SPWF, pCaller);
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
