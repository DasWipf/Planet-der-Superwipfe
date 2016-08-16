/*-- Meteor --*/

#strict

protected func SmokeTrail() {
  Smoke(0, 0, 2);
  Smoke(0, -5, Random(3));
  var i = Random(20);
  while (i--) {
    var c = (20+Random(41))/2;
    CreateParticle("PxSpark", Random(11)-5, Random(11)-5, 0, 0, c,
      RGBa(255, Random(100), c*4, 128));
  }
  CreateParticle("PxSpark", 0, 0, 0, 0, 20,
    RGBa(255, 155, 0, 128));
  //Bitte hier Schaden für Wipfe setzen
  //*99/100 = Grenzwertig stark, *98/100=Meistens 0 Schaden
  SetYDir(GetYDir(this, 1000)*982/1000, this, 1000);
}

public func Initialize() {
  SetAction("Evaporate");
  
}

protected func Hit(){
	BlastFree(GetX(), GetY(), 5, NO_OWNER);
	Explode(2+Random(1));
}

public func EnvironmentSelectionAmount(){return (3);}
