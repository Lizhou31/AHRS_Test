#ifndef __SUPPORT_H
#define __SUPPORT_H

#include "main.h"

#ifdef USE_HAL_DRIVER
extern I2C_HandleTypeDef hi2c1;
extern SPI_HandleTypeDef hspi1;

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

static inline void nRF24_CE_L()
{
    HAL_GPIO_WritePin(NRF_CE_GPIO_Port, NRF_CE_Pin, GPIO_PIN_RESET);
}

static inline void nRF24_CE_H()
{
    HAL_GPIO_WritePin(NRF_CE_GPIO_Port, NRF_CE_Pin, GPIO_PIN_SET);
}

static inline void nRF24_CSN_L()
{
    HAL_GPIO_WritePin(NRF_CSN_GPIO_Port, NRF_CSN_Pin, GPIO_PIN_RESET);
}

static inline void nRF24_CSN_H()
{
    HAL_GPIO_WritePin(NRF_CSN_GPIO_Port, NRF_CSN_Pin, GPIO_PIN_SET);
}

static inline uint8_t nRF24_LL_RW(uint8_t data)
{
    // Wait until TX buffer is empty
    uint8_t result;
    if (HAL_SPI_TransmitReceive(&hspi1, &data, &result, 1, 2000) != HAL_OK)
    {
        Error_Handler();
    };
    return result;
}

static inline void Delay_ms(uint32_t ms) { HAL_Delay(ms); }

#endif //USE_HAL_DRIVER

#endif //__SUPPORT_H