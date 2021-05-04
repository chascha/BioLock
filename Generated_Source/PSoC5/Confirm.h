/*******************************************************************************
* File Name: Confirm.h  
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

#if !defined(CY_PINS_Confirm_H) /* Pins Confirm_H */
#define CY_PINS_Confirm_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Confirm_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Confirm__PORT == 15 && ((Confirm__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Confirm_Write(uint8 value);
void    Confirm_SetDriveMode(uint8 mode);
uint8   Confirm_ReadDataReg(void);
uint8   Confirm_Read(void);
void    Confirm_SetInterruptMode(uint16 position, uint16 mode);
uint8   Confirm_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Confirm_SetDriveMode() function.
     *  @{
     */
        #define Confirm_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Confirm_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Confirm_DM_RES_UP          PIN_DM_RES_UP
        #define Confirm_DM_RES_DWN         PIN_DM_RES_DWN
        #define Confirm_DM_OD_LO           PIN_DM_OD_LO
        #define Confirm_DM_OD_HI           PIN_DM_OD_HI
        #define Confirm_DM_STRONG          PIN_DM_STRONG
        #define Confirm_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Confirm_MASK               Confirm__MASK
#define Confirm_SHIFT              Confirm__SHIFT
#define Confirm_WIDTH              1u

/* Interrupt constants */
#if defined(Confirm__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Confirm_SetInterruptMode() function.
     *  @{
     */
        #define Confirm_INTR_NONE      (uint16)(0x0000u)
        #define Confirm_INTR_RISING    (uint16)(0x0001u)
        #define Confirm_INTR_FALLING   (uint16)(0x0002u)
        #define Confirm_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Confirm_INTR_MASK      (0x01u) 
#endif /* (Confirm__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Confirm_PS                     (* (reg8 *) Confirm__PS)
/* Data Register */
#define Confirm_DR                     (* (reg8 *) Confirm__DR)
/* Port Number */
#define Confirm_PRT_NUM                (* (reg8 *) Confirm__PRT) 
/* Connect to Analog Globals */                                                  
#define Confirm_AG                     (* (reg8 *) Confirm__AG)                       
/* Analog MUX bux enable */
#define Confirm_AMUX                   (* (reg8 *) Confirm__AMUX) 
/* Bidirectional Enable */                                                        
#define Confirm_BIE                    (* (reg8 *) Confirm__BIE)
/* Bit-mask for Aliased Register Access */
#define Confirm_BIT_MASK               (* (reg8 *) Confirm__BIT_MASK)
/* Bypass Enable */
#define Confirm_BYP                    (* (reg8 *) Confirm__BYP)
/* Port wide control signals */                                                   
#define Confirm_CTL                    (* (reg8 *) Confirm__CTL)
/* Drive Modes */
#define Confirm_DM0                    (* (reg8 *) Confirm__DM0) 
#define Confirm_DM1                    (* (reg8 *) Confirm__DM1)
#define Confirm_DM2                    (* (reg8 *) Confirm__DM2) 
/* Input Buffer Disable Override */
#define Confirm_INP_DIS                (* (reg8 *) Confirm__INP_DIS)
/* LCD Common or Segment Drive */
#define Confirm_LCD_COM_SEG            (* (reg8 *) Confirm__LCD_COM_SEG)
/* Enable Segment LCD */
#define Confirm_LCD_EN                 (* (reg8 *) Confirm__LCD_EN)
/* Slew Rate Control */
#define Confirm_SLW                    (* (reg8 *) Confirm__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Confirm_PRTDSI__CAPS_SEL       (* (reg8 *) Confirm__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Confirm_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Confirm__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Confirm_PRTDSI__OE_SEL0        (* (reg8 *) Confirm__PRTDSI__OE_SEL0) 
#define Confirm_PRTDSI__OE_SEL1        (* (reg8 *) Confirm__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Confirm_PRTDSI__OUT_SEL0       (* (reg8 *) Confirm__PRTDSI__OUT_SEL0) 
#define Confirm_PRTDSI__OUT_SEL1       (* (reg8 *) Confirm__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Confirm_PRTDSI__SYNC_OUT       (* (reg8 *) Confirm__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Confirm__SIO_CFG)
    #define Confirm_SIO_HYST_EN        (* (reg8 *) Confirm__SIO_HYST_EN)
    #define Confirm_SIO_REG_HIFREQ     (* (reg8 *) Confirm__SIO_REG_HIFREQ)
    #define Confirm_SIO_CFG            (* (reg8 *) Confirm__SIO_CFG)
    #define Confirm_SIO_DIFF           (* (reg8 *) Confirm__SIO_DIFF)
#endif /* (Confirm__SIO_CFG) */

/* Interrupt Registers */
#if defined(Confirm__INTSTAT)
    #define Confirm_INTSTAT            (* (reg8 *) Confirm__INTSTAT)
    #define Confirm_SNAP               (* (reg8 *) Confirm__SNAP)
    
	#define Confirm_0_INTTYPE_REG 		(* (reg8 *) Confirm__0__INTTYPE)
#endif /* (Confirm__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Confirm_H */


/* [] END OF FILE */
