/*******************************************************************************
* File Name: UV5_POS.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "UV5_POS.h"

static UV5_POS_BACKUP_STRUCT  UV5_POS_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: UV5_POS_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function applies only to SIO and USBIO pins.
*  It should not be called for GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet UV5_POS_SUT.c usage_UV5_POS_Sleep_Wakeup
*******************************************************************************/
void UV5_POS_Sleep(void)
{
    #if defined(UV5_POS__PC)
        UV5_POS_backup.pcState = UV5_POS_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            UV5_POS_backup.usbState = UV5_POS_CR1_REG;
            UV5_POS_USB_POWER_REG |= UV5_POS_USBIO_ENTER_SLEEP;
            UV5_POS_CR1_REG &= UV5_POS_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(UV5_POS__SIO)
        UV5_POS_backup.sioState = UV5_POS_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        UV5_POS_SIO_REG &= (uint32)(~UV5_POS_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: UV5_POS_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep(). This 
* function applies only to SIO and USBIO pins. It should not be called for
* GPIO or GPIO_OVT pins.
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to UV5_POS_Sleep() for an example usage.
*******************************************************************************/
void UV5_POS_Wakeup(void)
{
    #if defined(UV5_POS__PC)
        UV5_POS_PC = UV5_POS_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            UV5_POS_USB_POWER_REG &= UV5_POS_USBIO_EXIT_SLEEP_PH1;
            UV5_POS_CR1_REG = UV5_POS_backup.usbState;
            UV5_POS_USB_POWER_REG &= UV5_POS_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(UV5_POS__SIO)
        UV5_POS_SIO_REG = UV5_POS_backup.sioState;
    #endif
}


/* [] END OF FILE */