#ifndef __MAX6675_H_
#define __MAX6675_H_

#include "Arduino.h"

#define MAX6675_CS 20
#define MAX6675_SO 19
#define MAX6675_SCK 18

class MAX6675{
public:
  MAX6675(int8_t SCLK, int8_t CS, int8_t MISO);

  float readCelsius(void);
  float readFahrenheit(void);

  /*!    @brief  For compatibility with older versions
         @returns Temperature in F or NAN on failure! */
  float readFarenheit(void) { return readFahrenheit(); }

private:
  int8_t sclk, miso, cs;
  uint8_t spiread(void);
};


#endif // !__MAX6675_H_
