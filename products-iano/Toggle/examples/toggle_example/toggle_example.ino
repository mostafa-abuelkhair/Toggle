
#include "Toggle.h"

String id="xxxxxxxxxxxx";    //unit id
String pid="xxxxxxx";        //product id

void setup() {
  
  delay(10);
  
  Serial.begin(115200);
  
  ToggleBegin();
}



void loop() {
  
  delay (10);
   
ToggleLoop();

}



void orders(String ordstr)   //function to receive orders from app
   {
    
  //dw_op(ordstr, outputs_k, outputs_v, op, outputs_n);     // digital write outputs 

  int ord=0; 
  y=ordstr;  
  String yv1=getValue(y,'/',0);
    
    ord=0;
    ord= (yv1=="ord1")? 1:ord;
    ord= (yv1=="ord2")? 2:ord;
    ord= (yv1=="ord3")? 3:ord;
    
  switch(ord){
      
       case 1:
   // do something here
      break;
      
      case 2:
   // do something here 
      break;
      
      case 3:
   // do something here
      break;
      
   }
   }



String data()   //function to send data to app
  {
    
 String outputs_k[]={};      //outputs keys
 int outputs_v[]={};         //outputs values
 int outputs_n=0;            //outputs number
 String sensors_k[]={};      //sensors keys 
 String sensors_v[]={};      //sensors values
 int sensors_n=0;              //sensors number
 String data_k[]={};         //data keys
 String data_v[]={};         //data values
 int data_t[]={};            //data type   1 for string  0 for others
 int data_n=0;               //data number
  
  return d_add(data_k,data_v,data_t,data_n,outputs_k,outputs_v,outputs_n,sensors_k,sensors_v,sensors_n);
  }


 
