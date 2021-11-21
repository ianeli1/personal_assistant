#include <LiquidCrystal_I2C.h>
#include <ArduinoJson.h>
#include "fetch.h"
#include "env.h"
#include <time.h>

extern LiquidCrystal_I2C lcd;
extern DynamicJsonDocument doc;

void drawError(char *errorMsg)
{
}

void drawWeather()
{
    HttpResponse weatherData = fetch(WEATHER_ENDPOINT);
    if (weatherData.status < 200 || weatherData.status >= 300)
    {
        drawError(weatherData.payload);
        return;
    }

    DeserializationError error = deserializeJson(doc, weatherData.payload);

    if (error)
    {
        drawError("Deserialization failed");
        return;
    }
    const char *weatherDesc = doc["weather"][0]["description"];
    const int temp = doc["main"]["temp"];
    const int humidity = doc["main"]["humidity"];
    const time_t time = doc["dt"].as<int>() - (3600 * HOUR_OFFSET);

    char dateBuff[20];

    strftime(dateBuff, sizeof dateBuff, "%b%e @ %R", gmtime(&time));

    lcd.clear();
    lcd.print("Weather");
    lcd.setCursor(0, 1);
    lcd.println(weatherDesc);
    lcd.setCursor(0, 2);
    lcd.print(dateBuff);
    lcd.setCursor(0, 3);
    lcd.printf("%iC %i%%RH", temp, humidity);
}