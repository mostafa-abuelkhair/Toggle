
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
    
  String ark[]={"key1","key2"};                   //data keys
  String arv[]={"string data1","integer data2"};  //data values
  int ari[]={1,0};                                // 1 for string data and 0 for others
  
  return d_add(ark,arv,ari,2);
  }


 
