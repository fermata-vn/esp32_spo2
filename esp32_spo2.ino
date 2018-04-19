

#include "MAX30102.h"
#include <Wire.h>

#define I2C_SDA 16
#define I2C_SCL 22
#define LED     23
#define MAX30102_INT_PIN 34

void setup()
{
    Serial.begin(115200);
    Wire.begin(I2C_SDA, I2C_SCL);
    pinMode(LED, OUTPUT);
    //delay(100);
    while (!Serial);
    Serial.println("hello");

    pinMode(MAX30102_INT_PIN, INPUT);
    MAX30102.reset();
    delay(1000);
    uint8_t dummy;
    MAX30102.readReg(INTR_STATUS_1, &dummy); // read to clear interrupt
    MAX30102.init();
}

void loop()
{
    digitalWrite(LED, HIGH);
    delay(250);
    digitalWrite(LED, LOW);
    delay(250);

    uint32_t red, ir;
    while (1)
    {
        MAX30102.readFifo(&red, &ir);
        Serial.printf("%8d %8d\n", red, ir);
    }
}
