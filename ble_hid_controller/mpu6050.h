#ifndef MPU6050_H__
#define MPU6050_H__

#include "app_twi.h"

#define MPU6050_ADDR        (0x68U)
#define MPU6050_PWR_ADDR    (0x6BU)
#define MPU6050_READ_ADDR   (0x3BU)
#define MPU6050_READ_SIZE   (14U)

// Init MPU6050
void Init_mpu6050(void);
// Read from MPU6050
void Read_mpu6050(void);

#endif // MPU6050_H__
