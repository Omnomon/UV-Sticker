/*******************************************************************************
* File Name: UVD_1A.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_UVD_1A_ALIASES_H) /* Pins UVD_1A_ALIASES_H */
#define CY_PINS_UVD_1A_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define UVD_1A_0			(UVD_1A__0__PC)
#define UVD_1A_0_PS		(UVD_1A__0__PS)
#define UVD_1A_0_PC		(UVD_1A__0__PC)
#define UVD_1A_0_DR		(UVD_1A__0__DR)
#define UVD_1A_0_SHIFT	(UVD_1A__0__SHIFT)
#define UVD_1A_0_INTR	((uint16)((uint16)0x0003u << (UVD_1A__0__SHIFT*2u)))

#define UVD_1A_INTR_ALL	 ((uint16)(UVD_1A_0_INTR))


#endif /* End Pins UVD_1A_ALIASES_H */


/* [] END OF FILE */