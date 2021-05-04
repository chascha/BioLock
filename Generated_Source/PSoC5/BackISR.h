/*******************************************************************************
* File Name: BackISR.h
* Version 1.71
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_BackISR_H)
#define CY_ISR_BackISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void BackISR_Start(void);
void BackISR_StartEx(cyisraddress address);
void BackISR_Stop(void);

CY_ISR_PROTO(BackISR_Interrupt);

void BackISR_SetVector(cyisraddress address);
cyisraddress BackISR_GetVector(void);

void BackISR_SetPriority(uint8 priority);
uint8 BackISR_GetPriority(void);

void BackISR_Enable(void);
uint8 BackISR_GetState(void);
void BackISR_Disable(void);

void BackISR_SetPending(void);
void BackISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the BackISR ISR. */
#define BackISR_INTC_VECTOR            ((reg32 *) BackISR__INTC_VECT)

/* Address of the BackISR ISR priority. */
#define BackISR_INTC_PRIOR             ((reg8 *) BackISR__INTC_PRIOR_REG)

/* Priority of the BackISR interrupt. */
#define BackISR_INTC_PRIOR_NUMBER      BackISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable BackISR interrupt. */
#define BackISR_INTC_SET_EN            ((reg32 *) BackISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the BackISR interrupt. */
#define BackISR_INTC_CLR_EN            ((reg32 *) BackISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the BackISR interrupt state to pending. */
#define BackISR_INTC_SET_PD            ((reg32 *) BackISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the BackISR interrupt. */
#define BackISR_INTC_CLR_PD            ((reg32 *) BackISR__INTC_CLR_PD_REG)


#endif /* CY_ISR_BackISR_H */


/* [] END OF FILE */
