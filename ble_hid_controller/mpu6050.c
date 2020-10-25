#include "mpu6050.h"
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "main.h"

static char string_buffer[30];
static uint8_t m_buffer[MPU6050_READ_SIZE];

void read_mpu6050_cb(ret_code_t result, void * p_user_data)
{
    int16_t AccelX 	= ((m_buffer[0]<<8) | m_buffer[1]);
    int16_t AccelY	= ((m_buffer[2]<<8) | m_buffer[3]);
    int16_t AccelZ 	= ((m_buffer[4]<<8) | m_buffer[5]);
    // int16_t GyroX 	= ((m_buffer[8]<<8) | m_buffer[9]);
    // int16_t GyroY 	= ((m_buffer[10]<<8) | m_buffer[11]);
    // int16_t GyroZ 	= ((m_buffer[12]<<8) | m_buffer[13]);
    AccelX >>= 5;
    AccelY >>= 5;
    AccelZ >>= 5;
    // GyroX /= 131;
    // GyroY /= 131;
    // GyroZ /= 131;

    // float AngleX = atanf(AccelX/hypotf(AccelY,AccelZ))*57.29578;
    // float AngleY = atanf(AccelY/hypotf(AccelX,AccelZ))*57.29578;

    float Pitch_f = atanf(AccelX/hypotf(AccelY,AccelZ))*80;
    float Roll_f = atanf(AccelY/hypotf(AccelX,AccelZ))*80;
    int16_t Pitch = (int16_t)Pitch_f;
    int16_t Roll = (int16_t)Roll_f;

	// float Last_Angle=0, Calculated_Angle;
    // if(AccelZ >= 0) Calculated_Angle = 0.93*(Last_Angle-(0.065*GyroY))+ 0.07*AngleX;
    // else Calculated_Angle = 0.93*(Last_Angle+(0.065*GyroY))+ 0.07*AngleX;
    // Last_Angle = Calculated_Angle;
    // int16_t PrintResult = (int16_t)Calculated_Angle;

    // sprintf(string_buffer, "AccelX: %d\r\nAccelY: %d\r\nAccelZ: %d\r\nGyroX: %d\r\nGyroY: %d\r\nGyroZ: %d\r\n\r\nPitch: %d\r\nRoll: %d\r\n\r\nCalculated Angle: %d\r\n",AccelX,AccelY,AccelZ,GyroX,GyroY,GyroZ,Pitch,Roll,PrintResult);
    // App_uart_send_string(strlen(string_buffer), string_buffer);
    sprintf(string_buffer, "Pitch: %d\tRoll: %d",Pitch, Roll);
    App_uart_send_string(strlen(string_buffer), string_buffer);
}

void Read_mpu6050(void)
{
    static uint8_t var_reg[] = {MPU6050_READ_ADDR};
    static app_twi_transfer_t const transfers[] =
    {
        APP_TWI_WRITE(MPU6050_ADDR, var_reg, sizeof(var_reg), APP_TWI_NO_STOP), \
        APP_TWI_READ(MPU6050_ADDR, m_buffer, MPU6050_READ_SIZE, 0)
    };
    static app_twi_transaction_t const transaction =
    {
        .callback            = read_mpu6050_cb,
        .p_user_data         = NULL,
        .p_transfers         = transfers,
        .number_of_transfers = sizeof(transfers) / sizeof(transfers[0])
    };
    Twi_send(&transaction);
}

void Init_mpu6050(void)
{
    static uint8_t pwr_reg[] = {MPU6050_PWR_ADDR, 0};
    static app_twi_transfer_t const transfers[] =
    {
        APP_TWI_WRITE(MPU6050_ADDR, pwr_reg, sizeof(pwr_reg), 0)
    };
    static app_twi_transaction_t const transaction =
    {
        .callback            = NULL,
        .p_user_data         = NULL,
        .p_transfers         = transfers,
        .number_of_transfers = sizeof(transfers) / sizeof(transfers[0])
    };
    Twi_send(&transaction);
}
