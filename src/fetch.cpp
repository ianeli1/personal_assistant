#include <HTTPClient.h>
#include <WiFi.h>
#include <LiquidCrystal_I2C.h>
#include "fetch.h"

extern LiquidCrystal_I2C lcd;

HttpResponse __httpResponse;

HttpResponse fetch(const char *url)
{
    lcd.noBacklight();
    WiFiClient client;
    HTTPClient http;

    free(__httpResponse.payload);

    digitalWrite(LED_BUILTIN, 1);

    http.begin(client, url);

    __httpResponse.status = http.GET();

    if (__httpResponse.status < 300 && __httpResponse.status > 0)
    {
        __httpResponse.payload = strdup(http.getString().c_str());
    }
    else
    {
        __httpResponse.payload = strdup(http.errorToString(__httpResponse.status).c_str());
    }
    digitalWrite(LED_BUILTIN, 0);

    lcd.backlight();
    return __httpResponse;
}