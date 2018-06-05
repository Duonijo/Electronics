
#include <U8glib.h>
U8GLIB_KS0108_128 u8g(4, 5, 6, 7, 8, 9, 10, 11, 12, 3, 2, 13, 0);

#include <Wire.h>;
 // adresse I2C du nunchuck
#define WII_NUNCHUK_I2C_ADDRESS 0x52

// définition d'une variable counter
uint8_t counter;
 
// définition d'un tableau de données
uint8_t data[6];
int n = 0;
uint8_t bp;

//Lancement ecran jeu
boolean gameStart=false;

//Tableaux
const int nbCol = 25;
const int nbLigne = 20;
char tabEcran[nbCol][nbLigne];
uint8_t SX = data[0];
uint8_t SY = data[1];
int lig, col;
int x = 5;
int y=3;

//SNAKE 
int corpsLig = y;
int corpsCol = x - 1;
int queueLig = corpsLig;
int queueCol = corpsCol - 1;

//Score
int score=0;

//Pomme
 const unsigned int coordXPomme = 15;
  const unsigned int coordYPomme = 10;


unsigned char positionPomme[coordXPomme][coordYPomme];

void setup() {
 
  u8g.begin();
 
 
  Serial.begin(9600);
  // initialisation du nunchuck
  Wire.begin();
  Wire.beginTransmission(WII_NUNCHUK_I2C_ADDRESS);
  Wire.write(0xF0);
  Wire.write(0x55);
  Wire.endTransmission();
 
  Wire.beginTransmission(WII_NUNCHUK_I2C_ADDRESS);
  Wire.write(0xFB);
  Wire.write(0x00);
  Wire.endTransmission();
}
 
/*-----------------------------------------------
Fonctions ecrans
-----------------------------------------------*/
void requeteWii()
{
  // on demande 6 octets au nunchuck
  Wire.requestFrom(WII_NUNCHUK_I2C_ADDRESS, 6);
  counter = 0;  // tant qu’il y a des données
  while(Wire.available()) {
  // on récupère les données
  data[counter++] = Wire.read();
  }
 
  // on réinitialise le nunchuck pour la prochaine demande
  Wire.beginTransmission(WII_NUNCHUK_I2C_ADDRESS);
  Wire.write(0x00);
  Wire.endTransmission();
 
  if(counter >= 5){
   
  //BOUTON Z
  bp= data[5] & 0b00000001;
  if ( bp == 0 )
  {
    Serial.println("Bouton z enfonce");
  
  } else {
    Serial.println("Bouton z relache");
  }
    
  /*BOUTON C
  uint8_t bp= data[5] & 0b00000010;
  if ( bp == 0 )
  {
    Serial.println("Bouton c enfonce");
  } else {
    Serial.println("Bouton c relache");
  }*/
    
  uint8_t SX = data[0];
  uint8_t SY = data[1];
  Serial.print("SX = ");
  Serial.print(SX);
  Serial.print(" : SY = ");
  Serial.println(SY);
   
   }
   // un petit delai  pour pas saturer la liaison série.
   delay(1000);
}


void menuSnake()
{
   
    u8g.setFont(u8g_font_gdr11);
    u8g.drawStr(20, 14, "Snake Game");
    //Clignotement de "Appuyez sur Z"
    if ( n <=2)
    {
      u8g.setFont(u8g_font_gdr9);
      u8g.drawStr(25, 50, "Appuyez sur Z");
    } else if (n == 4)
      {
          n = -1;
    }
        n++;
}


void gameSnake()
{
    tabEcran[x][y]=1;
    deplacement();
    mangerPomme();
    

    u8g.setFont(u8g_font_gdr11);
    u8g.drawStr(20, 14, "Score :" + score);

    
    for(col = 0; col<nbCol;col=col++)
    {
      for(lig = 0; lig<nbLigne; lig++)
      {
        if (tabEcran[col][lig]==1)
        {
          u8g.drawBox(col,lig,5,5); // tête
          u8g.drawBox(corpsCol,corpsLig,5,5);// 2e partie corps
          u8g.drawBox(queueCol,queueLig,5,5);//queue
          }
        }
     }
}
 void deplacement()
 {
   //Déplacement HAUT
   if(SY>=170){
       queueCol = corpsCol;
       queueLig = corpsLig;
       corpsCol = col;
       corpsLig = lig;
       
       tabEcran[x][y]=0;
       
       y=y+1;//tête
       
     }   
   //Déplacement BAS    
   if(SY<=80){
       queueCol = corpsCol;
       queueLig = corpsLig;
       corpsCol = col;
       corpsLig = lig;
       
       tabEcran[x][y]=0;
       y=y-1;//tête
     }
   //Déplacement DROITE
   if(SX>=170){
       queueCol = corpsCol;
       queueLig = corpsLig;
       corpsCol = col;
       corpsLig = lig;
       
       tabEcran[x][y]=0;
       x=x+1;//tête
     }
    //Déplacement GAUCHE
    if(SX<=80){
       queueCol = corpsCol;
       queueLig = corpsLig;
       corpsCol = col;
       corpsLig = lig;
       
       tabEcran[x][y]=0;
       x=x-1;//tête
     }
        
   }

   void mangerPomme ()
   {
    int i,j;
    if (tabEcran[x][y] == positionPomme[coordXPomme][coordYPomme])
    {
      score = score + 1;
      for(i = 0; i<=20; i++)
      {
        for(j = 0; j<=20; j++)
        {
          positionPomme[i][j];
        }
        
      }

     
      
    }
   }
/*-----------------------------------------------
Boucle Principale
-----------------------------------------------*/


void loop() {
 
  
   requeteWii();

  
/*-----------------------------------------------
Gestion Pages
-----------------------------------------------*/

   u8g.firstPage();
   do
   {

   if ( (gameStart == false) && (bp == 1) )
   {
     menuSnake();
   }
    else if ( (gameStart == true)||(bp == 0) )
   {
     gameSnake();
     gameStart = true;
     
   }
      } while( u8g.nextPage() );
}


