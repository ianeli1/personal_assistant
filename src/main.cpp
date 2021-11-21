#include <Arduino.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
#include "fetch.h"
#include "env.h"
#include "weather.h"

LiquidCrystal_I2C lcd(0x27, 20, 4);
DynamicJsonDocument doc(1024);

void setup()
{

  //disable brown out detector
  WRITE_PERI_REG(DR_REG_RTCCNTL_BASE + 0xd4, 0);

  // initialize the LCD
  Wire.begin();
  lcd.begin(20, 4);
  lcd.backlight();
  delay(5000);
  lcd.clear();

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, 0);

  // initialize WiFi
  WiFi.begin(SSID, PASSWORD);
  lcd.setCursor(0, 0);
  lcd.backlight();
  lcd.printf("Connecting to %s", SSID);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  switch (WiFi.status())
  {
  case WL_CONNECTED:
    lcd.print("IP:");
    lcd.print(WiFi.localIP());
    break;
  default:
    lcd.print("An error ocurred!");
  }

  delay(2000);
  lcd.clear();

  drawWeather();
}

void loop()
{
  // Do nothing here...
}
