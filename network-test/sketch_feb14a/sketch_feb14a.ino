#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);
String testd="good";
void setup() {
  
Serial.begin(9600);

 WiFi.mode(WIFI_STA);
 
WiFi.begin("Mahmoud","01007375396"); 

  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
    Serial.println("connecting");
    delay(500);
  }
 server.on("/",appget);
 server.begin();
Serial.println("connected");
Serial.println(WiFi.localIP().toString());

}

void loop() {
  // put your main code here, to run repeatedly:
server.handleClient();
if(Serial.available()){testd=Serial.readString();}

}

void appget(){
appsend();
  }

void appsend(){
server.sendHeader("Access-Control-Allow-Origin","*");
server.send(200,"text","{'rep':'0432','ip' :'"+WiFi.localIP().toString()+"','pid':'control-unit','name':'test device','testd':'"+testd+"'}");
Serial.println("{'rep':'0432','ip' :'"+WiFi.localIP().toString()+"','pid':'control-unit','name':'test device','testd':'"+testd+"'}");
  }
