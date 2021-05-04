/*******************************************************************************
* File Name: ConfirmISR.h
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
#if !defined(CY_ISR_ConfirmISR_H)
#define CY_ISR_ConfirmISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void ConfirmISR_Start(void);
void ConfirmISR_StartEx(cyisraddress address);
void ConfirmISR_Stop(void);

CY_ISR_PROTO(ConfirmISR_Interrupt);

void ConfirmISR_SetVector(cyisraddress address);
cyisraddress ConfirmISR_GetVector(void);

void ConfirmISR_SetPriority(uint8 priority);
uint8 ConfirmISR_GetPriority(void);

void ConfirmISR_Enable(void);
uint8 ConfirmISR_GetState(void);
void ConfirmISR_Disable(void);

void ConfirmISR_SetPending(void);
void ConfirmISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the ConfirmISR ISR. */
#define ConfirmISR_INTC_VECTOR            ((reg32 *) ConfirmISR__INTC_VECT)

/* Address of the ConfirmISR ISR priority. */
#define ConfirmISR_INTC_PRIOR             ((reg8 *) ConfirmISR__INTC_PRIOR_REG)

/* Priority of the ConfirmISR interrupt. */
#define ConfirmISR_INTC_PRIOR_NUMBER      ConfirmISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable ConfirmISR interrupt. */
#define ConfirmISR_INTC_SET_EN            ((reg32 *) ConfirmISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the ConfirmISR interrupt. */
#define ConfirmISR_INTC_CLR_EN            ((reg32 *) ConfirmISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the ConfirmISR interrupt state to pending. */
#define ConfirmISR_INTC_SET_PD            ((reg32 *) ConfirmISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the ConfirmISR interrupt. */
#define ConfirmISR_INTC_CLR_PD            ((reg32 *) ConfirmISR__INTC_CLR_PD_REG)


#endif /* CY_ISR_ConfirmISR_H */


/* [] END OF FILE */
