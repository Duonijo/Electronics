#include <SparkFunMiniMoto.h>   // Include the MiniMoto library

// Create two MiniMoto instances, with different address settings.
MiniMoto motorG(0xC0); // moteur gauche
MiniMoto motorD(0xD0); // moteur droit

int CaptCG=A3, CaptMG=A2, CaptMD=A1, CaptCD=A0;
char LedCG=11, LedMG=10, LedMD=9, LedCD=8;
char PresenceCG=5, PresenceMG=6, PresenceMD=13, PresenceCD=12;
int mini=1023,maxi=0,moy;
int ValCaptCG, ValCaptMG, ValCaptMD, ValCaptCD;
int MG=50; //Moteur roue gauche
int MD=-50; //Moteur roue droite
void setup()
{
  //Capteurs
  pinMode(CaptCG,INPUT);
  pinMode(CaptMG,INPUT);
  pinMode(CaptMD,INPUT);
  pinMode(CaptCD,INPUT);
  //Leds Capteurs
  pinMode(LedCG,OUTPUT);
  pinMode(LedMG,OUTPUT);
  pinMode(LedMD,OUTPUT);
  pinMode(LedCD,OUTPUT);
  //Leds Présence
  pinMode(PresenceCG,OUTPUT);
  pinMode(PresenceMG,OUTPUT);
  pinMode(PresenceMD,OUTPUT);
  pinMode(PresenceCD,OUTPUT);

  Serial.begin(9600);
}

void loop()
{
  digitalWrite(LedCG,HIGH);
  digitalWrite(LedMG,HIGH);
  digitalWrite(LedMD,HIGH);
  digitalWrite(LedCD,HIGH);

  //Capteur Coté Gauche
  ValCaptCG=analogRead(CaptCG);
  moy=(mini+maxi)/2;
  if(ValCaptCG<mini){
    mini=ValCaptCG;
  }
  if(ValCaptCG>maxi){
    maxi=ValCaptCG;
  }
  if(ValCaptCG>moy) {
    digitalWrite(PresenceCG,HIGH);
  }
  else{
    digitalWrite(PresenceCG,LOW);
  }

  //Capteur Milieu Gauche
  ValCaptMG=analogRead(CaptMG);
  moy=(mini+maxi)/2;
  if(ValCaptMG<mini){
    mini=ValCaptMG;
  }
  if(ValCaptMG>maxi){
    maxi=ValCaptMG;
  }
  if(ValCaptMG>moy) {
    digitalWrite(PresenceMG,HIGH);
  }
  else{
    digitalWrite(PresenceMG,LOW);
  }

  //Capteur Milieu Droit
  ValCaptMD=analogRead(CaptMD);
  moy=(mini+maxi)/2;
  if(ValCaptMD<mini){
    mini=ValCaptMD;
  }
  if(ValCaptMD>maxi){
    maxi=ValCaptMD;
  }
  if(ValCaptMD>moy) {
    digitalWrite(PresenceMD,HIGH);
  }
  else{
    digitalWrite(PresenceMD,LOW);
  }

  //Capteur Coté Droit
  ValCaptCD=analogRead(CaptCD);
  moy=(mini+maxi)/2;
  if(ValCaptCD<mini){
    mini=ValCaptCD;
  }
  if(ValCaptCD>maxi){
    maxi=ValCaptCD;
  }
  if(ValCaptCD>moy) {
    digitalWrite(PresenceCD,HIGH);
  }
  else{
    digitalWrite(PresenceCD,LOW);
  }

  //Moteurs
  if((ValCaptMG>moy)&&(ValCaptMD>moy)){             //Condition ligne droite
    MD=-48;
    MG=48;
  }
  else if((ValCaptCG>moy)&&(ValCaptMG>moy)){       //Condition virage à gauche
    MD=-58;
    MG=20;
  }
  else if((ValCaptCD>moy)&&(ValCaptMD>moy)){      //Condition virage à droite
    MD=-20;
    MG=58;
  }
  else if((ValCaptCG>moy)&&(ValCaptMG<moy)){    //Correction trajectoire droite
    MD=-47;
    MG=0;
  }
    else if((ValCaptCG>moy)&&(ValCaptMG<moy)){  //Correction trajectoire gauche
    MD=0;
    MG=47;
  }
  motorD.drive(MD);
  motorG.drive(MG);
}
