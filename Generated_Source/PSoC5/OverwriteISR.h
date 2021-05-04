/*******************************************************************************
* File Name: OverwriteISR.h
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
#if !defined(CY_ISR_OverwriteISR_H)
#define CY_ISR_OverwriteISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void OverwriteISR_Start(void);
void OverwriteISR_StartEx(cyisraddress address);
void OverwriteISR_Stop(void);

CY_ISR_PROTO(OverwriteISR_Interrupt);

void OverwriteISR_SetVector(cyisraddress address);
cyisraddress OverwriteISR_GetVector(void);

void OverwriteISR_SetPriority(uint8 priority);
uint8 OverwriteISR_GetPriority(void);

void OverwriteISR_Enable(void);
uint8 OverwriteISR_GetState(void);
void OverwriteISR_Disable(void);

void OverwriteISR_SetPending(void);
void OverwriteISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the OverwriteISR ISR. */
#define OverwriteISR_INTC_VECTOR            ((reg32 *) OverwriteISR__INTC_VECT)

/* Address of the OverwriteISR ISR priority. */
#define OverwriteISR_INTC_PRIOR             ((reg8 *) OverwriteISR__INTC_PRIOR_REG)

/* Priority of the OverwriteISR interrupt. */
#define OverwriteISR_INTC_PRIOR_NUMBER      OverwriteISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable OverwriteISR interrupt. */
#define OverwriteISR_INTC_SET_EN            ((reg32 *) OverwriteISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the OverwriteISR interrupt. */
#define OverwriteISR_INTC_CLR_EN            ((reg32 *) OverwriteISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the OverwriteISR interrupt state to pending. */
#define OverwriteISR_INTC_SET_PD            ((reg32 *) OverwriteISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the OverwriteISR interrupt. */
#define OverwriteISR_INTC_CLR_PD            ((reg32 *) OverwriteISR__INTC_CLR_PD_REG)


#endif /* CY_ISR_OverwriteISR_H */


/* [] END OF FILE */
