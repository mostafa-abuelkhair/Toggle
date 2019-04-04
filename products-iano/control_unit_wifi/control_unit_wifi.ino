

#include <DHT.h>;
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <EEPROM.h>
#include <Servo.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

//#-id-bluepass-wfstate-wfon-r[8]-alarm-door-tr[12]-sr[11]-vr[11]
//Variables

ESP8266WebServer server(80);

int chk;
float hum;  //Stores humidity value
float temp; //Stores temperature value
float smoker = 0;  //smoke sensor readig
float knockr = 0;  // vibration sensor reading
String id="a2f5mh*o6sb%";
String wfstate="no connection";
IPAddress ip ;
String ipa="";
String ssidpass;
 String ssid = "no";
 String password = "no";
 String apssid = "control-unit";
 String appass= "123456789";
 String wfon="0";
 int tn=1; //temp sensor on/off
int tx=800; //temp alarm point
int sn=1; //smoke sensor on/off
int sx=800; //smoke alarm point
int kn=1; //vibrations sensor on/off
int kx=100; //vibrations alarm point
int r[]={0,0,0,0,0,0,0,0};  //switches state array  
int tr[]={0,0,80,1,1,1,1,1,1,1,1,1}; // switches state after smoke alarm
int sr[]={0,600,1,1,1,1,1,1,1,1,1}; // switches state after temprature alarm
int vr[]={0,100,1,0,0,0,0,0,0,0,0}; // switches state after vibrations alarm
int rr1,rr2;
float tempth;

int alarm=0,door=0; //alarm,door on/off 
int wcount;


const int analogsensor = A0; //vibrations sensor pin
#define re1   D0 //switch 1
#define re2   D1 //switch 2
#define re3   D2 //switch3
#define re4   D3 //switch4
#define re5   D4 //switch5
#define re6   D6 //switch6
#define re7   D4 //switch7
#define re8   D4 //switch8
#define serin   D8 //alarm pin
 #define doorout D5
 #define DHTPIN D7    // what pin we're connected to temp sensor
#define DHTTYPE DHT11   // DHT 11  (AM2302)
DHT dht(DHTPIN, DHTTYPE,15); //// Initialize DHT sensor for normal 16mhz Arduino
Servo myservo;
int mx=0,svx=0; //counters
String y="Lbj";
String bdt="Lbj";
String sdt="Lbj";
String temp1="Lbj";
boolean bup=false,sup=false,up=false;
int cas =0;

void setup() {
  
  delay(10);
  myservo.attach(doorout); 
  
  Serial.begin(115200);
  dht.begin();
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
  
 pinMode(D0, OUTPUT); pinMode(D1, OUTPUT);pinMode(D2, OUTPUT);pinMode(D3, OUTPUT);pinMode(D4, OUTPUT);pinMode(D6, OUTPUT);pinMode(D8, OUTPUT);//pinMode(10, OUTPUT);
digitalWrite(serin,0);


y="";
bdt="";
sdt="";
 delay(1000);
WiFi.mode(WIFI_AP_STA); 

   Serial.println();
  Serial.print("Configuring access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(apssid.c_str(),appass.c_str(),4);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/",appget);
  server.begin();
  Serial.println("HTTP server started");
   delay(100);
    
WiFi.begin(ssid.c_str(),password.c_str());   //WiFi connection
    wcount=0;
  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
    if(wcount==20){break;}
    wcount++;
    wfstate="connecting to "+ssid;
    Serial.println(wfstate);
    delay(500);
  }
    if (WiFi.status() == WL_CONNECTED){
      serversend();delay(10);if(wfon=="1"){serverget(0);}Serial.println("local ip : "+WiFi.localIP().toString());
    wfstate="unit connected to "+ssid ;
    }
    else{WiFi.disconnect(); wfstate="unit faild to connect to wifi";}
   delay(1000);


   
  myservo.write((door==1)?180:0); 

  Serial.println(jstrdata());
}




void loop() {
  
  delay (10);
 mx++;
   //svx++;
   
 server.handleClient();
 
if(wfon=="1"){serverget(1);}

 if(bup){sup=true;bup=false;}

 if(sup&&(wfon=="1")){serversend();}
        
  if (WiFi.status() != WL_CONNECTED){
    WiFi.disconnect(); wfstate="unit faild to connect to wifi";
    }

   

  //reading from humidity and temprature sensors
  //fire alarm if it exceeds the alarm point
if (mx==250) {
  mx=0;
/* delay(1500);
  if(tr[3]==1){
     tempth=dht.readTemperature();
     Serial.println(tempth);
    tr[0]=(tempth>=1)? (int)tempth:tr[0];
 if (tr[0]>=tr[2]){
      alarm=1;digitalWrite(serin,alarm);writerelays(tr,4);
     }   
     tempth=dht.readHumidity();
   tr[1] = (tempth>=1)? (int)tempth:tr[1];

     }
      bup=true;sup=true;*/
     }
     

   //reading from vibrations sensor 
  //fire alarm if it exceeds the alarm point
  
 if (sr[2]==1){
  
     sr[0]=analogRead(analogsensor);
     
     if (sr[0]>=sr[1]){alarm=1;digitalWrite(serin,alarm);writerelays(sr,3);}
     
     }

        
delay(1);

}



void appget(){
  temp1=server.arg(0);
  if(temp1=="get"){ipa=server.arg(2);}
  orders(temp1);
 if(getValue(temp1,'/',0)!="wfset"){ appsend();}
  sup= (sup)? sup:up;
  up=false;
  
  }

void appsend(){
server.sendHeader("Access-Control-Allow-Origin","*");
server.send(200,"text",jstrdata());
bup=false;

  }
  
void serverget(int z){
  
 if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
  
   HTTPClient http;    //Declare object of class HTTPClient
   String g="http://remotech.000webhostapp.com/unit.php?key=get&id="+id;
   g.replace(" ", "%20");
   http.begin(g); //Specify request destination
   http.setTimeout(500);
   http.addHeader("Content-Type", "text/plain");  //Specify content-type header
   int httpCode = http.GET();   //Send the request
   String payload = http.getString();   //Get the response payload
   
   if (z==1){orders(payload);}
   
    bup= (bup)? bup:up;
    up=false;
   
   http.end();  //Close connection
 }

  }

  void serversend(){
    
   if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
   HTTPClient http;    //Declare object of class HTTPClient
   String g="http://remotech.000webhostapp.com/unit.php?key=send&id="+id+"&data="+(strdata().substring(1));
    g.replace(" ", "%20");
   http.begin(g); 
   http.setTimeout(1500);
   //Specify request destination
   http.addHeader("Content-Type", "text/plain");  //Specify content-type header
   int httpCode = http.GET();   //Send the request
   String payload = http.getString();                  //Get the response payload  
   http.end();  //Close connection
   sup=false;
 }
    
    }
  

void orders(String ordstr){

  int ord=0;
    
    y=getValue(ordstr,'-',0);
     
    String yv1=getValue(y,'/',0);
    
    ord=0;
    ord= (y=="get")?   1:ord;
    ord= (yv1=="alm")? 2:ord;
    ord= (yv1=="dor")? 3:ord;
    ord= (yv1=="ch1")? 4:ord;
    ord= (yv1=="ch2")? 5:ord;
    ord= (yv1=="ch3")? 6:ord;
    ord= (yv1=="ch4")? 7:ord;
    ord= (yv1=="ch5")? 8:ord;
    ord= (yv1=="ch6")? 9:ord;
    ord= (yv1=="ch7")? 10:ord;
    ord= (yv1=="ch8")? 11:ord;
    ord= (yv1=="settemps")? 12:ord;
    ord= (yv1=="setsmokes")? 13:ord;
    ord= (yv1=="setvibrs")? 14:ord;
    ord= (yv1=="wfset")? 15:ord;
    ord= (yv1=="wfon")? 16:ord;
    ord= (yv1=="appass")? 17:ord;
    
    switch(ord){
      
      case 1:
     // appsend();
       up=true;
      break;
      
      case 2:
      alarm=getValue(y,'/',1).toInt();
      digitalWrite(serin,alarm);
       up=true;
      break;
      
      case 3:
      door=getValue(y,'/',1).toInt();
   
       myservo.write((door==1)?180:0); 
       up=true;
      break;
      
      case 4:
      r[0]=getValue(y,'/',1).toInt();
      writerelays(r,0);
       up=true;
      break;
      
      case 5:
      r[1]=getValue(y,'/',1).toInt();
       writerelays(r,0);
        up=true;
      break;
      
      case 6:
      r[2]=getValue(y,'/',1).toInt();
      writerelays(r,0);
       up=true;
      break;
      
      case 7:
      r[3]=getValue(y,'/',1).toInt();
      writerelays(r,0);
       up=true;
      break;
      
      case 8:
      r[4]=getValue(y,'/',1).toInt();
      writerelays(r,0);
       up=true;
      break;
      
      case 9:
      r[5]=getValue(y,'/',1).toInt();
      writerelays(r,0);
       up=true;
      break;
      
      case 10:
      r[6]=getValue(y,'/',1).toInt();
      writerelays(r,0);
       up=true;
      break;
      
      case 11:
      r[7]=getValue(y,'/',1).toInt();
      writerelays(r,0);
       up=true;
      break;
      
      case 12:
      rr1=tr[0];
      rr2=tr[1];
      star(getValue(y,'/',1),tr,12);
      tr[0]=rr1;tr[1]=rr2;
       up=true;
      break;
      
      case 13:
      rr1=sr[0];
      star(getValue(y,'/',1),sr,11);
      sr[0]=rr1;
       up=true;
      break;
      
      case 14:
        rr1=vr[0];
      star(getValue(y,'/',1),vr,11);
      vr[0]=rr1;
       up=true;
      break;
      
      case 15:
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
      
    wcount=0;
    
  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
    if(wcount==20){break;}
    wcount++;
    server.handleClient();
    //Serial.print(strdata());
    delay(500);
  }
  delay(100);
       if (WiFi.status() == WL_CONNECTED){
      serversend();delay(10);if(wfon=="1"){serverget(0);}Serial.println("local ip : "+WiFi.localIP().toString());
    wfstate="unit connected to "+ssid ;
    }
    else{WiFi.disconnect(); wfstate="unit faild to connect to wifi";}
   //Serial.print(strdata());
    up=true;
      break;
      
      case 16:
       wfon=getValue(y,'/',1);
       if(wfon=="1"){serverget(0);}
        up=true;
      break;
      
      case 17:
    appass=getValue(y,'/',1);
    
   for(int ii=0;ii<appass.length();ii++){
    EEPROM.write(ii+50,appass.charAt(ii));
    EEPROM.commit();
    }
     EEPROM.write(110,appass.length());
    EEPROM.commit();

    
   WiFi.softAPdisconnect();
   WiFi.softAP(apssid.c_str(),appass.c_str(),4);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  Serial.println("new ap started");
      up=true;
      break;
      
      }
      ord=0; 
  }

String strdata(){
  //#-id-appass-wfstate,localip-ssid-wfon-r[8]-alarm-door-tr[12]-sr[11]-vr[11]-
  String dt;
  dt="#-"+id+"-"+appass+"-"+wfstate+","+WiFi.localIP().toString()+"-"+wfon+"-"+arts(r,8)+"-"+String(alarm)+"-"+String(door)+"-"+arts(tr,12)+"-"+arts(sr,11)+"-"+arts(vr,11)+"-";

 return dt;
  }

String jstrdata(){
 // dt="{'rep':'0432','id':'"+id+"','appass':'"+appass+"','wfstate':'"+wfstate+"','ip':'"+WiFi.localIP().toString()+"','wfon':'"+wfon+"',"
 String ark[]={"pid","id","appass","wfstate","ip","wfon","swhs","alarm","door","sensors","sd"};
 String arv[]={"control-unit",id,appass,wfstate,ipa,wfon,"["+arts(r,8)+"]",String(alarm),String(door),"[{'name':'a0-connected sensor','reading':"+String(sr[0])+"}]","["+arts(sr,11)+"]"};
  int ari[]={1,1,1,1,1,0,0,0,0,0,0};
  String dt=jsonf(ark,arv,ari,11);
  
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
  if (w[idx+5]!=2){digitalWrite(re6,w[idx+5]);r[5]=w[idx+5];}
  if (w[idx+6]!=2){digitalWrite(re7,w[idx+6]);r[6]=w[idx+6];}
  if (w[idx+7]!=2){digitalWrite(re8,w[idx+7]);r[7]=w[idx+7];}
}

/*void relays(String x){//function to handle switches requests
  if(x=="r1"){
    r[0]=(r[0]==0)?1:0; digitalWrite(re1,r[0]);
  }
    else if(x=="r2"){
    r[1]=(r[1]==0)?1:0; digitalWrite(re2,r[1]);
    }
    else if(x=="r3"){
    r[2]=(r[2]==0)?1:0; digitalWrite(re3,r[2]);
    }
   else if(x=="r4"){
    r[3]=(r[3]==0)?1:0; digitalWrite(re4,r[3]);
   }
   else if(x=="r5"){
    r[4]=(r[4]==0)?1:0; digitalWrite(re5,r[4]);
   }
  else if(x=="r6"){
    r[5]=(r[5]==0)?1:0; digitalWrite(re6,r[5]);
  }
   else if(x=="r7"){
    r[6]=(r[6]==0)?1:0; digitalWrite(re7,r[6]);
   }
   else if(x=="r8"){
    r[7]=(r[7]==0)?1:0; digitalWrite(re8,r[7]);
   }

    }*/

   
