
#include "Toggle.h"

int r[]={0,0,0,0,0};  //switches state array
int fb[]={0,0,0,0,0};  //feedback state array
int ts[]={0,0,0,0,0};

const int adc = A0; //vibrations sensor pin
#define re1   5 //switch 1
#define re2   4 //switch 2
#define re3   0 //switch3
#define re4   2 //switch4
#define re5   15 //switch5
#define sela 16 //A
#define selb   14 //B
#define selc   12 //C
#define muxout   13 //mux out

String id="a3f5mh*o6sb%";
 
void setup() {
  
  delay(10);
  
  Serial.begin(115200);
  
  ToggleBegin();
    
 pinMode(re1, OUTPUT); pinMode(re2, OUTPUT);pinMode(re3, OUTPUT);pinMode(re4, OUTPUT);pinMode(re5, OUTPUT);
 pinMode(muxout, INPUT);
 pinMode(sela, OUTPUT);pinMode(selb, OUTPUT);;pinMode(selc, OUTPUT);//pinMode(10, OUTPUT);


}




void loop() {
  
  delay (10);
   
ToggleLoop();


muxf(10);

}



String s_data()
  {
    
  String ark[]={"swhs","fb"};
 String arv[]={"["+arts(r,5)+"]","["+arts(fb,4)+"]"};
  int ari[]={0,0};
  
  return d_add(ark,arv,ari,2);
  }

 void r_orders(String ordstr)
   {
  int ord=0;
    
    y=ordstr;
     
    String yv1=getValue(y,'/',0);
    
    ord=0;
    ord= (yv1=="ch1")? 2:ord;
    ord= (yv1=="ch2")? 3:ord;
    ord= (yv1=="ch3")? 4:ord;
    ord= (yv1=="ch4")? 5:ord;
    ord= (yv1=="ch5")? 6:ord;
    
  switch(ord){
      
     
      case 2:
     r[0]=getValue(y,'/',1).toInt();
      writerelays(r,0);
      break;
      
      case 3:
     r[1]=getValue(y,'/',1).toInt();
      writerelays(r,0);
      break;
      
      case 4:
       r[2]=getValue(y,'/',1).toInt();
      writerelays(r,0);
   
      break;
      
      case 5:
      r[3]=getValue(y,'/',1).toInt();
      writerelays(r,0);
      break;
      
      case 6:
       r[4]=getValue(y,'/',1).toInt();
      writerelays(r,0);
      break;
      
   }
   }

void muxf(int d){
  
    for (int i=0;i<4;i++){
   digitalWrite(sela,bitRead(i,0));
   digitalWrite(selb,bitRead(i,1));
   digitalWrite(selc,bitRead(i,2));
   
   delay(d);
   
    if ((digitalRead(muxout)==1) &&(ts[i]==0)){
    r[i]=r[i]==1?0:1;
    writerelays(r,0);
    }
    
    ts[i]=digitalRead(muxout);
  }
  
 for (int i=4;i<8;i++){
   digitalWrite(sela,bitRead(i,0));
   digitalWrite(selb,bitRead(i,1));
   digitalWrite(selc,bitRead(i,2));
   
   delay(d);

   fb[i-4]=digitalRead(muxout);
    
  }
  
  }



  void writerelays(int w[],int idx){ //function digital write the switches state array to the switches pins
  if (w[idx]!=2){digitalWrite(re1,w[idx]);r[0]=w[idx];}
  if (w[idx+1]!=2){digitalWrite(re2,w[idx+1]);r[1]=w[idx+1];}
  if (w[idx+2]!=2){digitalWrite(re3,w[idx+2]);r[2]=w[idx+2];}
  if (w[idx+3]!=2){digitalWrite(re4,w[idx+3]);r[3]=w[idx+3];}
  if (w[idx+4]!=2){digitalWrite(re5,w[idx+4]);r[4]=w[idx+4];}
}
