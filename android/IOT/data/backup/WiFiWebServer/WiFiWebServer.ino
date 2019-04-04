/*
 *  This sketch demonstrates how to set up a simple HTTP-like server.
 */

#include <ESP8266WiFi.h>

int r[]={1,1,1,1,1,1,1,1},sr[]={1,1,1,1,1,1,1,1},tr[]={1,1,1,1,1,1,1,1},kr[]={0,0,0,0,0,0,0,0};
int ser=0,tn=1,tx=800,sn=1,sx=800,kn=1,kx=100;
String vb="dgdglklklkl";
String vsb="dgdglklklkl"+vb+"dfdf";
int smoker = 0;  
int knockr = 0;  
const int analogsensor = A0;
 #define serin   D10
 #define DS18B20_PIN   D9
 #define swh   D0
int raw_temp;
float temp;
char txt[] = " C ";
int lx=0;
int mx=0;

IPAddress ip ;
const char* ssid = "your-ssid";
const char* password = "your-password";

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);

 pinMode(D0, OUTPUT); pinMode(D1, OUTPUT);pinMode(D2, OUTPUT);pinMode(D4, OUTPUT);pinMode(D5, OUTPUT);pinMode(D6, OUTPUT);pinMode(D7, OUTPUT);pinMode(D8, OUTPUT);pinMode(D3, OUTPUT);pinMode(D10, OUTPUT);
   digitalWrite(D0,0);
txt[0] = 223;   
  
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  ip=WiFi.localIP();
  Serial.println(ip);
}

void loop() {
  delay (10);
  lx++;mx++;
  String y="Lbj";
  
if ((mx==10)&&(tn==1)) {
   if(ds18b20_read(&raw_temp)) {
    temp = (float)raw_temp / 16; mx=0;    // Convert temperature raw value into degree Celsius (temp in °C = raw/16)
 if (temp>=tx){
      ser=1;digitalWrite(serin,ser);writerelays(tr);
     }}}
  
   
  if ((lx==12)&&(sn==1)) {
       digitalWrite(swh,1);delay(200);
       smoker = analogRead(analogsensor);
       digitalWrite(swh,0);delay(100);lx=0;
      if (smoker>=sx){
   ser=1; digitalWrite(serin, ser); writerelays(sr);
   }}
   
 if ((analogRead(analogsensor)>=kx)&&(kn==1)){
      ser=1;digitalWrite(serin,ser);writerelays(kr);
     }

WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  
  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  
 /* // Match the request
  int val;
  if (req.indexOf("/gpio/0") != -1)
    val = 0;
  else if (req.indexOf("/gpio/1") != -1)
    val = 1;
  else {
    Serial.println("invalid request");
    client.stop();
    return;
  }*/
  
  y=req.substring(5,(y.indexOf("HTTP")-1));
  relays(y);
  
  if (y=="ser"){
      ser=(ser==1)? 0:1;digitalWrite(serin,ser);
     }
     
 else if (y=="temp"){
       if(ds18b20_read(&raw_temp)) {
    temp = (float)raw_temp / 16;     // Convert temperature raw value into degree Celsius (temp in °C = raw/16)
     client.flush();
    client.print(p2(tr,tn,tx,"temp",temp,"Temprature Sensor Setting"));
  }
    }
    
   else if (y=="smoke"){
        digitalWrite(swh,1);delay(200);
       smoker = analogRead(analogsensor);
       digitalWrite(swh,0);delay(100);
          client.flush();
    client.print(p2(sr,sn,sx,"smoke",smoker,"Smoke Sensor Setting"));
     }

  else if (y=="knock"){
       knockr = analogRead(analogsensor);
          client.flush();
    client.print(p2(kr,kn,kx,"knock",smoker,"Vibration Sensor Setting"));
     }
     
   else if (y.indexOf("set") != -1){
    String z[]={"mtj"};
    for(int i=0;i<=11;i++){z[i]=getValue(y,'-',i);}
   if (z[1]=="temp"){
    for(int i=0;i<=7;i++){tr[i]=z[i+4].toInt();}
    tx=z[2].toInt();tn=z[3].toInt() ;
    client.flush();
    client.print(p1());
    }
  if (z[1]=="smoke"){
    for(int i=0;i<=7;i++){sr[i]=z[i+4].toInt() ;}
    sx=z[2].toInt();sn=z[3].toInt();
    client.flush();
    client.print(p1());
    }
    
     if (z[1]=="knock"){
    for(int i=0;i<=7;i++){kr[i]=z[i+4].toInt();}
    kx=z[2].toInt();kn=z[3].toInt();
    client.flush();
    client.print(p1());
    }
     }

     else{
    client.flush();
    client.print(p1());
    }
   /* if (digitalRead(12)==HIGH) {
   ser=1; digitalWrite(serin, ser); writerelays(kr); Serial.print(1);
   }delay(5);
  // Check if a client has connected
  


  // Prepare the response
  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\nGPIO is now ";
  s += (val)?"high":"low";
  s += "</html>\n";

  // Send the response to the client
  client.print(s);
  
  Serial.println("Client disonnected");*/
delay(1);
  // The client will actually be disconnected 
  // when the function returns and 'client' object is detroyed
}

String p1(){
  String fs="HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\
<html>\
 \
<head>\
 <script>\
  var r1="+String(r[0])+",r2="+String(r[1])+",r3="+String(r[2])+",r4="+String(r[3])+",r5="+String(r[4])+",r6="+String(r[5])+",r7="+String(r[6])+",r8="+String(r[7])+",ser="+String(ser)+";\
 </script>\
 <style>.icono-volumeHigh:after{border:2px solid}.icono-volumeHigh:before{border:2px solid}\
 .icono-volumeHigh:after,.icono-volumeHigh:before{position:absolute;top:50%;-webkit-transform:translateY(-50%);-ms-transform:translateY(-50%);transform:translateY(-50%)}\
   .icono-volumeHigh{width:0;height:0;border:7px solid;border-left:none;border-top-color:transparent;border-bottom-color:transparent;padding:6px 3px;box-shadow:inset 4px 0;margin:4px 10px 4px 11px}\
  .icono-volumeHigh{margin:4px 18px 4px 3px}\
  .icono-volumeHigh:after,.icono-volumeHigh:before{width:15px;height:15px;position:absolute;border-radius:50%;border-top-color:transparent;border-bottom-color:transparent;border-left-color:transparent;left:2px;margin:4px 16px 4px 5px}\
 icono-volumeHigh:before{border-style:double;border-width:6px;left:-2px}\
 .icono-volumeHigh{margin:4px 18px 4px 3px}.icono-volumeHigh:after{width:32px;height:32px;left:-7px}\
  .swh{width :300px;margin: auto;margin-top: 10px;}\
        .swhd{border: 3px solid white;width: 100px;cursor: pointer;display: inline;margin-left: 50px;}\
       .son{ background: #99ffcc;width: 50%;}.soff{ background:  #ff6666;width: 50%;}\
</style>\
</head>\
<body style=\"background: #bfbfbf;\">\
 \
 <div style=\"background:#ffd966;font-size: 20px;text-align: center;margin: auto;margin-top: 10px;cursor: pointer; \" onclick=\"location.replace('http://"+ip.toString()+"/temp');\">Temprature Sensor Setting</div>\
<div style=\"background:#ffff66;font-size: 20px;text-align: center;margin: auto;margin-top: 10px;cursor: pointer; \" onclick=\"location.replace('http://"+ip.toString()+"/smoke');\">Smoke Sensor Setting</div>\
<div style=\"background:#b3ff66;font-size: 20px;text-align: center;margin: auto;margin-top: 10px; cursor: pointer; \" onclick=\"location.replace('http://"+ip.toString()+"/knock');\">Vibration Sensor Setting</div>\
\
 <div style=\"font-size: 30px;text-align: center;margin-top: 30px; \">\
<div class=\"swh\"><span style=\"display: inline;\">Switch 1 </span><div class=\"swhd\" onclick=\"location.replace('http://"+ip.toString()+"/r1');\"><span class=\"son\" id=\"n1\">ON</span><span class=\"soff\" id=\"f1\">OFF</span></div></div>\
 <div class=\"swh\"><span style=\"display: inline;\">Switch 2 </span><div class=\"swhd\" onclick=\"location.replace('http://"+ip.toString()+"/r2');\"><span class=\"son\" id=\"n2\" >ON</span><span class=\"soff\" id=\"f2\" >OFF</span></div></div>\
 <div class=\"swh\"><span style=\"display: inline;\">Switch 3 </span><div class=\"swhd\" onclick=\"location.replace('http://"+ip.toString()+"/r3');\"><span class=\"son\" id=\"n3\">ON</span><span class=\"soff\" id=\"f3\">OFF</span></div></div>\
 <div class=\"swh\"><span style=\"display: inline;\">Switch 4 </span><div class=\"swhd\" onclick=\"location.replace('http://"+ip.toString()+"/r4');\"><span class=\"son\"id=\"n4\">ON</span><span class=\"soff\" id=\"f4\">OFF</span></div></div>\
 <div class=\"swh\"><span style=\"display: inline;\">Switch 5 </span><div class=\"swhd\" onclick=\"location.replace('http://"+ip.toString()+"/r5');\"><span class=\"son\" id=\"n5\">ON</span><span class=\"soff\" id=\"f5\" >OFF</span></div></div>\
 <div class=\"swh\"><span style=\"display: inline;\">Switch 6 </span><div class=\"swhd\" onclick=\"location.replace('http://"+ip.toString()+"/r6');\"><span class=\"son\" id=\"n6\">ON</span><span class=\"soff\" id=\"f6\">OFF</span></div></div>\
 <div class=\"swh\"><span style=\"display: inline;\">Switch 7 </span><div class=\"swhd\" onclick=\"location.replace('http://"+ip.toString()+"/r7');\"><span class=\"son\" id=\"n7\">ON</span><span class=\"soff\" id=\"f7\">OFF</span></div></div>\
 <div class=\"swh\"><span style=\"display: inline;\">Switch 8 </span><div class=\"swhd\" onclick=\"location.replace('http://"+ip.toString()+"/r8');\"><span class=\"son\" id=\"n8\">ON</span><span class=\"soff\" id=\"f8\">OFF</span></div></div>\
 </div>\
 <div style=\"margin: auto;margin-top: 50px;cursor: pointer;width: 130px;color: #4c4ce6;font-size: 30px;\" id=\"ser\" onclick=\"location.replace('http://"+ip.toString()+"/ser');\"><span class=\"icono-volumeHigh\"></span><span>Alarm</span></div>\
</body>\
<script>var relay=()=>{\
 var rx=[r1,r2,r3,r4,r5,r6,r7,r8];\
 for(i=1;i<=8;i++){\
 var on =document.getElementById('n'+i);var off =document.getElementById('f'+i);\
 if(rx[(i-1)]==0){ on.style.visibility='hidden' ;off.style.visibility='visible';}else{off.style.visibility='hidden' ;on.style.visibility='visible';}\
 }\
 };\
 relay();\
 document.getElementById('ser').style.color=ser==0? '#4c4ce6':'red';\
 </script>\
</html>"; 
  return fs;
  }

  String p2(int psr[],int psn,int pv,String sens ,int rd,String tit){
  String fs ="HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\
<html>\
 \
<head>\
    <script>var sr1="+String(psr[0])+",sr2="+String(psr[1])+",sr3="+String(psr[2])+",sr4="+String(psr[3])+",sr5="+String(psr[4])+",sr6="+String(psr[5])+",sr7="+String(psr[6])+",sr8="+String(psr[7])+",sn="+String(psn)+",valu="+String(pv)+",sensor='"+sens+"',reading="+String(rd)+";</script>\
    <style>\
        .swh{width :320px;margin: auto;margin-top: 10px;}\
        .swhd{border: 3px solid white;width: 100px;cursor: pointer;display: inline;margin-left: 100px;}\
       .son{ background: #99ffcc;width: 50%;}.snc{ background: white;width: 50%;}.soff{ background:  #ff6666;width: 50%;}\
    </style>\
</head>\
<body style=\"background: #bfbfbf;\">\
    `<div style=\"margin: auto;margin-bottom: 50px;text-align: center;font-size: 32px;background: #ffff00;\">"+tit+"</div>\
<div style=\"width :320px;margin: auto;margin-top: 15px;font-size: 30px;\"><span style=\"display: inline;\">Sensor</span><div class=\"swhd\" onclick=\"location.replace('http://"+ip.toString()+"/r1');\"><span class=\"son\" id=\"n9\">ON</span><span class=\"soff\" id=\"f9\">OFF</span></div></div>\
    <div style=\"width :320px;margin: auto;margin-top: 15px;font-size: 25px;\"><span>Sensor reading : </span><span>"+String(rd)+"</span><span style=\"margin-left: 30px;color: blue;font-size: 17px;cursor: pointer;\" onclick=\"location.replace('http://"+ip.toString()+"/'+sensor);\">Refresh</span></div>\
      <div style=\"width :320px;margin: auto;margin-top: 15px;font-size: 30px;\"><span>Alarm point : </span><input type=\"text\" name=\"alarm\" value=\""+String(pv)+"\" onchange=\"valu=this.value;\" id=\"alarmp\" style=\"width: 80px;font-size: 20px;\"></div>\
    <div style=\"font-size: 20px;text-align: center;margin-top: 30px; \">\
        switchs response on alarm <br/>\
    <div class=\"swh\"><span style=\"display: inline;\"><span>Switch 1 </span><div class=\"swhd\" onclick=\"sr1=(sr1==0)? 1:((sr1==1)? 2:0);relay();\"><span class=\"son\" id=\"n1\">ON</span><span class=\"snc\" id=\"c1\">NC</span><span class=\"soff\" id=\"f1\">OFF</span></div></div>\
    <div class=\"swh\"><span style=\"display: inline;\"><span>Switch 2 </span><div class=\"swhd\" onclick=\"sr2=(sr2==0)? 1:((sr2==1)? 2:0);relay();\"><span class=\"son\" id=\"n2\">ON</span><span class=\"snc\" id=\"c2\">NC</span><span class=\"soff\" id=\"f2\">OFF</span></div></div>\
    <div class=\"swh\"><span style=\"display: inline;\"><span>Switch 3 </span><div class=\"swhd\" onclick=\"sr3=(sr3==0)? 1:((sr3==1)? 2:0);relay();\"><span class=\"son\" id=\"n3\">ON</span><span class=\"snc\" id=\"c3\">NC</span><span class=\"soff\" id=\"f3\">OFF</span></div></div>\
    <div class=\"swh\"><span style=\"display: inline;\"><span>Switch 4 </span><div class=\"swhd\" onclick=\"sr4=(sr4==0)? 1:((sr4==1)? 2:0);relay();\"><span class=\"son\" id=\"n4\">ON</span><span class=\"snc\" id=\"c4\">NC</span><span class=\"soff\" id=\"f4\">OFF</span></div></div>\
    <div class=\"swh\"><span style=\"display: inline;\"><span>Switch 5 </span><div class=\"swhd\" onclick=\"sr5=(sr5==0)? 1:((sr5==1)? 2:0);relay();\"><span class=\"son\" id=\"n5\">ON</span><span class=\"snc\" id=\"c5\">NC</span><span class=\"soff\" id=\"f5\">OFF</span></div></div>\
    <div class=\"swh\"><span style=\"display: inline;\"><span>Switch 6 </span><div class=\"swhd\" onclick=\"sr6=(sr6==0)? 1:((sr6==1)? 2:0);relay();\"><span class=\"son\" id=\"n6\">ON</span><span class=\"snc\" id=\"c6\">NC</span><span class=\"soff\" id=\"f6\">OFF</span></div></div>\
    <div class=\"swh\"><span style=\"display: inline;\"><span>Switch 7 </span><div class=\"swhd\" onclick=\"sr7=(sr7==0)? 1:((sr7==1)? 2:0);relay();\"><span class=\"son\" id=\"n7\">ON</span><span class=\"snc\" id=\"c7\">NC</span><span class=\"soff\" id=\"f7\">OFF</span></div></div>\
    <div class=\"swh\"><span style=\"display: inline;\"><span>Switch 8 </span><div class=\"swhd\" onclick=\"sr8=(sr8==0)? 1:((sr8==1)? 2:0);relay();\"><span class=\"son\" id=\"n8\">ON</span><span class=\"snc\" id=\"c8\">NC</span><span class=\"soff\" id=\"f8\">OFF</span></div></div>\
\
    </div>\
    <div style=\"width: 300px;margin: auto;font-size: 25px;margin-top: 30px;\">\
 <div style=\"float: left;background:green; \" onclick=\"location.replace('http://"+ip.toString()+"');\">back</div>\
 <div style=\"float: right;background:green;\" onclick=\"location.replace('http://"+ip.toString()+"/'+'set-'+sensor+'-'+valu+'-'+sn+'-'+sr1+'-'+sr2+'-'+sr3+'-'+sr4+'-'+sr5+'-'+sr6+'-'+sr7+'-'+sr8);\">save</div>\
    </div>\
\
<script>\
    \
    var relay=()=>{\
 var rx=[sr1,sr2,sr3,sr4,sr5,sr6,sr7,sr8,sn];\
 for(i=1;i<=9;i++){\
 var on =document.getElementById('n'+i), off =document.getElementById('f'+i),nc =document.getElementById('c'+i);\
 if(rx[(i-1)]==0){ on.style.visibility='hidden' ;nc.style.visibility='hidden' ;off.style.visibility='visible';}else if(rx[(i-1)]==1){off.style.visibility='hidden' ;nc.style.visibility='hidden' ;on.style.visibility='visible';}else if(rx[(i-1)]==2){off.style.visibility='hidden' ;nc.style.visibility='visible' ;on.style.visibility='hidden';}\
 }\
 };\
 relay();\
// document.getElementById('alarmp').value=valu;\
//document.getElementById('reading').innerHTML=reading;\
</script>\
</body></html>";
  
return fs;
  }

  String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}




void writerelays(int w[]){
  if (w[0]!=2){digitalWrite(D1,w[0]);}
  if (w[1]!=2){digitalWrite(D2,w[1]);}
  if (w[2]!=2){digitalWrite(D3,w[2]);}
  if (w[3]!=2){digitalWrite(D4,w[3]);}
  if (w[4]!=2){digitalWrite(D5,w[4]);}
  if (w[5]!=2){digitalWrite(D6,w[5]);}
  if (w[6]!=2){digitalWrite(D7,w[6]);}
  if (w[7]!=2){digitalWrite(D8,w[7]);}
}

void relays(String x){
  if(x=="r1"){
    r[0]=(r[0]==0)?1:0; digitalWrite(D1,r[0]);
  }
    else if(x=="r2"){
    r[1]=(r[1]==0)?1:0; digitalWrite(D2,r[1]);
    }
    else if(x=="r3"){
    r[2]=(r[2]==0)?1:0; digitalWrite(D3,r[2]);
    }
   else if(x=="r4"){
    r[3]=(r[3]==0)?1:0; digitalWrite(D4,r[3]);
   }
   else if(x=="r5"){
    r[4]=(r[4]==0)?1:0; digitalWrite(D5,r[4]);
   }
  else if(x=="r6"){
    r[5]=(r[5]==0)?1:0; digitalWrite(D6,r[5]);
  }
   else if(x=="r7"){
    r[6]=(r[6]==0)?1:0; digitalWrite(D7,r[6]);
   }
   else if(x=="r8"){
    r[7]=(r[7]==0)?1:0; digitalWrite(D8,r[7]);
   }

    }

    

bool ds18b20_start(){
  bool ret = 0;
  digitalWrite(DS18B20_PIN, LOW);     // Send reset pulse to the DS18B20 sensor
  pinMode(DS18B20_PIN, OUTPUT);
  delayMicroseconds(500);             // Wait 500 us
  pinMode(DS18B20_PIN, INPUT);
  delayMicroseconds(100);             //wait to read the DS18B20 sensor response
  if (!digitalRead(DS18B20_PIN)) {
    ret = 1;                          // DS18B20 sensor is present
    delayMicroseconds(400);           // Wait 400 us
  }
  return(ret);
}
void ds18b20_write_bit(bool value){
  digitalWrite(DS18B20_PIN, LOW);
  pinMode(DS18B20_PIN, OUTPUT);
  delayMicroseconds(2);
  digitalWrite(DS18B20_PIN, value);
  delayMicroseconds(80);
  pinMode(DS18B20_PIN, INPUT);
  delayMicroseconds(2);
}
 
void ds18b20_write_byte(byte value){
  byte i;
  for(i = 0; i < 8; i++)
    ds18b20_write_bit(bitRead(value, i));
}
 
bool ds18b20_read_bit(void) {
  bool value;
  digitalWrite(DS18B20_PIN, LOW);
  pinMode(DS18B20_PIN, OUTPUT);
  delayMicroseconds(2);
  pinMode(DS18B20_PIN, INPUT);
  delayMicroseconds(5);
  value = digitalRead(DS18B20_PIN);
  delayMicroseconds(100);
  return value;
}
 
byte ds18b20_read_byte(void) {
  byte i, value;
  for(i = 0; i  <8; i++)
    bitWrite(value, i, ds18b20_read_bit());
  return value;
}
 
bool ds18b20_read(int *raw_temp_value) {
  if (!ds18b20_start())                     // Send start pulse
    return(0);                              // Return 0 if error
  ds18b20_write_byte(0xCC);                 // Send skip ROM command
  ds18b20_write_byte(0x44);                 // Send start conversion command
  while(ds18b20_read_byte() == 0);          // Wait for conversion complete
  if (!ds18b20_start())                     // Send start pulse
    return(0);                              // Return 0 if error
  ds18b20_write_byte(0xCC);                 // Send skip ROM command
  ds18b20_write_byte(0xBE);                 // Send read command
  *raw_temp_value = ds18b20_read_byte();    // Read temperature LSB byte and store it on raw_temp_value LSB byte
  *raw_temp_value |= (unsigned int)(ds18b20_read_byte() << 8);     // Read temperature MSB byte and store it on raw_temp_value MSB byte
  return(1);                                // OK --> return 1
}




