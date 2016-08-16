#strict

func Initialize(){
	return(1);
}

func Show(menu, vertex_index){
	SetOwner(GetOwner(menu));
	SetVisibility(VIS_Owner());
	SetAction("Show", menu);
	SetActionData(256*0+vertex_index);
	SetDir(GetDir(menu));
}

func Hide(){
	SetAction("Hide");
	SetVisibility(VIS_None());
}
