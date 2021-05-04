/*******************************************************************************
* File Name: MotorCLK.h
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

#if !defined(CY_CLOCK_MotorCLK_H)
#define CY_CLOCK_MotorCLK_H

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

void MotorCLK_Start(void) ;
void MotorCLK_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void MotorCLK_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void MotorCLK_StandbyPower(uint8 state) ;
void MotorCLK_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 MotorCLK_GetDividerRegister(void) ;
void MotorCLK_SetModeRegister(uint8 modeBitMask) ;
void MotorCLK_ClearModeRegister(uint8 modeBitMask) ;
uint8 MotorCLK_GetModeRegister(void) ;
void MotorCLK_SetSourceRegister(uint8 clkSource) ;
uint8 MotorCLK_GetSourceRegister(void) ;
#if defined(MotorCLK__CFG3)
void MotorCLK_SetPhaseRegister(uint8 clkPhase) ;
uint8 MotorCLK_GetPhaseRegister(void) ;
#endif /* defined(MotorCLK__CFG3) */

#define MotorCLK_Enable()                       MotorCLK_Start()
#define MotorCLK_Disable()                      MotorCLK_Stop()
#define MotorCLK_SetDivider(clkDivider)         MotorCLK_SetDividerRegister(clkDivider, 1u)
#define MotorCLK_SetDividerValue(clkDivider)    MotorCLK_SetDividerRegister((clkDivider) - 1u, 1u)
#define MotorCLK_SetMode(clkMode)               MotorCLK_SetModeRegister(clkMode)
#define MotorCLK_SetSource(clkSource)           MotorCLK_SetSourceRegister(clkSource)
#if defined(MotorCLK__CFG3)
#define MotorCLK_SetPhase(clkPhase)             MotorCLK_SetPhaseRegister(clkPhase)
#define MotorCLK_SetPhaseValue(clkPhase)        MotorCLK_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(MotorCLK__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define MotorCLK_CLKEN              (* (reg8 *) MotorCLK__PM_ACT_CFG)
#define MotorCLK_CLKEN_PTR          ((reg8 *) MotorCLK__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define MotorCLK_CLKSTBY            (* (reg8 *) MotorCLK__PM_STBY_CFG)
#define MotorCLK_CLKSTBY_PTR        ((reg8 *) MotorCLK__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define MotorCLK_DIV_LSB            (* (reg8 *) MotorCLK__CFG0)
#define MotorCLK_DIV_LSB_PTR        ((reg8 *) MotorCLK__CFG0)
#define MotorCLK_DIV_PTR            ((reg16 *) MotorCLK__CFG0)

/* Clock MSB divider configuration register. */
#define MotorCLK_DIV_MSB            (* (reg8 *) MotorCLK__CFG1)
#define MotorCLK_DIV_MSB_PTR        ((reg8 *) MotorCLK__CFG1)

/* Mode and source configuration register */
#define MotorCLK_MOD_SRC            (* (reg8 *) MotorCLK__CFG2)
#define MotorCLK_MOD_SRC_PTR        ((reg8 *) MotorCLK__CFG2)

#if defined(MotorCLK__CFG3)
/* Analog clock phase configuration register */
#define MotorCLK_PHASE              (* (reg8 *) MotorCLK__CFG3)
#define MotorCLK_PHASE_PTR          ((reg8 *) MotorCLK__CFG3)
#endif /* defined(MotorCLK__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define MotorCLK_CLKEN_MASK         MotorCLK__PM_ACT_MSK
#define MotorCLK_CLKSTBY_MASK       MotorCLK__PM_STBY_MSK

/* CFG2 field masks */
#define MotorCLK_SRC_SEL_MSK        MotorCLK__CFG2_SRC_SEL_MASK
#define MotorCLK_MODE_MASK          (~(MotorCLK_SRC_SEL_MSK))

#if defined(MotorCLK__CFG3)
/* CFG3 phase mask */
#define MotorCLK_PHASE_MASK         MotorCLK__CFG3_PHASE_DLY_MASK
#endif /* defined(MotorCLK__CFG3) */

#endif /* CY_CLOCK_MotorCLK_H */


/* [] END OF FILE */
