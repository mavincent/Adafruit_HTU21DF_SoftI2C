/*************************************************** 
  This is a library for the HTU21DF Humidity & Temp Sensor

  Designed specifically to work with the HTU21DF sensor from Adafruit
  ----> https://www.adafruit.com/products/1899

  These displays use I2C to communicate, 2 pins are required to  
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include "Adafruit_HTU21DF_soft.h"
#if defined(__AVR__)
#include <util/delay.h>
#endif

Adafruit_HTU21DF::Adafruit_HTU21DF(SoftI2CMaster* _i2c) {
    i2c = _i2c;
}


boolean Adafruit_HTU21DF::begin() {

  //Wire.begin();
  
  reset();

  i2c->beginTransmission(HTU21DF_I2CADDR);
  i2c->write(HTU21DF_READREG);
  i2c->endTransmission();
  //i2c.requestFrom(HTU21DF_I2CADDR, 1);
  i2c->requestFrom(HTU21DF_I2CADDR);
  return (i2c->readLast() == 0x2); // after reset should be 0x2
}

void Adafruit_HTU21DF::reset(void) {
  i2c->beginTransmission(HTU21DF_I2CADDR);
  i2c->write(HTU21DF_RESET);
  i2c->endTransmission();
  delay(15);
}


float Adafruit_HTU21DF::readTemperature(void) {
  
  // OK lets ready!
  i2c->beginTransmission(HTU21DF_I2CADDR);
  i2c->write(HTU21DF_READTEMP);
  i2c->endTransmission();
  
  delay(50); // add delay between request and actual read!
  
  i2c->requestFrom(HTU21DF_I2CADDR);
  delay(100);
  uint16_t t = i2c->read();
  t <<= 8;
  t |= i2c->read();

  uint8_t crc = i2c->read();

  float temp = t;
  temp *= 175.72;
  temp /= 65536;
  temp -= 46.85;

  return temp;
}
  

float Adafruit_HTU21DF::readHumidity(void) {
  // OK lets ready!
  i2c->beginTransmission(HTU21DF_I2CADDR);
  i2c->write(HTU21DF_READHUM);
  i2c->endTransmission();
  
  delay(50); // add delay between request and actual read!
  i2c->requestFrom(HTU21DF_I2CADDR);

  delay(100);

  uint16_t h = i2c->read();
  h <<= 8;
  h |= i2c->read();

  uint8_t crc = i2c->read();

  float hum = h;
  hum *= 125;
  hum /= 65536;
  hum -= 6;

  return hum;
}



/*********************************************************************/
