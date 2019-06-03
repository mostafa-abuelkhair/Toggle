#include <EEPROM.h>

void setup() {
  // put your setup code here, to run once:
  EEPROM.begin(512);
  delay(10);
Serial.begin(115200);

Serial.println("start");        //read saved data
Serial.println(eep_read(0,100));
Serial.println(eep_read(50,110));
Serial.println(eep_read(111,150));
Serial.println(eep_read(160,200));


eep_write("ssidname-ssidpass",0,100);   //save new data
eep_write("appass",50,110);
eep_write("pname",111,150);
eep_write("key",160,200);



Serial.println("");              //read new saved data
Serial.println("start");
Serial.println(eep_read(0,100));
Serial.println(eep_read(50,110));
Serial.println(eep_read(111,150));
Serial.println(eep_read(160,200));

}

void loop() {
  
delay(5);
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
