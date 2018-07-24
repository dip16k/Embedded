#ifndef I2C_H
#define I2C_H

typedef unsigned char u8;
// define
extern void i2c_start(void);

extern void i2c_stop(void);

extern void i2c_write(u8 ins);

extern void i2c_ack();

extern void i2c_noack();

extern u8 i2c_read();

extern void i2c_device_write(u8 slave, u8 addr, u8 msg);

extern u8 i2c_device_read(u8 slave, u8 addr);

extern void delay_ms(unsigned char n);

#endif
