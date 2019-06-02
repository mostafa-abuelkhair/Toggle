/*
  Toggle.h - Library for using toggle app.
  Created by mostafa ahmed.
  Released into the public domain.
*/

#ifndef Toggle_h
#define Toggle_h


void ToggleBegin();
void ToggleLoop();
void appsend();
void appget();
String arts(int v[],int asize);
String getValue(String data, char separator, int index);
String d_add(String a[],String b[],int c[],int asize);
void star(String v,int arra[],int asize);
void orders(String ordstr);
String jstrdata();
void r_orders(String ordstr);
String s_data();


#include "Arduino.h"
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <EEPROM.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

extern String id;
extern String pname;
extern String apssid;
extern String appass;

String wfstate="no connection";
IPAddress ip ;
String ipa="";
String ssidpass;
String ssid = "no";
String password = "no";
int wcount;
int uctw =0;
String wfon="0";
String y="";
String bdt="";
String sdt="";
int cas =0;

String p_key="";


ESP8266WebServer server(80);

  
 


void ToggleBegin()
{

EEPROM.begin(512);
  
ssidpass="";


int eesz=EEPROM.read(100);
for(int i2=0;i2<eesz;i2++){
  ssidpass+=char(EEPROM.read(i2));
    }
  ssid=getValue(ssidpass,'-',0);password=getValue(ssidpass,'-',1);
  
 appass="";
 
   eesz=EEPROM.read(110);
for(int i2=0;i2<eesz;i2++){
  appass+=char(EEPROM.read(i2+50));
    }

pname="";
     eesz=EEPROM.read(150);
for(int i2=0;i2<eesz;i2++){
  pname+=char(EEPROM.read(i2+111));
    }


delay(1000);
WiFi.mode(WIFI_AP_STA); 

   Serial.println();
  Serial.print("Configuring access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(pname.c_str(),appass.c_str(),4);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/",appget);
  server.begin();
  Serial.println("HTTP server started");
   delay(100);
    
WiFi.begin(ssid.c_str(),password.c_str());   //WiFi connection
    uctw=1;
    wcount=0;
  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
    if(wcount==20){break;}
    wcount++;
    wfstate="connecting to "+ssid;
    Serial.println(wfstate);
    delay(500);
  }
    if (WiFi.status() == WL_CONNECTED){
      Serial.println("local ip : "+WiFi.localIP().toString());
    wfstate="unit connected to "+ssid ;
    }
    else{WiFi.disconnect();uctw=0; wfstate="unit faild to connect to other wifi network";}
   delay(1000);

}

void ToggleLoop()
{

 server.handleClient();
        
  if ( (WiFi.status() != WL_CONNECTED) && (uctw) ){
    WiFi.disconnect();uctw=0; wfstate="unit faild to connect to other wifi network";
    }
}



    
void appsend(){
server.sendHeader("Access-Control-Allow-Origin","*");
server.send(200,"text",jstrdata());

  }


String jstrdata(){
  
String dt="";
 dt="{'rep':'0432'";

 String ark[]={"pid","id","appass","wfstate","ip","wfon","name"};
 String arv[]={"control-unit0.2",id,appass,wfstate,ipa,wfon,pname};
  int ari[]={1,1,1,1,1,0,1};
  dt+=d_add(ark,arv,ari,7);
  
  dt+=s_data();

   dt+="}";
Serial.println(dt);
  return dt;
  }
  
  String d_add(String a[],String b[],int c[],int asize){

    String dt2="";
    for(int g=0;g<asize;g++){
      dt2+=",'";
      dt2+=a[g];
      dt2+="':";
      if(c[g]==1){dt2+="'"+b[g]+"'";}
      else{dt2+=b[g];}
      }

   return dt2;
    }
    

void appget(){
  String temp1=server.arg(0);
  if(temp1=="get"){ipa=server.arg(2);}
  orders(temp1);
  r_orders(temp1);
 if(getValue(temp1,'/',0)!="wfset"){ appsend();}
  
  }
  

void orders(String ordstr){

  int ord=0;
    
    y=ordstr;
     
    String yv1=getValue(y,'/',0);
    
    ord=0;
    ord= (y=="get")?   1:ord;
    ord= (yv1=="wfset")? 7:ord;
    ord= (yv1=="wfon")? 8:ord;
    ord= (yv1=="appass")? 9:ord;
    ord= (yv1=="name")? 10:ord;
    
    switch(ord){
      
      case 1:
    
      break;
      
      case 7:
      ssid=getValue(getValue(y,'/',1),',',0);
      password=getValue(getValue(y,'/',1),',',1);
      ssidpass=ssid+'-'+password+'-';
      
         wfstate="connecting to "+ssid;
         appsend();
      
    for(int ii=0;ii<ssidpass.length();ii++){
    EEPROM.write(ii,ssidpass.charAt(ii));
    EEPROM.commit();
    }
     EEPROM.write(100,ssidpass.length());
    EEPROM.commit();

      WiFi.disconnect(); 
      delay(100);
      WiFi.begin(ssid.c_str(),password.c_str());
      uctw=1;
    wcount=0;
    
  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
    if(wcount==20){break;}
    wcount++;
    server.handleClient();
    delay(500);
  }
  delay(100);
       if (WiFi.status() == WL_CONNECTED){
      Serial.println("local ip : "+WiFi.localIP().toString());
    wfstate="unit connected to "+ssid ;
    }
    else{WiFi.disconnect();uctw=0; wfstate="unit faild to connect to other wifi network";}
  
      break;
      
      case 8:
       wfon=getValue(y,'/',1);
      break;
      
      case 9:{
    appass=getValue(y,'/',1);
    
   for(int ii=0;ii<appass.length();ii++){
    EEPROM.write(ii+50,appass.charAt(ii));
    EEPROM.commit();
    }
     EEPROM.write(110,appass.length());
    EEPROM.commit();

    
   WiFi.softAPdisconnect();
   WiFi.softAP(pname.c_str(),appass.c_str(),4);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  Serial.println("new ap started");}
      break;

       case 10 :
    pname=getValue(y,'/',1);
    
   for(int ii=0;ii<pname.length();ii++){
    EEPROM.write(ii+111,pname.charAt(ii));
    EEPROM.commit();
    }
     EEPROM.write(150,pname.length());
    EEPROM.commit();
    
      break;
      
      }
      ord=0; 
  }
  

 String getValue(String data, char separator, int index)  //function to split string by char
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            
            strIndex[1] = (data.charAt(i) == separator) ? i:i+1;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

 String arts(int v[],int asize){
    String dt1;
    for(int g=0;g<asize;g++){
      dt1+=v[g];
      dt1+=",";
      }
    dt1=dt1.substring(0,dt1.length()-1);
    return dt1;
    }



    
   void star(String v,int arra[],int asize){
    String smss;
    for(int g=0;g<asize;g++){
      smss=getValue(v,',',g);
      arra[g]=smss.toInt();
      }
    }




   

#endif
