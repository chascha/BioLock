/*******************************************************************************
* File Name: Overwrite.h  
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

#if !defined(CY_PINS_Overwrite_H) /* Pins Overwrite_H */
#define CY_PINS_Overwrite_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Overwrite_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Overwrite__PORT == 15 && ((Overwrite__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Overwrite_Write(uint8 value);
void    Overwrite_SetDriveMode(uint8 mode);
uint8   Overwrite_ReadDataReg(void);
uint8   Overwrite_Read(void);
void    Overwrite_SetInterruptMode(uint16 position, uint16 mode);
uint8   Overwrite_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Overwrite_SetDriveMode() function.
     *  @{
     */
        #define Overwrite_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Overwrite_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Overwrite_DM_RES_UP          PIN_DM_RES_UP
        #define Overwrite_DM_RES_DWN         PIN_DM_RES_DWN
        #define Overwrite_DM_OD_LO           PIN_DM_OD_LO
        #define Overwrite_DM_OD_HI           PIN_DM_OD_HI
        #define Overwrite_DM_STRONG          PIN_DM_STRONG
        #define Overwrite_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Overwrite_MASK               Overwrite__MASK
#define Overwrite_SHIFT              Overwrite__SHIFT
#define Overwrite_WIDTH              1u

/* Interrupt constants */
#if defined(Overwrite__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Overwrite_SetInterruptMode() function.
     *  @{
     */
        #define Overwrite_INTR_NONE      (uint16)(0x0000u)
        #define Overwrite_INTR_RISING    (uint16)(0x0001u)
        #define Overwrite_INTR_FALLING   (uint16)(0x0002u)
        #define Overwrite_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Overwrite_INTR_MASK      (0x01u) 
#endif /* (Overwrite__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Overwrite_PS                     (* (reg8 *) Overwrite__PS)
/* Data Register */
#define Overwrite_DR                     (* (reg8 *) Overwrite__DR)
/* Port Number */
#define Overwrite_PRT_NUM                (* (reg8 *) Overwrite__PRT) 
/* Connect to Analog Globals */                                                  
#define Overwrite_AG                     (* (reg8 *) Overwrite__AG)                       
/* Analog MUX bux enable */
#define Overwrite_AMUX                   (* (reg8 *) Overwrite__AMUX) 
/* Bidirectional Enable */                                                        
#define Overwrite_BIE                    (* (reg8 *) Overwrite__BIE)
/* Bit-mask for Aliased Register Access */
#define Overwrite_BIT_MASK               (* (reg8 *) Overwrite__BIT_MASK)
/* Bypass Enable */
#define Overwrite_BYP                    (* (reg8 *) Overwrite__BYP)
/* Port wide control signals */                                                   
#define Overwrite_CTL                    (* (reg8 *) Overwrite__CTL)
/* Drive Modes */
#define Overwrite_DM0                    (* (reg8 *) Overwrite__DM0) 
#define Overwrite_DM1                    (* (reg8 *) Overwrite__DM1)
#define Overwrite_DM2                    (* (reg8 *) Overwrite__DM2) 
/* Input Buffer Disable Override */
#define Overwrite_INP_DIS                (* (reg8 *) Overwrite__INP_DIS)
/* LCD Common or Segment Drive */
#define Overwrite_LCD_COM_SEG            (* (reg8 *) Overwrite__LCD_COM_SEG)
/* Enable Segment LCD */
#define Overwrite_LCD_EN                 (* (reg8 *) Overwrite__LCD_EN)
/* Slew Rate Control */
#define Overwrite_SLW                    (* (reg8 *) Overwrite__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Overwrite_PRTDSI__CAPS_SEL       (* (reg8 *) Overwrite__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Overwrite_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Overwrite__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Overwrite_PRTDSI__OE_SEL0        (* (reg8 *) Overwrite__PRTDSI__OE_SEL0) 
#define Overwrite_PRTDSI__OE_SEL1        (* (reg8 *) Overwrite__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Overwrite_PRTDSI__OUT_SEL0       (* (reg8 *) Overwrite__PRTDSI__OUT_SEL0) 
#define Overwrite_PRTDSI__OUT_SEL1       (* (reg8 *) Overwrite__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Overwrite_PRTDSI__SYNC_OUT       (* (reg8 *) Overwrite__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Overwrite__SIO_CFG)
    #define Overwrite_SIO_HYST_EN        (* (reg8 *) Overwrite__SIO_HYST_EN)
    #define Overwrite_SIO_REG_HIFREQ     (* (reg8 *) Overwrite__SIO_REG_HIFREQ)
    #define Overwrite_SIO_CFG            (* (reg8 *) Overwrite__SIO_CFG)
    #define Overwrite_SIO_DIFF           (* (reg8 *) Overwrite__SIO_DIFF)
#endif /* (Overwrite__SIO_CFG) */

/* Interrupt Registers */
#if defined(Overwrite__INTSTAT)
    #define Overwrite_INTSTAT            (* (reg8 *) Overwrite__INTSTAT)
    #define Overwrite_SNAP               (* (reg8 *) Overwrite__SNAP)
    
	#define Overwrite_0_INTTYPE_REG 		(* (reg8 *) Overwrite__0__INTTYPE)
#endif /* (Overwrite__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Overwrite_H */


/* [] END OF FILE */
