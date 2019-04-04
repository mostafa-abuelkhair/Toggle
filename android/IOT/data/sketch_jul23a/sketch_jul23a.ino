

int r[]={1,1,1,1,1,1,1,1},sr[]={1,1,1,1,1,1,1,1},tr[]={1,1,1,1,1,1,1,1},kr[]={0,0,0,0,0,0,0,0};
int ser=0,tn=1,tx=800,sn=1,sx=800,kn=1,kx=100;
String vb="dgdglklklkl";
String vsb="dgdglklklkl"+vb+"dfdf";
int smoker = 0;  
int knockr = 0;  
const int analogsensor = A0;
 #define serin   10
 #define DS18B20_PIN   11
int raw_temp;
float temp;
char txt[] = " C ";
int lx=0;
int mx=0;
void setup(void) {
  pinMode(2, OUTPUT);pinMode(3, OUTPUT);pinMode(4, OUTPUT);pinMode(5, OUTPUT);pinMode(6, OUTPUT);pinMode(7, OUTPUT);pinMode(8, OUTPUT);pinMode(9, OUTPUT);pinMode(10, OUTPUT);
   pinMode(12, OUTPUT);pinMode(13, OUTPUT);digitalWrite(12,0);
  Serial.begin(9600);
txt[0] = 223;   

}

void loop(void) {
  lx++;mx++;
  String y="Lbj";
  y=Serial.readString();
  relays(y);

  if (y=="temp"){
       if(ds18b20_read(&raw_temp)) {
    Serial.print("Temperature = ");
    temp = (float)raw_temp / 16;     // Convert temperature raw value into degree Celsius (temp in °C = raw/16)
    Serial.print(temp);              // Print temperature value in degree Celsius
    Serial.print("C");            // Print '°C'
  }
  else {
    Serial.println("Communication Error!");
  }
    }
    
  else if (y=="ser"){
      ser=(ser==1)? 0:1;digitalWrite(serin,ser);
     }
   else if (y=="smoke"){
        digitalWrite(12,1);delay(200);
       smoker = analogRead(analogsensor);
       Serial.print(smoker);
       digitalWrite(12,0);delay(100);
     }

 if ((mx==10)&&(tn==1)) {
   if(ds18b20_read(&raw_temp)) {
    temp = (float)raw_temp / 16; mx=0;    // Convert temperature raw value into degree Celsius (temp in °C = raw/16)
 if (temp>=tx){
      ser=1;digitalWrite(serin,ser);writerelays(tr);
     }}}
  
   
  if ((lx==12)&&(sn==1)) {
       digitalWrite(12,1);delay(200);
       smoker = analogRead(analogsensor);
       digitalWrite(12,0);delay(100);lx=0;
      if (smoker>=sx){
   ser=1; digitalWrite(serin, ser); writerelays(sr);
   }}
   
 if ((analogRead(analogsensor)>=kx)&&(kn==1)){
      ser=1;digitalWrite(serin,ser);writerelays(kr);
     }
   
   /* if (digitalRead(12)==HIGH) {
   ser=1; digitalWrite(serin, ser); writerelays(kr); Serial.print(1);
   }*/delay(5);
}

void writerelays(int w[]){
  digitalWrite(2,w[1]);digitalWrite(3,w[2]);digitalWrite(4,w[3]);digitalWrite(5,w[4]);digitalWrite(6,w[5]);digitalWrite(7,w[6]);digitalWrite(8,w[7]);digitalWrite(9,w[8]);
}

void relays(String x){
  if(x=="r1"){
    r[1]=(r[1]==0)?1:0;
    digitalWrite(2,r[1]);
  }
    else if(x=="r2"){
    r[2]=(r[2]==0)?1:0; digitalWrite(3,r[2]);
    }
    else if(x=="r3"){
    r[3]=(r[3]==0)?1:0; digitalWrite(4,r[3]);
    }
   else if(x=="r4"){
    r[4]=(r[4]==0)?1:0; digitalWrite(5,r[4]);
   }
   else if(x=="r5"){
    r[5]=(r[5]==0)?1:0; digitalWrite(6,r[5]);
   }
  else if(x=="r6"){
    r[6]=(r[6]==0)?1:0; digitalWrite(7,r[6]);
  }
   else if(x=="r7"){
    r[7]=(r[7]==0)?1:0; digitalWrite(8,r[7]);
   }
   else if(x=="r8"){
    r[8]=(r[8]==0)?1:0; digitalWrite(9,r[8]);
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



