/*************************************************** 
  MODIFIED 2105-08 MAV

  This is an example for the HTU21D-F Humidity & Temp Sensor

  Designed specifically to work with the HTU21D-F sensor from Adafruit
  ----> https://www.adafruit.com/products/1899

  These displays use I2C to communicate, *any* 2 pins are required to  
  interface
 ****************************************************/

#include "Adafruit_HTU21DF_soft.h"
#include "SoftI2CMaster.h"

// Connect Vin to 3-5VDC
// Connect GND to ground
// Connect SCL to sclPin 
// Connect SDA to sdaPin

int sdaPin = 11;
int sclPin = 10;

SoftI2CMaster i2c = SoftI2CMaster( sclPin, sdaPin, 0 );
Adafruit_HTU21DF htu = Adafruit_HTU21DF(&i2c);

void setup() {
  Serial.begin(9600);
  Serial.println("HTU21D-F test");
  
  if (!htu.begin()) {
    Serial.println("Couldn't find sensor!");
    while (1);
  }
}


void loop() {
  Serial.print("Temp: "); Serial.print(htu.readTemperature());
  Serial.print("\t\tHum: "); Serial.println(htu.readHumidity());
  delay(500);
}