#ifndef __GY85_H
#define __GY85_H

#include "support.h"

#define GY85_ACCEL_I2CADDR 0x53   /*!< ADXL345 - Three axis accelerometer */
#define GY85_COMPASS_I2CADDR 0x1E /*!< HMC5883L — Three axis magnetometer */
#define GY85_GYRO_I2CADDR 0x68    /*!< ITG3205 — Three axis gyroscope */

#define GY85_COMPASS_CRAADDR 0x00   /*!< magnetometer CRA Register Address */
#define GY85_COMPASS_CRBADDR 0x01   /*!< magnetometer CRB Register Address */
#define GY85_COMPASS_MODEADDR 0x02  /*!< magnetometer Mode Register Address */
#define GY85_COMPASS_DATA_XMSB 0x03 /*!< magnetometer DataX MSB Register Address */
#define GY85_COMPASS_DATA_XLSB 0x04 /*!< magnetometer DataX LSB Register Address */
#define GY85_COMPASS_DATA_ZMSB 0x05 /*!< magnetometer DataY MSB Register Address */
#define GY85_COMPASS_DATA_ZLSB 0x06 /*!< magnetometer DataY LSB Register Address */
#define GY85_COMPASS_DATA_YMSB 0x07 /*!< magnetometer DataZ MSB Register Address */
#define GY85_COMPASS_DATA_YLSB 0x08 /*!< magnetometer DataZ LSB Register Address */

#define GY85_ACCEL_PWRADDR 0x2D  /*!< accelerometer POWER_CTL Register Address */
#define GY85_ACCEL_DATA_X0 0x32  /*!< accelerometer DataX LSB Register Address */
#define GY85_ACCEL_DATA_X1 0x33  /*!< accelerometer DataX MSB Register Address */
#define GY85_ACCEL_DATA_Y0 0x34  /*!< accelerometer DataY LSB Register Address */
#define GY85_ACCEL_DATA_Y1 0x35  /*!< accelerometer DataY MSB Register Address */
#define GY85_ACCEL_DATA_Z0 0x36  /*!< accelerometer DataZ LSB Register Address */
#define GY85_ACCEL_DATA_Z1 0x37  /*!< accelerometer DataZ MSB Register Address */
#define GY85_ACCEL_OFFSET_X 0x1E /*!< accelerometer Offset X Register Address */
#define GY85_ACCEL_OFFSET_Y 0x1F /*!< accelerometer Offset Y Register Address */
#define GY85_ACCEL_OFFSET_Z 0x20 /*!< accelerometer Offset Z Register Address */

enum
{
    GY85_COMPASS_NORMAL_CONF = (uint8_t)0x00,
    GY85_COMPASS_POSBIAS_CONF = (uint8_t)0x01,
    GY85_COMPASS_NEGBIAS_CONF = (uint8_t)0x02
};

enum
{
    GY85_COMPASS_RATE_P75 = (uint8_t)0x00 << 2,
    GY85_COMPASS_RATE_1P5 = (uint8_t)0x01 << 2,
    GY85_COMPASS_RATE_3 = (uint8_t)0x02 << 2,
    GY85_COMPASS_RATE_7P5 = (uint8_t)0x03 << 2,
    GY85_COMPASS_RATE_15 = (uint8_t)0x04 << 2,
    GY85_COMAPSS_RATE_30 = (uint8_t)0x05 << 2,
    GY85_COMPASS_RATE_75 = (uint8_t)0x06 << 2
};

enum
{
    GY85_COMPASS_AVE_1 = (uint8_t)0x00 << 5,
    GY85_COMPASS_AVE_2 = (uint8_t)0x01 << 5,
    GY85_COMPASS_AVE_4 = (uint8_t)0x02 << 5,
    GY85_COMPASS_AVE_8 = (uint8_t)0x03 << 5
};

enum
{
    GY85_COMPASS_GAIN_1370 = (uint8_t)0x00 << 5,
    GY85_COMPASS_GAIN_1090 = (uint8_t)0x01 << 5,
    GY85_COMPASS_GAIN_0820 = (uint8_t)0x02 << 5,
    GY85_COMPASS_GAIN_0660 = (uint8_t)0x03 << 5,
    GY85_COMPASS_GAIN_0440 = (uint8_t)0x04 << 5,
    GY85_COMPASS_GAIN_0390 = (uint8_t)0x05 << 5,
    GY85_COMPASS_GAIN_0330 = (uint8_t)0x06 << 5,
    GY85_COMPASS_GAIN_0230 = (uint8_t)0x07 << 5
};

enum
{
    GY85_COMPASS_MODE_CONT = (uint8_t)0x00,
    GY85_COMPASS_MODE_SING = (uint8_t)0x01
};

void gy85_compass_init(void);
void gy85_compass_getRaw(uint8_t *data);
void gy85_compass_getData(int16_t *data);
void gy85_accel_init(void);
void gy85_accel_getRaw(uint8_t *data);
void gy85_accel_getData(int16_t *data);

#endif //__GY85_H
