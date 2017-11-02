/*******************************************************************************
* File Name: EN_ML8511.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_EN_ML8511_H) /* Pins EN_ML8511_H */
#define CY_PINS_EN_ML8511_H

#include "cytypes.h"
#include "cyfitter.h"
#include "EN_ML8511_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} EN_ML8511_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   EN_ML8511_Read(void);
void    EN_ML8511_Write(uint8 value);
uint8   EN_ML8511_ReadDataReg(void);
#if defined(EN_ML8511__PC) || (CY_PSOC4_4200L) 
    void    EN_ML8511_SetDriveMode(uint8 mode);
#endif
void    EN_ML8511_SetInterruptMode(uint16 position, uint16 mode);
uint8   EN_ML8511_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void EN_ML8511_Sleep(void); 
void EN_ML8511_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(EN_ML8511__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define EN_ML8511_DRIVE_MODE_BITS        (3)
    #define EN_ML8511_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - EN_ML8511_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the EN_ML8511_SetDriveMode() function.
         *  @{
         */
        #define EN_ML8511_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define EN_ML8511_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define EN_ML8511_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define EN_ML8511_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define EN_ML8511_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define EN_ML8511_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define EN_ML8511_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define EN_ML8511_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define EN_ML8511_MASK               EN_ML8511__MASK
#define EN_ML8511_SHIFT              EN_ML8511__SHIFT
#define EN_ML8511_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in EN_ML8511_SetInterruptMode() function.
     *  @{
     */
        #define EN_ML8511_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define EN_ML8511_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define EN_ML8511_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define EN_ML8511_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(EN_ML8511__SIO)
    #define EN_ML8511_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(EN_ML8511__PC) && (CY_PSOC4_4200L)
    #define EN_ML8511_USBIO_ENABLE               ((uint32)0x80000000u)
    #define EN_ML8511_USBIO_DISABLE              ((uint32)(~EN_ML8511_USBIO_ENABLE))
    #define EN_ML8511_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define EN_ML8511_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define EN_ML8511_USBIO_ENTER_SLEEP          ((uint32)((1u << EN_ML8511_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << EN_ML8511_USBIO_SUSPEND_DEL_SHIFT)))
    #define EN_ML8511_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << EN_ML8511_USBIO_SUSPEND_SHIFT)))
    #define EN_ML8511_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << EN_ML8511_USBIO_SUSPEND_DEL_SHIFT)))
    #define EN_ML8511_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(EN_ML8511__PC)
    /* Port Configuration */
    #define EN_ML8511_PC                 (* (reg32 *) EN_ML8511__PC)
#endif
/* Pin State */
#define EN_ML8511_PS                     (* (reg32 *) EN_ML8511__PS)
/* Data Register */
#define EN_ML8511_DR                     (* (reg32 *) EN_ML8511__DR)
/* Input Buffer Disable Override */
#define EN_ML8511_INP_DIS                (* (reg32 *) EN_ML8511__PC2)

/* Interrupt configuration Registers */
#define EN_ML8511_INTCFG                 (* (reg32 *) EN_ML8511__INTCFG)
#define EN_ML8511_INTSTAT                (* (reg32 *) EN_ML8511__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define EN_ML8511_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(EN_ML8511__SIO)
    #define EN_ML8511_SIO_REG            (* (reg32 *) EN_ML8511__SIO)
#endif /* (EN_ML8511__SIO_CFG) */

/* USBIO registers */
#if !defined(EN_ML8511__PC) && (CY_PSOC4_4200L)
    #define EN_ML8511_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define EN_ML8511_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define EN_ML8511_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define EN_ML8511_DRIVE_MODE_SHIFT       (0x00u)
#define EN_ML8511_DRIVE_MODE_MASK        (0x07u << EN_ML8511_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins EN_ML8511_H */


/* [] END OF FILE */