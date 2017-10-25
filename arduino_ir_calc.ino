#include "TM1650.h"
#include "IRSendRev.h"
TM1650 disp(2,3);//U2 KEBZ U1 0,1
  int cislo;
  int cislo_1;
  int cislo_2;
  int vysledok;
//////////////////////////////////////////////////////
/////////////7seg display/////////////////////////////
int sedemseg[12]=
{
 0b00111111,  // = 0
 0b00000110,  // = 1
 0b01011011,  // = 2
 0b01001111,  // = 3
 0b01100110,  // = 4
 0b01101101,  // = 5
 0b01111101,  // = 6
 0b00000111,  // = 7
 0b01111111,  // = 8
 0b01100111,   // = 9
 0b01111001,   // = E
 0b01010000   // = r
};
///////////////////////////////////////
////////////////////////////////////
void cele_cisla(int cislo)
{
  int d;
  if(cislo>9999){
    disp.display(1,sedemseg[10]);
    disp.display(2,sedemseg[11]);
    disp.display(3,sedemseg[11]);
  }
  else
  {
    d=cislo/1000;
    if (d==0)
    {
      disp.display(0,0b00000000);
    }
    else
    {
      disp.display(0,sedemseg[d]);
    }
    d=cislo/100;
    d=d%10; 
    disp.display(1,sedemseg[d]);
    d=cislo/10;
    d=d%10; 
    disp.display(2,sedemseg[d]);
    d=cislo%10; 
    disp.display(3,sedemseg[d]);
  }
}
///////////////////////////////////////////////
///////////////////////////////////////////////
//ff97 -105
//ffcf -49
//ffe7 -25
//ff85 -123
//ffef -17
//ffc7 -57
//ffa5 -91
//ffbd -67
//ffb5 -75
//ffad -83
//+ 87
//- 31
//100+ 103
//200+ 79
int BajtToInt(char vstup[16])
{
  String u = String(vstup[9],DEC); 
  int vystup=u.toInt();
  switch(vystup){
    case -105:
    vystup = 0;
    break;
    case -49:
    vystup = 1;
    break;
    case -25:
    vystup = 2;
    break;
    case -123:
    vystup = 3;
    break;
    case -17:
    vystup = 4;
    break;
    case -57:
    vystup = 5;
    break;
    case -91:
    vystup = 6;
    break;
    case -67:
    vystup = 7;
    break;
    case -75:
    vystup = 8;
    break;
    case -83:
    vystup = 9;
    break;
////////////////////////////////
    case 87:
    vystup = 10;
    break;
    case 31:
    vystup = 11;
    break;
    
    default:
    vystup = 10000;
  }
  return vystup;
}
///////////////////////////////////////////
//////////////////////////////////////////
int kalkulacka(int znak)
{
if((znak>=0)&(znak<=9))
    {
      
      if (cislo/1000)
      else
      {
        if (cislo/100)
        {
          cislo=cislo+1000*znak
        }  
        else
        {
          if (cislo/10)
          {
             cislo=cislo+100*znak
          }
          else
          {
            if (cislo/1)
            {
              cislo=cislo+10*znak
            }
            else
            {
              cislo=znak
            }
          }
        }
      }
    }
    else if ((znak==10)&(znak==11))
    {
      cislo_1=cislo;
      cislo = 0;
      ukon=znak
    }
    else if (znak==12)
    {
      cislo_2=cislo;
      if (ukon=10)
      {
      vysledok = cislo_1 + cislo_2;
      cislo_1=cislo_2=0;
      }
      if (ukon=10)
      {
      vysledok = cislo_1 + cislo_2;
      cislo_1=cislo_2=0;
      }
       return vysledok;
    }  
     return cislo;
}
/////////////////////////////////////////////// 
void setup() 
{
  disp.clearDisplay();
  Serial.begin(9600);
  IR.Init(4);
  cislo = 0;
  cislo_1 = 0;
  cislo_2 = 0;
  vysledok = 0;
}  
void loop() 
{
  int znak;
  char pole[16];
  if(IR.IsDta())
  {
    IR.Recv(pole);
    znak=BajtToInt(pole);
    znak=kalkulacka(znak);
    cele_cisla(znak);
    Serial.println(znak);
  }  
}
