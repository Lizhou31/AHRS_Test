#include "gy85.h"

void gy85_compass_init(void)
{
    uint8_t data = GY85_COMPASS_NORMAL_CONF | GY85_COMPASS_RATE_75 | GY85_COMPASS_AVE_8;
    GY85_HAL_WRITE_MEM8(&data, GY85_COMPASS_I2CADDR << 1, GY85_COMPASS_CRAADDR, 1U);
    data = GY85_COMPASS_GAIN_1090;
    GY85_HAL_WRITE_MEM8(&data, GY85_COMPASS_I2CADDR << 1, GY85_COMPASS_CRBADDR, 1U);
    data = GY85_COMPASS_MODE_CONT;
    GY85_HAL_WRITE_MEM8(&data, GY85_COMPASS_I2CADDR << 1, GY85_COMPASS_MODEADDR, 1U);
}

static void gy85_compass_fetch(uint8_t *data)
{
    GY85_HAL_READ_MEM8(data, GY85_COMPASS_I2CADDR << 1, GY85_COMPASS_DATA_XMSB, 1U);
    GY85_HAL_READ_MEM8(data + 1, GY85_COMPASS_I2CADDR << 1, GY85_COMPASS_DATA_XLSB, 1U);

    GY85_HAL_READ_MEM8(data + 2, GY85_COMPASS_I2CADDR << 1, GY85_COMPASS_DATA_YMSB, 1U);
    GY85_HAL_READ_MEM8(data + 3, GY85_COMPASS_I2CADDR << 1, GY85_COMPASS_DATA_YLSB, 1U);

    GY85_HAL_READ_MEM8(data + 4, GY85_COMPASS_I2CADDR << 1, GY85_COMPASS_DATA_ZMSB, 1U);
    GY85_HAL_READ_MEM8(data + 5, GY85_COMPASS_I2CADDR << 1, GY85_COMPASS_DATA_ZLSB, 1U);
}

void gy85_compass_getRaw(uint8_t *data)
{
    gy85_compass_fetch(data);
}

void gy85_compass_getData(int16_t *data)
{
    uint8_t rdata[6];
    gy85_compass_fetch(rdata);
    data[0] = ((int16_t)rdata[0] << 8) + (int16_t)rdata[1];
    data[1] = ((int16_t)rdata[2] << 8) + (int16_t)rdata[3];
    data[2] = ((int16_t)rdata[3] << 8) + (int16_t)rdata[5];
}

void gy85_accel_init(void)
{
    uint8_t data = 0x08; // temp test
    GY85_HAL_WRITE_MEM8(&data, GY85_ACCEL_I2CADDR << 1, GY85_ACCEL_PWRADDR, 1U);
}

static void gy85_accel_fetch(uint8_t *data)
{
    GY85_HAL_READ_MEM8(data, GY85_ACCEL_I2CADDR << 1, GY85_ACCEL_DATA_X1, 1U);
    GY85_HAL_READ_MEM8(data + 1, GY85_ACCEL_I2CADDR << 1, GY85_ACCEL_DATA_X0, 1U);

    GY85_HAL_READ_MEM8(data + 2, GY85_ACCEL_I2CADDR << 1, GY85_ACCEL_DATA_Y1, 1U);
    GY85_HAL_READ_MEM8(data + 3, GY85_ACCEL_I2CADDR << 1, GY85_ACCEL_DATA_Y0, 1U);

    GY85_HAL_READ_MEM8(data + 4, GY85_ACCEL_I2CADDR << 1, GY85_ACCEL_DATA_Z1, 1U);
    GY85_HAL_READ_MEM8(data + 5, GY85_ACCEL_I2CADDR << 1, GY85_ACCEL_DATA_Z0, 1U);
}

void gy85_accel_getRaw(uint8_t *data)
{
    gy85_accel_fetch(data);
}

void gy85_accel_getData(int16_t *data)
{
    uint8_t rdata[6];
    gy85_accel_fetch(rdata);
    data[0] = ((int16_t)rdata[0] << 8) + (int16_t)rdata[1];
    data[1] = ((int16_t)rdata[2] << 8) + (int16_t)rdata[3];
    data[2] = ((int16_t)rdata[3] << 8) + (int16_t)rdata[5];
}