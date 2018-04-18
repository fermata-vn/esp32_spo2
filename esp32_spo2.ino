

#include <Wire.h>

#define I2C_SDA 16
#define I2C_SCL 22
#define LED     23

void setup()
{
    Serial.begin(115200);
    Wire.begin(I2C_SDA, I2C_SCL);
    pinMode(LED, OUTPUT);
    //delay(100);
    while (!Serial);
    Serial.println("hello");
}

void loop()
{
    digitalWrite(LED, HIGH);
    delay(250);
    digitalWrite(LED, LOW);
    delay(250);
}
