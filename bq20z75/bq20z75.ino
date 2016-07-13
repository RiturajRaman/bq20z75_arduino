#include <Wire.h>
int count = 0;
int address = 0x0b;  //decimal address of sensor 1

void setup() {
  Serial.begin(9600);
  Wire.begin();     // create a wire object
  Serial.println ("Init done!");
}
 
void loop() {
  Serial.print ("Count = ");
  Serial.print (++count);
  Serial.print (" ");
  Serial.print ("d = ");
  read_expt(address, 0x0d);
  Serial.print (" e = ");
  read_expt(address, 0x0e);
  Serial.print (" 01 = ");
  read_expt(address, 0x01);
  Serial.print (" 02 = ");
  read_expt(address, 0x02);
  Serial.print (" Rem cap = ");
  read_expt(address, 0x0f);
  Serial.print (" Rem time = ");
  read_expt(address, 0x11);
  write(address, 0x01, 0);
  write(address, 0x02, 0x0);
  Serial.println ();
  
  delay(5000);  
}
 

void write(int address, int reg, int data) 
{
  Wire.beginTransmission(address); 
  Wire.write(reg);
  Wire.write(data & 0xff);
  Wire.write ( (data >>8) & 0xff );
  Wire.endTransmission();
}

void read(int address, int reg) 
{
  int val;
  Wire.beginTransmission(address); 
  Wire.write(reg);
  Wire.endTransmission(false);
  Wire.beginTransmission(address);
  Wire.endTransmission();
  Wire.requestFrom (address, 2);
  while(Wire.available())
  {
    val = Wire.read();
    Serial.print (val);
    Serial.print (" ");
  }
  
}

void read_expt(int address, int reg) 
{
  int lsb, msb;
  long value = 0;
  Wire.beginTransmission(address); 
  Wire.write(reg);
  Wire.endTransmission(false);
  Wire.beginTransmission(address);
  Wire.endTransmission();
  Wire.requestFrom (address, 2);
  
    lsb = Wire.read();
    msb = Wire.read();
    value = (msb << 8) | (lsb);
    
  Serial.print (value);
  
}
