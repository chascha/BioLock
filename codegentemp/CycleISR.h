/*******************************************************************************
* File Name: CycleISR.h
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
#if !defined(CY_ISR_CycleISR_H)
#define CY_ISR_CycleISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void CycleISR_Start(void);
void CycleISR_StartEx(cyisraddress address);
void CycleISR_Stop(void);

CY_ISR_PROTO(CycleISR_Interrupt);

void CycleISR_SetVector(cyisraddress address);
cyisraddress CycleISR_GetVector(void);

void CycleISR_SetPriority(uint8 priority);
uint8 CycleISR_GetPriority(void);

void CycleISR_Enable(void);
uint8 CycleISR_GetState(void);
void CycleISR_Disable(void);

void CycleISR_SetPending(void);
void CycleISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the CycleISR ISR. */
#define CycleISR_INTC_VECTOR            ((reg32 *) CycleISR__INTC_VECT)

/* Address of the CycleISR ISR priority. */
#define CycleISR_INTC_PRIOR             ((reg8 *) CycleISR__INTC_PRIOR_REG)

/* Priority of the CycleISR interrupt. */
#define CycleISR_INTC_PRIOR_NUMBER      CycleISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable CycleISR interrupt. */
#define CycleISR_INTC_SET_EN            ((reg32 *) CycleISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the CycleISR interrupt. */
#define CycleISR_INTC_CLR_EN            ((reg32 *) CycleISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the CycleISR interrupt state to pending. */
#define CycleISR_INTC_SET_PD            ((reg32 *) CycleISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the CycleISR interrupt. */
#define CycleISR_INTC_CLR_PD            ((reg32 *) CycleISR__INTC_CLR_PD_REG)


#endif /* CY_ISR_CycleISR_H */


/* [] END OF FILE */
