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
void r_orders(String ordstr);
String jstrdata();
void orders(String ordstr);
String data();
void eep_write(String val,int st, int leidx);
String eep_read(int st, int leidx);


#include "Arduino.h"
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <EEPROM.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

extern String id;
extern String pid;

String appass;
String pname;
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
  
 ssidpass=eep_read(0,100);
 ssid=getValue(ssidpass,'-',0);password=getValue(ssidpass,'-',1);
  
 appass=eep_read(50,110);
 
 pname=eep_read(111,150);

 p_key=eep_read(160,200);



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

 String ark[]={"pid","id","appass","wfstate","ip","wfon","name","repeatper"};
 String arv[]={pid,id,appass,wfstate,ipa,wfon,pname,"200"};
  int ari[]={1,1,1,1,1,0,1,0};
  dt+=d_add(ark,arv,ari,8);
  
  dt+=data();

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
  String r_key=server.arg(1);
  if(temp1=="get"){ipa=server.arg(2);}

if (r_key==p_key || p_key=="") {

  r_orders(temp1);
  orders(temp1);

 if(getValue(temp1,'/',0)!="wfset"){ appsend();}

  }

  }
  

void r_orders(String ordstr){

  int ord=0;
    
    y=ordstr;
     
    String yv1=getValue(y,'/',0);
    
    ord=0;
    ord= (y=="get")?   1:ord;
    ord= (yv1=="wfset")? 7:ord;
    ord= (yv1=="wfon")? 8:ord;
    ord= (yv1=="appass")? 9:ord;
    ord= (yv1=="name")? 10:ord;
    ord= (yv1=="key")? 11:ord;

    switch(ord){
      
      case 1:
    
      break;
      
      case 7:
      ssid=getValue(getValue(y,'/',1),',',0);
      password=getValue(getValue(y,'/',1),',',1);
      ssidpass=ssid+'-'+password+'-';
      
         wfstate="connecting to "+ssid;
         appsend();
      
    eep_write(ssidpass,0,100);

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
    
    eep_write(appass,50,110);

    
   WiFi.softAPdisconnect();
   WiFi.softAP(pname.c_str(),appass.c_str(),4);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  Serial.println("new ap started");}
      break;

       case 10 :
    pname=getValue(y,'/',1);
    
    eep_write(pname,111,150);
    
      break;

       case 11 :
    p_key=getValue(y,'/',1);
    
    eep_write(p_key,160,200);
    
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



void eep_write(String val,int st, int leidx)  //function to write to eeprom
  {
    
 for(int ii=0;ii<val.length();ii++){
    EEPROM.write(ii+st,val.charAt(ii));
    EEPROM.commit();
    }
     EEPROM.write(leidx,val.length());
    EEPROM.commit();
  
  }

  String eep_read(int st, int leidx) //function to read from eeprom
  {
    
String dt="";
     int eesz=EEPROM.read(leidx);
    for(int i2=0;i2<eesz;i2++){
      dt+=char(EEPROM.read(i2+st));
    }
  return dt;
  }
   

#endif
