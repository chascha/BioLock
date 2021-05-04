/*******************************************************************************
* File Name: Cycle.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Cycle_H) /* Pins Cycle_H */
#define CY_PINS_Cycle_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Cycle_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Cycle__PORT == 15 && ((Cycle__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Cycle_Write(uint8 value);
void    Cycle_SetDriveMode(uint8 mode);
uint8   Cycle_ReadDataReg(void);
uint8   Cycle_Read(void);
void    Cycle_SetInterruptMode(uint16 position, uint16 mode);
uint8   Cycle_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Cycle_SetDriveMode() function.
     *  @{
     */
        #define Cycle_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Cycle_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Cycle_DM_RES_UP          PIN_DM_RES_UP
        #define Cycle_DM_RES_DWN         PIN_DM_RES_DWN
        #define Cycle_DM_OD_LO           PIN_DM_OD_LO
        #define Cycle_DM_OD_HI           PIN_DM_OD_HI
        #define Cycle_DM_STRONG          PIN_DM_STRONG
        #define Cycle_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Cycle_MASK               Cycle__MASK
#define Cycle_SHIFT              Cycle__SHIFT
#define Cycle_WIDTH              1u

/* Interrupt constants */
#if defined(Cycle__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Cycle_SetInterruptMode() function.
     *  @{
     */
        #define Cycle_INTR_NONE      (uint16)(0x0000u)
        #define Cycle_INTR_RISING    (uint16)(0x0001u)
        #define Cycle_INTR_FALLING   (uint16)(0x0002u)
        #define Cycle_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Cycle_INTR_MASK      (0x01u) 
#endif /* (Cycle__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Cycle_PS                     (* (reg8 *) Cycle__PS)
/* Data Register */
#define Cycle_DR                     (* (reg8 *) Cycle__DR)
/* Port Number */
#define Cycle_PRT_NUM                (* (reg8 *) Cycle__PRT) 
/* Connect to Analog Globals */                                                  
#define Cycle_AG                     (* (reg8 *) Cycle__AG)                       
/* Analog MUX bux enable */
#define Cycle_AMUX                   (* (reg8 *) Cycle__AMUX) 
/* Bidirectional Enable */                                                        
#define Cycle_BIE                    (* (reg8 *) Cycle__BIE)
/* Bit-mask for Aliased Register Access */
#define Cycle_BIT_MASK               (* (reg8 *) Cycle__BIT_MASK)
/* Bypass Enable */
#define Cycle_BYP                    (* (reg8 *) Cycle__BYP)
/* Port wide control signals */                                                   
#define Cycle_CTL                    (* (reg8 *) Cycle__CTL)
/* Drive Modes */
#define Cycle_DM0                    (* (reg8 *) Cycle__DM0) 
#define Cycle_DM1                    (* (reg8 *) Cycle__DM1)
#define Cycle_DM2                    (* (reg8 *) Cycle__DM2) 
/* Input Buffer Disable Override */
#define Cycle_INP_DIS                (* (reg8 *) Cycle__INP_DIS)
/* LCD Common or Segment Drive */
#define Cycle_LCD_COM_SEG            (* (reg8 *) Cycle__LCD_COM_SEG)
/* Enable Segment LCD */
#define Cycle_LCD_EN                 (* (reg8 *) Cycle__LCD_EN)
/* Slew Rate Control */
#define Cycle_SLW                    (* (reg8 *) Cycle__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Cycle_PRTDSI__CAPS_SEL       (* (reg8 *) Cycle__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Cycle_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Cycle__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Cycle_PRTDSI__OE_SEL0        (* (reg8 *) Cycle__PRTDSI__OE_SEL0) 
#define Cycle_PRTDSI__OE_SEL1        (* (reg8 *) Cycle__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Cycle_PRTDSI__OUT_SEL0       (* (reg8 *) Cycle__PRTDSI__OUT_SEL0) 
#define Cycle_PRTDSI__OUT_SEL1       (* (reg8 *) Cycle__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Cycle_PRTDSI__SYNC_OUT       (* (reg8 *) Cycle__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Cycle__SIO_CFG)
    #define Cycle_SIO_HYST_EN        (* (reg8 *) Cycle__SIO_HYST_EN)
    #define Cycle_SIO_REG_HIFREQ     (* (reg8 *) Cycle__SIO_REG_HIFREQ)
    #define Cycle_SIO_CFG            (* (reg8 *) Cycle__SIO_CFG)
    #define Cycle_SIO_DIFF           (* (reg8 *) Cycle__SIO_DIFF)
#endif /* (Cycle__SIO_CFG) */

/* Interrupt Registers */
#if defined(Cycle__INTSTAT)
    #define Cycle_INTSTAT            (* (reg8 *) Cycle__INTSTAT)
    #define Cycle_SNAP               (* (reg8 *) Cycle__SNAP)
    
	#define Cycle_0_INTTYPE_REG 		(* (reg8 *) Cycle__0__INTTYPE)
#endif /* (Cycle__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Cycle_H */


/* [] END OF FILE */
