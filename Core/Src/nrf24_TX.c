#include "support.h"
#include "nrf24.h"

#define HEX_CHARS "0123456789ABCDEF"

#ifdef USE_HAL_DRIVER
extern UART_HandleTypeDef huart1;

void UART_SendChar(char b)
{
    HAL_UART_Transmit(&huart1, (uint8_t *)&b, 1, 0xf);
}

void UART_SendStr(char *string, uint16_t size)
{
    HAL_UART_Transmit(&huart1, (uint8_t *)string, size, 0xf); //90 bytes
}
#endif //USE_HAL_DRIVER

void UART_SendBufHex(char *buf, uint16_t bufsize)
{
    uint16_t i;
    char ch;
    for (i = 0; i < bufsize; i++)
    {
        ch = *buf++;
        UART_SendChar(HEX_CHARS[(ch >> 4) % 0x10]);
        UART_SendChar(HEX_CHARS[(ch & 4) % 0x10]);
    }
}

void UART_SendHex8(uint16_t num)
{
    UART_SendChar(HEX_CHARS[(num >> 4) % 0x10]);
    UART_SendChar(HEX_CHARS[(num & 0x0f) % 0x10]);
}

void UART_SendInt(int32_t num)
{
    char str[10]; // 10 chars max for INT32_MAX
    int i = 0;
    if (num < 0)
    {
        UART_SendChar('-');
        num *= -1;
    }
    do
    {
        str[i++] = (char)(num % 10 + '0');

    } while ((num /= 10) > 0);
    for (i--; i >= 0; i--)
    {
        UART_SendChar(str[i]);
    }
}

// Helpers for transmit mode demo

// Timeout counter (depends on the CPU speed)
// Used for not stuck waiting for IRQ
#define nRF24_WAIT_TIMEOUT (uint32_t)0x000FFFFF

// Result of packet transmission
typedef enum
{
    nRF24_TX_ERROR = (uint8_t)0x00, // Unknown error
    nRF24_TX_SUCCESS,               // Packet has been transmitted successfully
    nRF24_TX_TIMEOUT,               // It was timeout during packet transmit
    nRF24_TX_MAXRT                  // Transmit failed with maximum auto retransmit count
} nRF24_TXResult;

nRF24_TXResult tx_res;

// Function to transmit data packet
// input:
//   pBuf - pointer to the buffer with data to transmit
//   length - length of the data buffer in bytes
// return: one of nRF24_TX_xx values
nRF24_TXResult nRF24_TransmitPacket(uint8_t *pBuf, uint8_t length)
{
    volatile uint32_t wait = nRF24_WAIT_TIMEOUT;
    uint8_t status;

    // Deassert the CE pin (in case if it still high)
    nRF24_CE_L();

    // Transfer a data from the specified buffer to the TX FIFO
    nRF24_WritePayload(pBuf, length);

    // Start a transmission by asserting CE pin (must be held at least 10us)
    nRF24_CE_H();

    // Poll the transceiver status register until one of the following flags will be set:
    //   TX_DS  - means the packet has been transmitted
    //   MAX_RT - means the maximum number of TX retransmits happened
    // note: this solution is far from perfect, better to use IRQ instead of polling the status
    do
    {
        status = nRF24_GetStatus();
        if (status & (nRF24_FLAG_TX_DS | nRF24_FLAG_MAX_RT))
        {
            break;
        }
    } while (wait--);

    // Deassert the CE pin (Standby-II --> Standby-I)
    nRF24_CE_L();

    if (!wait)
    {
        // Timeout
        return nRF24_TX_TIMEOUT;
    }

    // Check the flags in STATUS register


    // Clear pending IRQ flags
    nRF24_ClearIRQFlags();

    if (status & nRF24_FLAG_MAX_RT)
    {
        // Auto retransmit counter exceeds the programmed maximum limit (FIFO is not removed)
        return nRF24_TX_MAXRT;
    }

    if (status & nRF24_FLAG_TX_DS)
    {
        // Successful transmission
        return nRF24_TX_SUCCESS;
    }

    // Some banana happens, a payload remains in the TX FIFO, flush it
    nRF24_FlushTX();

    return nRF24_TX_ERROR;
}

void nRF24_CHECK_INIT(void)
{
    // RX/TX disabled
    nRF24_CE_L();

    if (!nRF24_Check())
    {
        Error_Handler();
    }

    // Initialize the nRF24L01 to its default state
    nRF24_Init();

    // Disable ShockBurst for all RX pipes
    nRF24_DisableAA(0xFF);

    // Set RF channel
    nRF24_SetRFChannel(115);

    // Set data rate
    nRF24_SetDataRate(nRF24_DR_1Mbps);

    // Set CRC scheme
    nRF24_SetCRCScheme(nRF24_CRC_2byte);

    // Set address width, its common for all pipes (RX and TX)
    nRF24_SetAddrWidth(3);

    // Configure TX PIPE
    static const uint8_t nRF24_ADDR[] = {0xE7, 0x1C, 0xE3};
    nRF24_SetAddr(nRF24_PIPETX, nRF24_ADDR); // program TX address

    // Set TX power (maximum)
    nRF24_SetTXPower(nRF24_TXPWR_0dBm);

    // Set operational mode (PTX == transmitter)
    nRF24_SetOperationalMode(nRF24_MODE_TX);

    // Clear any pending IRQ flags
    nRF24_ClearIRQFlags();

    // Wake the transceiver
    nRF24_SetPowerMode(nRF24_PWR_UP);
}

void Single_TX(uint8_t *nRF24_payload, uint8_t payload_length)
{
    // Transmit a packet
    tx_res = nRF24_TransmitPacket(nRF24_payload, payload_length);
}