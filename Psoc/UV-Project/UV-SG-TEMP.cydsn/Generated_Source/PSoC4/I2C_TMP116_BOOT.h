/***************************************************************************//**
* \file I2C_TMP116_BOOT.h
* \version 4.0
*
* \brief
*  This file provides constants and parameter values of the bootloader
*  communication APIs for the SCB Component.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2014-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_BOOT_I2C_TMP116_H)
#define CY_SCB_BOOT_I2C_TMP116_H

#include "I2C_TMP116_PVT.h"

#if (I2C_TMP116_SCB_MODE_I2C_INC)
    #include "I2C_TMP116_I2C.h"
#endif /* (I2C_TMP116_SCB_MODE_I2C_INC) */

#if (I2C_TMP116_SCB_MODE_EZI2C_INC)
    #include "I2C_TMP116_EZI2C.h"
#endif /* (I2C_TMP116_SCB_MODE_EZI2C_INC) */

#if (I2C_TMP116_SCB_MODE_SPI_INC || I2C_TMP116_SCB_MODE_UART_INC)
    #include "I2C_TMP116_SPI_UART.h"
#endif /* (I2C_TMP116_SCB_MODE_SPI_INC || I2C_TMP116_SCB_MODE_UART_INC) */


/***************************************
*  Conditional Compilation Parameters
****************************************/

/* Bootloader communication interface enable */
#define I2C_TMP116_BTLDR_COMM_ENABLED ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_I2C_TMP116) || \
                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

/* Enable I2C bootloader communication */
#if (I2C_TMP116_SCB_MODE_I2C_INC)
    #define I2C_TMP116_I2C_BTLDR_COMM_ENABLED     (I2C_TMP116_BTLDR_COMM_ENABLED && \
                                                            (I2C_TMP116_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             I2C_TMP116_I2C_SLAVE_CONST))
#else
     #define I2C_TMP116_I2C_BTLDR_COMM_ENABLED    (0u)
#endif /* (I2C_TMP116_SCB_MODE_I2C_INC) */

/* EZI2C does not support bootloader communication. Provide empty APIs */
#if (I2C_TMP116_SCB_MODE_EZI2C_INC)
    #define I2C_TMP116_EZI2C_BTLDR_COMM_ENABLED   (I2C_TMP116_BTLDR_COMM_ENABLED && \
                                                         I2C_TMP116_SCB_MODE_UNCONFIG_CONST_CFG)
#else
    #define I2C_TMP116_EZI2C_BTLDR_COMM_ENABLED   (0u)
#endif /* (I2C_TMP116_EZI2C_BTLDR_COMM_ENABLED) */

/* Enable SPI bootloader communication */
#if (I2C_TMP116_SCB_MODE_SPI_INC)
    #define I2C_TMP116_SPI_BTLDR_COMM_ENABLED     (I2C_TMP116_BTLDR_COMM_ENABLED && \
                                                            (I2C_TMP116_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             I2C_TMP116_SPI_SLAVE_CONST))
#else
        #define I2C_TMP116_SPI_BTLDR_COMM_ENABLED (0u)
#endif /* (I2C_TMP116_SPI_BTLDR_COMM_ENABLED) */

/* Enable UART bootloader communication */
#if (I2C_TMP116_SCB_MODE_UART_INC)
       #define I2C_TMP116_UART_BTLDR_COMM_ENABLED    (I2C_TMP116_BTLDR_COMM_ENABLED && \
                                                            (I2C_TMP116_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             (I2C_TMP116_UART_RX_DIRECTION && \
                                                              I2C_TMP116_UART_TX_DIRECTION)))
#else
     #define I2C_TMP116_UART_BTLDR_COMM_ENABLED   (0u)
#endif /* (I2C_TMP116_UART_BTLDR_COMM_ENABLED) */

/* Enable bootloader communication */
#define I2C_TMP116_BTLDR_COMM_MODE_ENABLED    (I2C_TMP116_I2C_BTLDR_COMM_ENABLED   || \
                                                     I2C_TMP116_SPI_BTLDR_COMM_ENABLED   || \
                                                     I2C_TMP116_EZI2C_BTLDR_COMM_ENABLED || \
                                                     I2C_TMP116_UART_BTLDR_COMM_ENABLED)


/***************************************
*        Function Prototypes
***************************************/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (I2C_TMP116_I2C_BTLDR_COMM_ENABLED)
    /* I2C Bootloader physical layer functions */
    void I2C_TMP116_I2CCyBtldrCommStart(void);
    void I2C_TMP116_I2CCyBtldrCommStop (void);
    void I2C_TMP116_I2CCyBtldrCommReset(void);
    cystatus I2C_TMP116_I2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus I2C_TMP116_I2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map I2C specific bootloader communication APIs to SCB specific APIs */
    #if (I2C_TMP116_SCB_MODE_I2C_CONST_CFG)
        #define I2C_TMP116_CyBtldrCommStart   I2C_TMP116_I2CCyBtldrCommStart
        #define I2C_TMP116_CyBtldrCommStop    I2C_TMP116_I2CCyBtldrCommStop
        #define I2C_TMP116_CyBtldrCommReset   I2C_TMP116_I2CCyBtldrCommReset
        #define I2C_TMP116_CyBtldrCommRead    I2C_TMP116_I2CCyBtldrCommRead
        #define I2C_TMP116_CyBtldrCommWrite   I2C_TMP116_I2CCyBtldrCommWrite
    #endif /* (I2C_TMP116_SCB_MODE_I2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (I2C_TMP116_I2C_BTLDR_COMM_ENABLED) */


#if defined(CYDEV_BOOTLOADER_IO_COMP) && (I2C_TMP116_EZI2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void I2C_TMP116_EzI2CCyBtldrCommStart(void);
    void I2C_TMP116_EzI2CCyBtldrCommStop (void);
    void I2C_TMP116_EzI2CCyBtldrCommReset(void);
    cystatus I2C_TMP116_EzI2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus I2C_TMP116_EzI2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map EZI2C specific bootloader communication APIs to SCB specific APIs */
    #if (I2C_TMP116_SCB_MODE_EZI2C_CONST_CFG)
        #define I2C_TMP116_CyBtldrCommStart   I2C_TMP116_EzI2CCyBtldrCommStart
        #define I2C_TMP116_CyBtldrCommStop    I2C_TMP116_EzI2CCyBtldrCommStop
        #define I2C_TMP116_CyBtldrCommReset   I2C_TMP116_EzI2CCyBtldrCommReset
        #define I2C_TMP116_CyBtldrCommRead    I2C_TMP116_EzI2CCyBtldrCommRead
        #define I2C_TMP116_CyBtldrCommWrite   I2C_TMP116_EzI2CCyBtldrCommWrite
    #endif /* (I2C_TMP116_SCB_MODE_EZI2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (I2C_TMP116_EZI2C_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (I2C_TMP116_SPI_BTLDR_COMM_ENABLED)
    /* SPI Bootloader physical layer functions */
    void I2C_TMP116_SpiCyBtldrCommStart(void);
    void I2C_TMP116_SpiCyBtldrCommStop (void);
    void I2C_TMP116_SpiCyBtldrCommReset(void);
    cystatus I2C_TMP116_SpiCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus I2C_TMP116_SpiCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map SPI specific bootloader communication APIs to SCB specific APIs */
    #if (I2C_TMP116_SCB_MODE_SPI_CONST_CFG)
        #define I2C_TMP116_CyBtldrCommStart   I2C_TMP116_SpiCyBtldrCommStart
        #define I2C_TMP116_CyBtldrCommStop    I2C_TMP116_SpiCyBtldrCommStop
        #define I2C_TMP116_CyBtldrCommReset   I2C_TMP116_SpiCyBtldrCommReset
        #define I2C_TMP116_CyBtldrCommRead    I2C_TMP116_SpiCyBtldrCommRead
        #define I2C_TMP116_CyBtldrCommWrite   I2C_TMP116_SpiCyBtldrCommWrite
    #endif /* (I2C_TMP116_SCB_MODE_SPI_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (I2C_TMP116_SPI_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (I2C_TMP116_UART_BTLDR_COMM_ENABLED)
    /* UART Bootloader physical layer functions */
    void I2C_TMP116_UartCyBtldrCommStart(void);
    void I2C_TMP116_UartCyBtldrCommStop (void);
    void I2C_TMP116_UartCyBtldrCommReset(void);
    cystatus I2C_TMP116_UartCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus I2C_TMP116_UartCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map UART specific bootloader communication APIs to SCB specific APIs */
    #if (I2C_TMP116_SCB_MODE_UART_CONST_CFG)
        #define I2C_TMP116_CyBtldrCommStart   I2C_TMP116_UartCyBtldrCommStart
        #define I2C_TMP116_CyBtldrCommStop    I2C_TMP116_UartCyBtldrCommStop
        #define I2C_TMP116_CyBtldrCommReset   I2C_TMP116_UartCyBtldrCommReset
        #define I2C_TMP116_CyBtldrCommRead    I2C_TMP116_UartCyBtldrCommRead
        #define I2C_TMP116_CyBtldrCommWrite   I2C_TMP116_UartCyBtldrCommWrite
    #endif /* (I2C_TMP116_SCB_MODE_UART_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (I2C_TMP116_UART_BTLDR_COMM_ENABLED) */

/**
* \addtogroup group_bootloader
* @{
*/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (I2C_TMP116_BTLDR_COMM_ENABLED)
    #if (I2C_TMP116_SCB_MODE_UNCONFIG_CONST_CFG)
        /* Bootloader physical layer functions */
        void I2C_TMP116_CyBtldrCommStart(void);
        void I2C_TMP116_CyBtldrCommStop (void);
        void I2C_TMP116_CyBtldrCommReset(void);
        cystatus I2C_TMP116_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
        cystatus I2C_TMP116_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    #endif /* (I2C_TMP116_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Map SCB specific bootloader communication APIs to common APIs */
    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_I2C_TMP116)
        #define CyBtldrCommStart    I2C_TMP116_CyBtldrCommStart
        #define CyBtldrCommStop     I2C_TMP116_CyBtldrCommStop
        #define CyBtldrCommReset    I2C_TMP116_CyBtldrCommReset
        #define CyBtldrCommWrite    I2C_TMP116_CyBtldrCommWrite
        #define CyBtldrCommRead     I2C_TMP116_CyBtldrCommRead
    #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_I2C_TMP116) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (I2C_TMP116_BTLDR_COMM_ENABLED) */

/** @} group_bootloader */

/***************************************
*           API Constants
***************************************/

/* Timeout unit in milliseconds */
#define I2C_TMP116_WAIT_1_MS  (1u)

/* Return number of bytes to copy into bootloader buffer */
#define I2C_TMP116_BYTES_TO_COPY(actBufSize, bufSize) \
                            ( ((uint32)(actBufSize) < (uint32)(bufSize)) ? \
                                ((uint32) (actBufSize)) : ((uint32) (bufSize)) )

/* Size of Read/Write buffers for I2C bootloader  */
#define I2C_TMP116_I2C_BTLDR_SIZEOF_READ_BUFFER   (64u)
#define I2C_TMP116_I2C_BTLDR_SIZEOF_WRITE_BUFFER  (64u)

/* Byte to byte time interval: calculated basing on current component
* data rate configuration, can be defined in project if required.
*/
#ifndef I2C_TMP116_SPI_BYTE_TO_BYTE
    #define I2C_TMP116_SPI_BYTE_TO_BYTE   (160u)
#endif

/* Byte to byte time interval: calculated basing on current component
* baud rate configuration, can be defined in the project if required.
*/
#ifndef I2C_TMP116_UART_BYTE_TO_BYTE
    #define I2C_TMP116_UART_BYTE_TO_BYTE  (2500u)
#endif /* I2C_TMP116_UART_BYTE_TO_BYTE */

#endif /* (CY_SCB_BOOT_I2C_TMP116_H) */


/* [] END OF FILE */
