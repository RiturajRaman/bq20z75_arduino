/*===================================================================================================
 * file          :       bq20z75.ino
 *
 * brief         :       This file contains the arduino sketch for reading and writing to bq20z75 registers.
 *
 * author        :       r.ramanbits@gmail.com
 *
 * copyright     :       The code contained herein is licensed under the GNU General Public License.
 *                       You may obtain a copy of the GNU General Public License Version 2 or later
 *                       at the following locations:
 *                       http://www.opensource.org/licenses/gpl-license.html
 *                       http://www.gnu.org/copyleft/gpl.html
 *=================================================================================================*/


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

//gives values of the individual bytes (2 byte registers)
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

//gives the decimal value as output (for 2 byte registers)
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
