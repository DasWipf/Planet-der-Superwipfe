/*-- Wipf --*/

#strict
//Nix da mit Ficken
//#include ANIM

local Bait; // Verfolgter Köder

local lorry_wipf; // Speichert das zugehörige Lorenwipf-Objekt

local PowerJump_Vel;
local PowerJump_Ready;

local ActionMenu_Obj;

public func IsPossessible() { return(1); }

/* Initialisierung */

public func InitVars(){
	PowerJump_Vel=7000;
}

protected func Initialize() {
	InitVars();
	PowerJump_Ready=true;
  SetAction("Walk");
  SetComDir(COMD_None());
	ActionMenu_Obj=CreateObject(SWAM);
}

/* TimerCall mit KI-Steuerung */

protected func Activity()
{
  // Geräusche machen
  if(!Random(15)) Sound("Snuff*");
	return (0);
	
	return (0);

  // Die KI-Steuerung wird bei Besessenheit nicht gebraucht
  if(GetEffect("PossessionSpell", this())) return(0);

  // Köder markiert?
  if(Bait) {
    // Bereits im Inventar?
    if(Contained(Bait)) Bait = 0;
    // Zu weit entfernt?
    if(ObjectDistance(Bait, this()) > 300) Bait = 0;
    // In Reichweite?
    if(ObjectDistance(Bait, this()) <= 15)
      // Aufessen!
      if(GetAction() == "Walk") {
        SetAction("Eat");
        SetXDir();
      }
  }

  var pObj, aList;
  // Nur wenn der Wipf ausgewachsen ist
  if(GetCon() == 100)
    // Soll nicht zu einfach sein...
    if(!Random(5)) {
      // Ein Köder in der Nähe?
      aList = FindObjects(Find_Distance(250),Find_NoContainer(),Find_Func("IsBait"));
      for(pObj in aList) {
        // Köder?
        if(!WildcardMatch(GetAction(pObj),"*MeatBait*")) continue;
        // Je nach Köderqualität...
        if(Random(100) >= pObj->~IsBait()) continue;
        // ... hinrennen
        SetCommand(this(), "Follow", pObj);
        // Und Köder merken
        Bait = pObj;
      }
    }

  // Graben, aber keine Richtung? Dann wieder laufen
  if(GetAction() eq "Dig" && GetComDir() == COMD_None())
    SetAction("Walk");

  // Die folgenden Aktionen nur im Freien
  if(Contained()) return(0);

  // Die folgenden Aktionen nur im Gehen oder Schwimmen
  if(GetAction() ne "Walk" && GetAction() ne "Swim") return(0);

  // Auftauchen, wenn der Atem ausgeht
  if(InLiquid() && GetBreath() <= 25 && GetComDir() != COMD_Up())
    SetComDir(COMD_Up());

  // Brennenden Objekten ausweichen
  if(pObj = FindObject(0,-!GetDir()*80,-30,80,35,OCF_OnFire())) {
    if(!Random(5) || !SpaceToFlee(pObj)) {
      if(GetDir()) SetComDir(COMD_Right());
      else SetComDir(COMD_Left());
      Jump();
    }
    else {
      if(GetComDir() == COMD_Left()) SetComDir(COMD_Right());
      else SetComDir(COMD_Left());
    }
  }

  // Nichts machen
  if(Random(2)) return(0);

  // Freigraben, falls er feststeckt
  if(Stuck()) return(DigFree());

  // Fortpflanzung
  //Keine Sodomie hier!
  //if(!Random(ReproductionRate())) 
  //  Reproduction();

  if(GetAction() eq "Walk") {
    // Springen
    if(!Random(3)) return(Jump());
    // Hinsetzen
    if(!Random(3)) return(SetAction("Sit"));
    // Graben
    if(!Random(25))
      // "In der Prärie wird nicht gegraben" - nicht buddeln bei aktiviertem Westernpack (arg!)
      if(!GetName(0, COWB))
        return(StartDig());
  }

  // Umdrehen
  if(Random(2)) return(TurnRight());
  return(TurnLeft());
}

private func SpaceToFlee(pFromObj)
{
 var x=-100;
 if (GetX() > GetX(pFromObj)) x=100;

 // Am Rand der Landschaft eingesperrt
 if (!Inside(x+GetX(), 0, LandscapeWidth())) return();

 // Am Rand einer Höhle eingesperrt
 if (!PathFree(GetX(),GetY(),GetX()+x,GetY())) return();

 return(1);
}

private func StartDig()
{
  SetAction("Dig");
  //SetComDir(2 + Random(7));
  if (GetComDir() == COMD_Down()) SetComDir(COMD_Stop());
  return(1);
}

private func DigSound()
{
  // Die KI-Steuerung wird bei Besessenheit nicht gebraucht
  if (GetEffect("PossessionSpell", this())) return();

  if (!Random(10)) StartDig();
  return(1);
}

private func Sitting()
{
  // Die KI-Steuerung wird bei Besessenheit nicht gebraucht
  if (GetEffect("PossessionSpell", this())) return();
  
  /*// Weiterlaufen
  if (!Random(10)) SetAction("Walk");*/
  return(1);
}

/* Kontakt */

/*protected func ContactLeft()
{
  // Die KI-Steuerung wird bei Besessenheit nicht gebraucht
  if (GetEffect("PossessionSpell", this())) return();
  return(TurnRight());
}

protected func ContactRight()
{
  // Die KI-Steuerung wird bei Besessenheit nicht gebraucht
  if (GetEffect("PossessionSpell", this())) return();
  
  return(TurnLeft());
}*/

private func CanTurn(){
	return !Stuck() && (GetAction()S="Walk" || GetAction()S="Swim" || GetAction()S="Sit" || InAir());
}

private func InAir(){
	return GetAction()S="Jump";
}

/* Aktionen */

public func TurnRight()
{
  if (!CanTurn()) return();
  //Vllt weg damit, dient halt der Stabilisierung auf dem Boden und so
  if (GetXDir() < 0 && !InAir()) SetXDir(0);
  SetDir(DIR_Right());
  SetComDir(COMD_Right());
  if (GetAction() eq "Sit") SetAction("Walk");
  return(1);
}

public func TurnLeft()
{
  if (!CanTurn()) return();
  if (GetXDir() > 0 && !InAir()) SetXDir(0);
  SetDir(DIR_Left());
  SetComDir(COMD_Left()); 
  if (GetAction() eq "Sit") SetAction("Walk");
  return(1);
}

private func DigFree()
{
  SetAction("DigFree");
  SetComDir(3+GetDir()*4);
  return(1);
}

/* Einwirkungen */

protected func CatchBlow()
{
  if (GetAction() eq "Dead") return(0);
  if (!Random(3)) Sound("WipfHurt");
  return(1);
}

protected func Death() 
{
  Sound("WipfDead");
  SetDir(0);
  LeftLorry();
  ChangeDef(DWPF);
  SetAction("Dead");
  return(1);
}

public func Entrance(obj) 
{
  // Ist in eine Lore gegangen?
  if (obj->~IsLorry())
  {
    // Lorenwipf suchen, der zu der Lore gehört
    lorry_wipf = FindObject(LWPF, 0,0,0,0, 0,0, obj);

    // Lorenwipf gefunden?
    if (lorry_wipf) 
    {
      // Benachrichtigen, dass wir jetzt in der Lore sind
      lorry_wipf->IncreaseCount();
    }
    // Keinen Lorenwipf gefunden?
    else 
    {
      // Erzeugen wir halt einen
      lorry_wipf = CreateObject(LWPF, 0,0, -1);

      // An die Lore kleben
      lorry_wipf->AttachTo(obj);
    }
  }
}

protected func Departure(obj) { LeftLorry(); }
protected func Destruction()  { LeftLorry(); }

protected func LeftLorry() 
{
  // Lorenwipfobjekt informieren
  if (lorry_wipf) lorry_wipf->DecreaseCount();
  lorry_wipf = 0;
}

/* Vermehrung */

//private func ReproductionRate() { return(1000); } // Die Chance, dass in einem Timerintervall eine Vermehrung stattfindet

/* Anti-Sofort-Wieder einsammeln */

public func RejectEntrance(object pNewCont, a,b,c) 
{
  // nur einsammeln lassen wenn er nicht springt
  if (GetAction() S= "Jump") return(1);
  // Spezial: Einsammeln OK bei aktivierter Wipfjagd
  if (ObjectCount(WPHT)) return();
  // ansonsten nach Tiersteuerung
  return (_inherited(pNewCont, a,b,c));
}

/* Steuerung durch Besessenheit */

protected func RejectCollect(c4ID, pObject)
{
 var iEffectNumber, pSorcerer;
 if (iEffectNumber = GetEffect("PossessionSpell", this()))
  if (pSorcerer = EffectVar(0, this(), iEffectNumber))
   if (!GetEffect("IntCollectionDelay", this()))
    if (!pSorcerer->Contents())
     if (!(pObject->GetOCF() & OCF_Living()))
      Collect(pObject, pSorcerer);
 return(1);
}

/* Steuerung durch Besessenheit */

protected func ControlCommand(szCommand, pTarget, iTx, iTy)
{
 // Bewegungskommando
 if (szCommand eq "MoveTo" || szCommand eq "Dig")
  return(SetCommand(this(),szCommand, pTarget, iTx, iTy));
 return(0);
}

protected func ControlLeft(){
	if(GetAction()S="Jump"){
		TurnLeft();
		return (1);
	}
	return (0);
}

protected func ControlRight(){
	if(GetAction()S="Jump"){
		TurnRight();
		return (1);
	}
	return (0);
}

protected func ControlLeftDouble(){
	SetComDir(COMD_Left());
	SetDir(DIR_Left());
	return (PowerJump(180));
}

protected func ControlRightDouble(){
	SetComDir(COMD_Right());
	SetDir(DIR_Right());
	return (PowerJump(0));
}

protected func ControlUpDouble(){
	return (PowerJump(-90));
}

protected func ControlDownDouble(){
	return (PowerJump(90, true));
}

protected func ControlSpecial(){
	ActionMenu_Obj->SWAM::Set_Up(this());
	return (1);
}

public func PowerJump(angle, override){
	if(!PowerJump_Ready)
		return (0);
	SetXDir(Cos(angle, PowerJump_Vel)+GetXDir(this, 1000)*(!override), this, 1000);
	SetYDir(Sin(angle, PowerJump_Vel)+GetYDir(this, 1000)*(!override), this, 1000);
	PowerJump_Ready=false;
	return (1);
}

protected func ContactBottom(){
	PowerJump_Ready=true;
}

public func ActionMenuCommand(key){
	if(key S= "LEFT" || key S= "RIGHT"){
		if((key S= "LEFT") == (GetDir()==DIR_Left())){
			SetAction("Bite");
		}
		else
		{
			SetAction("Kick");
		}
	}
	else
	if(key S= "DIG"){
		Message("*Furz*", this());
	}
	else
	if(key S= "THROW"){
		Message("*Rülps*", this());
	}
	else
	Message("*Irgendwas anderes*", this());
}

/*
protected func ContainedLeft(object caller)
{
  [$TxtMovement$]
  SetCommand(this(), "None");
  if(!GetPlrJumpAndRunControl(caller->GetController()))
  {
    if(GetAction() eq "Dig")
    {
      if (GetComDir()+1 <= 8) SetComDir(GetComDir()+1);
    }
    else
    {
      TurnLeft();
    }
  }
  return(1);
}

protected func ContainedRight(object caller)
{
  [$TxtMovement$]
  SetCommand(this(), "None");
  if(!GetPlrJumpAndRunControl(caller->GetController()))
  {
    if(GetAction() eq "Dig")
    {
      if(GetComDir()-1 >= 2) SetComDir(GetComDir()-1);
    }
    else
    {
      TurnRight();
    }
  }

  return(1);
}

protected func ContainedUp(object caller)
{
 [$TxtMovement$]
 SetCommand(this(), "None");

 if (GetAction() eq "Swim")
 {
  if(!GetPlrJumpAndRunControl(caller->GetController()))
   SetComDir(COMD_Up());

  return(1);
 }

 Jump();
 return(1);
}

protected func ContainedDown(object caller)
{
 [$TxtMovement$]
 SetCommand(this(), "None");
 if(Contained()) SetCommand(this, "Exit");
 if (GetAction() eq "Swim")
 {
  if(!GetPlrJumpAndRunControl(caller->GetController()))
   SetComDir(COMD_Down());
  return(1);
 }

 // Nicht waehrend des Grabens, weil man sonst bei JumpAndRun-Steuerung
 // nicht nach unten graben kann.
 if (GetAction() eq "Walk")
  SetAction("Sit");

 if(!GetPlrJumpAndRunControl(caller->GetController()) && GetAction() eq "Dig")
  SetAction("Sit");

 return(1);
}*/

/* JumpAndRun Steuerung */

private func ClearDir(bool fX)
{
  if(fX && GetXDir())
  {
    if(GetXDir() > 0) SetXDir(Max(GetXDir() - 2, 0));
    else SetXDir(Min(GetXDir() + 2, 0));
  }
  if(!fX && GetYDir())
  {
    if(GetYDir() > 0) SetYDir(Max(GetYDir() - 2, 0));
    else SetYDir(Min(GetYDir() + 2, 0));
  }
}

public func ContainedUpdate(object self, int comdir, bool dig, bool throw)
{
  if(GetAction() S= "Swim")
  {
    SetComDir(comdir);
    ClearScheduleCall(this(), "ClearDir");
    if(comdir == COMD_Down || comdir == COMD_Up) ScheduleCall(this(), "ClearDir", 1, (Abs(GetXDir())+1)/2, true);
    if(comdir == COMD_Left || comdir == COMD_Right) ScheduleCall(this(), "ClearDir", 1, (Abs(GetYDir())+1)/2, false);
  }
  else if(GetAction() S= "Dig")
  {
    if(comdir == COMD_Stop && dig) return();
    SetComDir(comdir);
  }
  else
  {
    if(comdir == COMD_UpRight || comdir == COMD_DownRight) comdir = COMD_Right;
    if(comdir == COMD_Up || comdir == COMD_Down) comdir = COMD_Stop;
    if(comdir == COMD_UpLeft || comdir == COMD_DownLeft) comdir = COMD_Left;

    if(comdir == COMD_Right) TurnRight();
    else if(comdir == COMD_Left) TurnLeft();
    else SetComDir(comdir);
  }

  return(1);
}

/*

protected func ControlCommand(szCommand, pTarget, iTx, iTy)
{
 // Bewegungs- oder Grabkommando
 if (szCommand eq "MoveTo" || szCommand eq "Dig")
  return(SetCommand(this(),szCommand, pTarget, iTx, iTy));
 return(0);
}

protected func ContainedLeft()
{
 [$TxtMovement$]
 SetCommand(this(), "None");

 if (GetAction() eq "Dig")
 {
  if (GetComDir()+1 <= 8) SetComDir(GetComDir()+1);
  return(1);
 }

 TurnLeft();
 return(1);
}

protected func ContainedRight()
{
 [$TxtMovement$]
 SetCommand(this(), "None");

 if (GetAction() eq "Dig")
 {
  if (GetComDir()-1 >= 2) SetComDir(GetComDir()-1);
  return(1);
 }

 TurnRight();
 return(1);
}

protected func ContainedUp()
{
 [$TxtMovement$]
 SetCommand(this(), "None");

 if (GetAction() eq "Swim")
  return(SetComDir(COMD_Up()));

 Jump();
 return(1);
}

protected func ContainedDown()
{
 [$TxtMovement$]
 SetCommand(this(), "None");

 if (GetAction() eq "Swim")
  return(SetComDir(COMD_Down()));

 if (GetAction() eq "Walk" || GetAction() eq "Dig")
  SetAction("Sit");
  
 return(1);
}*/

protected func ContainedThrow()
{
 [$TxtDrop$]
 var iEffectNumber, pSorcerer;
 if (iEffectNumber = GetEffect("PossessionSpell", this()))
  if (pSorcerer = EffectVar(0, this(), iEffectNumber))
  {
   if (pSorcerer->Contents()) pSorcerer->Contents()->Exit(0,0,6);
   AddEffect("IntCollectionDelay", this(), 1, 70);
  }
 return(1);
}

protected func ContainedDig()
{
 [$TxtDig$]
 if (GetAction() eq "Walk" || GetAction() eq "Sit")
 {
  SetComDir(4 + !GetDir()*2);
  SetAction("Dig");
 }
 return(1);
}

protected func ContainedDigDouble()
{
 [$TxtLeave$]
 RemoveEffect("PossessionSpell", this());
 return(1);
}


/* Köder fressen */

protected func Eating()
{
  // Köder weg
  if(!Bait) return();
  // Köder fressen
  RemoveObject(Bait);
  // Schmeckt gut
  Sound("Snuff*");
}


protected func Kick_Call(){
	Message("*Kick*", this());
	var target=FindObject2(Find_Distance(10), Find_OCF(OCF_CrewMember), Find_Hostile(GetOwner()));
	if(target){
		DoEnergy(-20, target);
		var xdelta=GetX(target)-GetX();
		var ydelta=GetY(target)-GetY();
		var sqrln=xdelta*xdelta+ydelta*ydelta;
		sqrln*=1000000;
		sqrln=Sqrt(sqrln);
		SetXDir(xdelta*1000000/sqrln, target, 1000);
		SetYDir(ydelta*1000000/sqrln, target, 1000);
	}
}

protected func Bite_Call(){
	Message("*Beiß*", this());
	var target=FindObject2(Find_Distance(10), Find_OCF(OCF_CrewMember), Find_Hostile(GetOwner()));
	if(target)
		DoEnergy(-50, target);
}
