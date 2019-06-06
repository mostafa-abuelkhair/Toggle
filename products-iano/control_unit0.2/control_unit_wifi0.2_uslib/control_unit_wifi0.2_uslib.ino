
#include "Toggle.h"

int outputs_v[]={0,0,0,0,0};
String outputs_k[]={"ch1","ch2","ch3","ch4","ch5"};
int outputs_n=5;
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

int op[]={re1,re2,re3,re4,re5};

String id="a3f5mh*o6sb%";
String pid="control-unit0.2";
 
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

 String data(){
  
 String sensors_k[]={};
 String sensors_v[]={};
 int sensors_n;
 String data_k[]={"swhs","fb"};
 String data_v[]={"["+arts(outputs_v,5)+"]","["+arts(fb,4)+"]"};
 int data_t[]={0,0};
 int data_n=2;
  
  return d_add(data_k,data_v,data_t,data_n,outputs_k,outputs_v,outputs_n,sensors_k,sensors_v,sensors_n);
  
  }

 void orders(String ordstr)
   {

   dw_op(ordstr, outputs_k, outputs_v, op, outputs_n);

   }

void muxf(int d){
  
    for (int i=0;i<4;i++){
   digitalWrite(sela,bitRead(i,0));
   digitalWrite(selb,bitRead(i,1));
   digitalWrite(selc,bitRead(i,2));
   
   delay(d);
   
    if ((digitalRead(muxout)==1) &&(ts[i]==0)){
    outputs_v[i]=outputs_v[i]==1?0:1;
    writerelays(outputs_v,0);
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
  if (w[idx]!=2){digitalWrite(re1,w[idx]);outputs_v[0]=w[idx];}
  if (w[idx+1]!=2){digitalWrite(re2,w[idx+1]);outputs_v[1]=w[idx+1];}
  if (w[idx+2]!=2){digitalWrite(re3,w[idx+2]);outputs_v[2]=w[idx+2];}
  if (w[idx+3]!=2){digitalWrite(re4,w[idx+3]);outputs_v[3]=w[idx+3];}
  if (w[idx+4]!=2){digitalWrite(re5,w[idx+4]);outputs_v[4]=w[idx+4];}
}
