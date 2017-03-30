
/*
  Set_RTC_STM32
  by john.carter3 » 01 Nov 2016 19:13
  http://stm32duino.com/viewtopic.php?f=13&t=1511

*/

#include <time.h>
#include "TimeLib.h"
#include <RTClock.h>
#include <EEPROM.h>

#define CONFIG_CLOCK_BIT_ADRRESS 0
#define CONFIGURED 0

const char *monthName[12] = {
  "Jan", "Feb", "Mar", "Apr", "May", "Jun",
  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

RTClock rt (RTCSEL_LSE); // initialise

tmElements_t tm;

void setup()
{
  bool parse = false;
  bool config = false;

  Serial.begin(115200);
  Serial.println("Set_RTC_STM32");
  if (EEPROM.read(CONFIG_CLOCK_BIT_ADRRESS) != CONFIGURED)
  {
    // get the date and time the compiler was run
    if (getDate(__DATE__) && getTime(__TIME__))
    {
      parse = true;

      // first configure the STM32 RTC with this info
      rt.setTime(makeTime(tm));

      delay(200);

      // second sync TimeLib with STM32 RTC
      setTime(rt.getTime());

      if (timeStatus() == timeSet)
      {
        config = true;

        EEPROM.write(CONFIG_CLOCK_BIT_ADRRESS, CONFIGURED);
      }
    }

    delay(200);

    if (parse && config)
    {
      Serial.print("STM32 RTC configured, Time = ");
      Serial.print(__TIME__);
      Serial.print(", Date = ");
      Serial.println(__DATE__);
    }
    else
    {
      Serial.print("Could not parse info from the compiler, Time = \"");
      Serial.print(__TIME__);
      Serial.print("\", Date = \"");
      Serial.print(__DATE__);
      Serial.println("\"");
    }

  }
  else
  {
    Serial.println("STM32 RTC running...");

    setTime(rt.getTime());
  }
}

void loop()
{
  if (EEPROM.read(CONFIG_CLOCK_BIT_ADRRESS) == CONFIGURED)
  {
    digitalClockDisplay();
  }
  else
  {
    Serial.println("The time has not been set.  Please run the Time");
    Serial.println();
    delay(4000);
  }
  delay(1000);
}

void digitalClockDisplay()
{
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.print(" ");
  Serial.print(day());
  Serial.print(" ");
  Serial.print(month());
  Serial.print(" ");
  Serial.print(year());
  Serial.println();
}

void printDigits(int digits)
{
  // utility function for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if (digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

bool getTime(const char *str)
{
  int Hour, Min, Sec;

  if (sscanf(str, "%d:%d:%d", &Hour, &Min, &Sec) != 3) return false;
  tm.Hour = Hour;
  tm.Minute = Min;
  tm.Second = Sec;
  return true;
}

bool getDate(const char *str)
{
  char Month[12];
  int Day, Year;
  uint8_t monthIndex;

  if (sscanf(str, "%s %d %d", Month, &Day, &Year) != 3) return false;
  for (monthIndex = 0; monthIndex < 12; monthIndex++) {
    if (strcmp(Month, monthName[monthIndex]) == 0) break;
  }
  if (monthIndex >= 12) return false;
  tm.Day = Day;
  tm.Month = monthIndex + 1;
  tm.Year = CalendarYrToTm(Year);
  return true;
}

