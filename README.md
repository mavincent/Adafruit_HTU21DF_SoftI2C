# Adafruit_HTU21DF_SoftI2C
Implementation of SoftI2C for the Temp. &amp; Humidity sensor from Adafruit.
```c
#include "Adafruit_HTU21DF_soft.h"
#include "SoftI2CMaster.h"

int sdaPin = 11;
int sclPin = 10;

SoftI2CMaster i2c = SoftI2CMaster( sclPin, sdaPin, 0 );
Adafruit_HTU21DF htu = Adafruit_HTU21DF(&i2c);

...
```

