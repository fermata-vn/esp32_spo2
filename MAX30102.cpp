// 
// 
// 

#include "MAX30102.h"
#include <Wire.h>

bool MAX30102Class::init()
{
    if (false == writeReg(INTR_ENABLE_1, 0xc0)) // INTR setting
        return false;
    if (false == writeReg(INTR_ENABLE_2, 0x00))
        return false;
    if (false == writeReg(FIFO_WR_PTR, 0x00))  //FIFO_WR_PTR[4:0]
        return false;
    if (false == writeReg(OVF_COUNTER, 0x00))  //OVF_COUNTER[4:0]
        return false;
    if (false == writeReg(FIFO_RD_PTR, 0x00))  //FIFO_RD_PTR[4:0]
        return false;
    if (false == writeReg(FIFO_CONFIG, 0x4f))  //sample avg = 4, fifo rollover=false, fifo almost full = 17
        return false;
    if (false == writeReg(MODE_CONFIG, 0x03))   //0x02 for Red only, 0x03 for SpO2 mode 0x07 multimode LED
        return false;
    if (false == writeReg(SPO2_CONFIG, 0x27))  // SPO2_ADC range = 4096nA, SPO2 sample rate (100 Hz), LED pulseWidth (411uS)
        return false;

    if (false == writeReg(LED1_PA, 0x24))   //Choose value for ~ 7mA for LED1
        return false;
    if (false == writeReg(LED2_PA, 0x24))   // Choose value for ~ 7mA for LED2
        return false;
    if (false == writeReg(PILOT_PA, 0x7f))   // Choose value for ~ 25mA for Pilot LED
        return false;
    return true;
}

bool MAX30102Class::writeReg(max30102_reg_t reg, uint8_t data)
{
    Wire.beginTransmission(_i2c_addr);
    Wire.write((uint8_t)reg);
    Wire.write(data);
    Wire.endTransmission();
    return true;
}

bool MAX30102Class::readReg(max30102_reg_t reg, uint8_t *data)
{
    Wire.beginTransmission(_i2c_addr);
    Wire.write((uint8_t)reg);
    Wire.endTransmission();
    if (1 != Wire.requestFrom(_i2c_addr, (size_t)1, true))
    {
        return false;
    }
    *data = Wire.read();
    return true;
}

bool MAX30102Class::readFifo(uint32_t *red_led, uint32_t *ir_led)
{
    uint8_t dummy;
    readReg(INTR_STATUS_1, &dummy);
    readReg(INTR_STATUS_2, &dummy);

    Wire.beginTransmission(_i2c_addr);
    Wire.write((uint8_t)FIFO_DATA);
    Wire.endTransmission();
    // red[msb],red[mid],red[lsb],ir[msb],ir[mid],ir[lsb]
    // mask with 0x03ffff  
    if (6 != Wire.requestFrom(_i2c_addr, (size_t)6, true))
    {
        return false;
    }

    uint32_t data;
    data = (uint8_t)Wire.read();
    data <<= 8;
    data |= (uint8_t)Wire.read();
    data <<= 8;
    data |= (uint8_t)Wire.read();
    data &= 0x03ffff;
    *red_led = data;

    data = (uint8_t)Wire.read();
    data <<= 8;
    data |= (uint8_t)Wire.read();
    data <<= 8;
    data |= (uint8_t)Wire.read();
    data &= 0x03ffff;
    *ir_led = data;

    return true;
}

bool MAX30102Class::reset(void)
{
    return writeReg(MODE_CONFIG, 0x40);
}


MAX30102Class MAX30102;

