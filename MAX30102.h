// MAX30102.h

#ifndef _MAX30102_h
#define _MAX30102_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

typedef enum
{
    INTR_STATUS_1 = 0x00,
    INTR_STATUS_2 = 0x01,
    INTR_ENABLE_1 = 0x02,
    INTR_ENABLE_2 = 0x03,
    FIFO_WR_PTR = 0x04,
    OVF_COUNTER = 0x05,
    FIFO_RD_PTR = 0x06,
    FIFO_DATA = 0x07,
    FIFO_CONFIG = 0x08,
    MODE_CONFIG = 0x09,
    SPO2_CONFIG = 0x0A,
    LED1_PA = 0x0C,
    LED2_PA = 0x0D,
    PILOT_PA = 0x10,
    MULTI_LED_CTRL1 = 0x11,
    MULTI_LED_CTRL2 = 0x12,
    TEMP_INTR = 0x1F,
    TEMP_FRAC = 0x20,
    TEMP_CONFIG = 0x21,
    PROX_INT_THRESH = 0x30,
    REV_ID = 0xFE,
    PART_ID = 0xFF
} max30102_reg_t;



class MAX30102Class
{
 protected:


 public:
	bool init();
    bool writeReg(max30102_reg_t reg, uint8_t data);
    bool readReg(max30102_reg_t reg, uint8_t *data);
    bool readFifo(uint32_t *red_led, uint32_t *ir_led);
    bool reset(void);


private:
    static const uint8_t _i2c_addr = 0x57;
};

extern MAX30102Class MAX30102;

#endif

