/*******************************************************************************
* File Name: Motor.h  
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

#if !defined(CY_PINS_Motor_ALIASES_H) /* Pins Motor_ALIASES_H */
#define CY_PINS_Motor_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define Motor_0			(Motor__0__PC)
#define Motor_0_INTR	((uint16)((uint16)0x0001u << Motor__0__SHIFT))

#define Motor_1			(Motor__1__PC)
#define Motor_1_INTR	((uint16)((uint16)0x0001u << Motor__1__SHIFT))

#define Motor_2			(Motor__2__PC)
#define Motor_2_INTR	((uint16)((uint16)0x0001u << Motor__2__SHIFT))

#define Motor_3			(Motor__3__PC)
#define Motor_3_INTR	((uint16)((uint16)0x0001u << Motor__3__SHIFT))

#define Motor_INTR_ALL	 ((uint16)(Motor_0_INTR| Motor_1_INTR| Motor_2_INTR| Motor_3_INTR))

#endif /* End Pins Motor_ALIASES_H */


/* [] END OF FILE */
