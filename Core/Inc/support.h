#ifndef __SUPPOUT_H
#define __SUPPORT_H
#include "main.h"

#ifdef USE_HAL_DRIVER
extern I2C_HandleTypeDef hi2c1;

static inline void GY85_HAL_WRITE_MEM8(uint8_t *pData, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize)
{
    if (HAL_I2C_Mem_Write(&hi2c1, DevAddress, MemAddress, MemAddSize, pData, 1U, 0xff) != HAL_OK)
    {
        Error_Handler();
    }
}
static inline void GY85_HAL_READ_MEM8(uint8_t *pData, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize)
{
    if (HAL_I2C_Mem_Read(&hi2c1, DevAddress, MemAddress, MemAddSize, pData, 1U, 0xff) != HAL_OK)
    {
        Error_Handler();
    }
}

#endif //USE_HAL_DRIVER

#endif //__SUPPOUT_H