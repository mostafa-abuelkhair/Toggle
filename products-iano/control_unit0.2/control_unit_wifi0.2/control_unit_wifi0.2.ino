
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <EEPROM.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

//Variables

ESP8266WebServer server(80);

int chk;
String id="a3f5mh*o6sb%";
String pname="control-unit";
String wfstate="no connection";
IPAddress ip ;
String ipa="";
String ssidpass;
 String ssid = "no";
 String password = "no";
 String apssid = "control-unit0.2";
 String appass= "0123456789";
 String wfon="0";
int r[]={0,0,0,0,0};  //switches state array
int fb[]={0,0,0,0,0};  //feedback state array
int ts[]={0,0,0,0,0};
int wcount;
int uctw =0;


const int adc = A0; //vibrations sensor pin
#define re1   5 //switch 1
#define re2   4 //switch 2
#define re3   0 //switch3
#define re4   2 //switch4
#define re5   15 //switch5
#define sela 16 //mux out
#define selb   14 //A
#define selc   12 //B
#define muxout   13 //C

String y="Lbj";
String bdt="Lbj";
String sdt="Lbj";
int cas =0;

void setup() {
  
  delay(10);
  
  Serial.begin(115200);
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
    
 pinMode(re1, OUTPUT); pinMode(re2, OUTPUT);pinMode(re3, OUTPUT);pinMode(re4, OUTPUT);pinMode(re5, OUTPUT);
 pinMode(muxout, INPUT);
 pinMode(sela, OUTPUT);pinMode(selb, OUTPUT);;pinMode(selc, OUTPUT);//pinMode(10, OUTPUT);



y="";
bdt="";
sdt="";
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


  Serial.println(jstrdata());
}




void loop() {
  
  delay (10);
   
 server.handleClient();
        
  if ( (WiFi.status() != WL_CONNECTED) && (uctw) ){
    WiFi.disconnect();uctw=0; wfstate="unit faild to connect to other wifi network";
    }


muxf(10);
        
delay(1);

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

void appget(){
  String temp1=server.arg(0);
  if(temp1=="get"){ipa=server.arg(2);}
  orders(temp1);
 if(getValue(temp1,'/',0)!="wfset"){ appsend();}
  
  }

void appsend(){
server.sendHeader("Access-Control-Allow-Origin","*");
server.send(200,"text",jstrdata());

  }
  

void orders(String ordstr){

  int ord=0;
    
    y=ordstr;
     
    String yv1=getValue(y,'/',0);
    
    ord=0;
    ord= (y=="get")?   1:ord;
    ord= (yv1=="ch1")? 2:ord;
    ord= (yv1=="ch2")? 3:ord;
    ord= (yv1=="ch3")? 4:ord;
    ord= (yv1=="ch4")? 5:ord;
    ord= (yv1=="ch5")? 6:ord;
    ord= (yv1=="wfset")? 7:ord;
    ord= (yv1=="wfon")? 8:ord;
    ord= (yv1=="appass")? 9:ord;
    ord= (yv1=="name")? 10:ord;
    
    switch(ord){
      
      case 1:
    
      break;
      
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


String jstrdata(){

 String ark[]={"pid","id","appass","wfstate","ip","wfon","swhs","fb","name"};
 String arv[]={"control-unit0.2",id,appass,wfstate,ipa,wfon,"["+arts(r,5)+"]","["+arts(fb,4)+"]",pname};
  int ari[]={1,1,1,1,1,0,0,0,1};
  String dt=jsonf(ark,arv,ari,9);
  
  return dt;
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

  String jsonf(String a[],String b[],int c[],int asize){
    String dt2="{'rep':'0432'";
    for(int g=0;g<asize;g++){
      dt2+=",'";
      dt2+=a[g];
      dt2+="':";
      if(c[g]==1){dt2+="'"+b[g]+"'";}
      else{dt2+=b[g];}
      }
   dt2+="}";
   return dt2;
    }

    
   void star(String v,int arra[],int asize){
    String smss;
    for(int g=0;g<asize;g++){
      smss=getValue(v,',',g);
      arra[g]=smss.toInt();
      }
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




void writerelays(int w[],int idx){ //function digital write the switches state array to the switches pins
  if (w[idx]!=2){digitalWrite(re1,w[idx]);r[0]=w[idx];}
  if (w[idx+1]!=2){digitalWrite(re2,w[idx+1]);r[1]=w[idx+1];}
  if (w[idx+2]!=2){digitalWrite(re3,w[idx+2]);r[2]=w[idx+2];}
  if (w[idx+3]!=2){digitalWrite(re4,w[idx+3]);r[3]=w[idx+3];}
  if (w[idx+4]!=2){digitalWrite(re5,w[idx+4]);r[4]=w[idx+4];}
}
   
