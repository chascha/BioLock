/*******************************************************************************
* File Name: DebounceCLK.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_DebounceCLK_H)
#define CY_CLOCK_DebounceCLK_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v2_20 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void DebounceCLK_Start(void) ;
void DebounceCLK_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void DebounceCLK_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void DebounceCLK_StandbyPower(uint8 state) ;
void DebounceCLK_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 DebounceCLK_GetDividerRegister(void) ;
void DebounceCLK_SetModeRegister(uint8 modeBitMask) ;
void DebounceCLK_ClearModeRegister(uint8 modeBitMask) ;
uint8 DebounceCLK_GetModeRegister(void) ;
void DebounceCLK_SetSourceRegister(uint8 clkSource) ;
uint8 DebounceCLK_GetSourceRegister(void) ;
#if defined(DebounceCLK__CFG3)
void DebounceCLK_SetPhaseRegister(uint8 clkPhase) ;
uint8 DebounceCLK_GetPhaseRegister(void) ;
#endif /* defined(DebounceCLK__CFG3) */

#define DebounceCLK_Enable()                       DebounceCLK_Start()
#define DebounceCLK_Disable()                      DebounceCLK_Stop()
#define DebounceCLK_SetDivider(clkDivider)         DebounceCLK_SetDividerRegister(clkDivider, 1u)
#define DebounceCLK_SetDividerValue(clkDivider)    DebounceCLK_SetDividerRegister((clkDivider) - 1u, 1u)
#define DebounceCLK_SetMode(clkMode)               DebounceCLK_SetModeRegister(clkMode)
#define DebounceCLK_SetSource(clkSource)           DebounceCLK_SetSourceRegister(clkSource)
#if defined(DebounceCLK__CFG3)
#define DebounceCLK_SetPhase(clkPhase)             DebounceCLK_SetPhaseRegister(clkPhase)
#define DebounceCLK_SetPhaseValue(clkPhase)        DebounceCLK_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(DebounceCLK__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define DebounceCLK_CLKEN              (* (reg8 *) DebounceCLK__PM_ACT_CFG)
#define DebounceCLK_CLKEN_PTR          ((reg8 *) DebounceCLK__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define DebounceCLK_CLKSTBY            (* (reg8 *) DebounceCLK__PM_STBY_CFG)
#define DebounceCLK_CLKSTBY_PTR        ((reg8 *) DebounceCLK__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define DebounceCLK_DIV_LSB            (* (reg8 *) DebounceCLK__CFG0)
#define DebounceCLK_DIV_LSB_PTR        ((reg8 *) DebounceCLK__CFG0)
#define DebounceCLK_DIV_PTR            ((reg16 *) DebounceCLK__CFG0)

/* Clock MSB divider configuration register. */
#define DebounceCLK_DIV_MSB            (* (reg8 *) DebounceCLK__CFG1)
#define DebounceCLK_DIV_MSB_PTR        ((reg8 *) DebounceCLK__CFG1)

/* Mode and source configuration register */
#define DebounceCLK_MOD_SRC            (* (reg8 *) DebounceCLK__CFG2)
#define DebounceCLK_MOD_SRC_PTR        ((reg8 *) DebounceCLK__CFG2)

#if defined(DebounceCLK__CFG3)
/* Analog clock phase configuration register */
#define DebounceCLK_PHASE              (* (reg8 *) DebounceCLK__CFG3)
#define DebounceCLK_PHASE_PTR          ((reg8 *) DebounceCLK__CFG3)
#endif /* defined(DebounceCLK__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define DebounceCLK_CLKEN_MASK         DebounceCLK__PM_ACT_MSK
#define DebounceCLK_CLKSTBY_MASK       DebounceCLK__PM_STBY_MSK

/* CFG2 field masks */
#define DebounceCLK_SRC_SEL_MSK        DebounceCLK__CFG2_SRC_SEL_MASK
#define DebounceCLK_MODE_MASK          (~(DebounceCLK_SRC_SEL_MSK))

#if defined(DebounceCLK__CFG3)
/* CFG3 phase mask */
#define DebounceCLK_PHASE_MASK         DebounceCLK__CFG3_PHASE_DLY_MASK
#endif /* defined(DebounceCLK__CFG3) */

#endif /* CY_CLOCK_DebounceCLK_H */


/* [] END OF FILE */
