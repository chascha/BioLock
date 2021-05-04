/*******************************************************************************
* File Name: Forward.h  
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

#if !defined(CY_PINS_Forward_H) /* Pins Forward_H */
#define CY_PINS_Forward_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Forward_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Forward__PORT == 15 && ((Forward__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Forward_Write(uint8 value);
void    Forward_SetDriveMode(uint8 mode);
uint8   Forward_ReadDataReg(void);
uint8   Forward_Read(void);
void    Forward_SetInterruptMode(uint16 position, uint16 mode);
uint8   Forward_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Forward_SetDriveMode() function.
     *  @{
     */
        #define Forward_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Forward_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Forward_DM_RES_UP          PIN_DM_RES_UP
        #define Forward_DM_RES_DWN         PIN_DM_RES_DWN
        #define Forward_DM_OD_LO           PIN_DM_OD_LO
        #define Forward_DM_OD_HI           PIN_DM_OD_HI
        #define Forward_DM_STRONG          PIN_DM_STRONG
        #define Forward_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Forward_MASK               Forward__MASK
#define Forward_SHIFT              Forward__SHIFT
#define Forward_WIDTH              1u

/* Interrupt constants */
#if defined(Forward__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Forward_SetInterruptMode() function.
     *  @{
     */
        #define Forward_INTR_NONE      (uint16)(0x0000u)
        #define Forward_INTR_RISING    (uint16)(0x0001u)
        #define Forward_INTR_FALLING   (uint16)(0x0002u)
        #define Forward_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Forward_INTR_MASK      (0x01u) 
#endif /* (Forward__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Forward_PS                     (* (reg8 *) Forward__PS)
/* Data Register */
#define Forward_DR                     (* (reg8 *) Forward__DR)
/* Port Number */
#define Forward_PRT_NUM                (* (reg8 *) Forward__PRT) 
/* Connect to Analog Globals */                                                  
#define Forward_AG                     (* (reg8 *) Forward__AG)                       
/* Analog MUX bux enable */
#define Forward_AMUX                   (* (reg8 *) Forward__AMUX) 
/* Bidirectional Enable */                                                        
#define Forward_BIE                    (* (reg8 *) Forward__BIE)
/* Bit-mask for Aliased Register Access */
#define Forward_BIT_MASK               (* (reg8 *) Forward__BIT_MASK)
/* Bypass Enable */
#define Forward_BYP                    (* (reg8 *) Forward__BYP)
/* Port wide control signals */                                                   
#define Forward_CTL                    (* (reg8 *) Forward__CTL)
/* Drive Modes */
#define Forward_DM0                    (* (reg8 *) Forward__DM0) 
#define Forward_DM1                    (* (reg8 *) Forward__DM1)
#define Forward_DM2                    (* (reg8 *) Forward__DM2) 
/* Input Buffer Disable Override */
#define Forward_INP_DIS                (* (reg8 *) Forward__INP_DIS)
/* LCD Common or Segment Drive */
#define Forward_LCD_COM_SEG            (* (reg8 *) Forward__LCD_COM_SEG)
/* Enable Segment LCD */
#define Forward_LCD_EN                 (* (reg8 *) Forward__LCD_EN)
/* Slew Rate Control */
#define Forward_SLW                    (* (reg8 *) Forward__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Forward_PRTDSI__CAPS_SEL       (* (reg8 *) Forward__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Forward_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Forward__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Forward_PRTDSI__OE_SEL0        (* (reg8 *) Forward__PRTDSI__OE_SEL0) 
#define Forward_PRTDSI__OE_SEL1        (* (reg8 *) Forward__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Forward_PRTDSI__OUT_SEL0       (* (reg8 *) Forward__PRTDSI__OUT_SEL0) 
#define Forward_PRTDSI__OUT_SEL1       (* (reg8 *) Forward__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Forward_PRTDSI__SYNC_OUT       (* (reg8 *) Forward__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Forward__SIO_CFG)
    #define Forward_SIO_HYST_EN        (* (reg8 *) Forward__SIO_HYST_EN)
    #define Forward_SIO_REG_HIFREQ     (* (reg8 *) Forward__SIO_REG_HIFREQ)
    #define Forward_SIO_CFG            (* (reg8 *) Forward__SIO_CFG)
    #define Forward_SIO_DIFF           (* (reg8 *) Forward__SIO_DIFF)
#endif /* (Forward__SIO_CFG) */

/* Interrupt Registers */
#if defined(Forward__INTSTAT)
    #define Forward_INTSTAT            (* (reg8 *) Forward__INTSTAT)
    #define Forward_SNAP               (* (reg8 *) Forward__SNAP)
    
	#define Forward_0_INTTYPE_REG 		(* (reg8 *) Forward__0__INTTYPE)
#endif /* (Forward__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Forward_H */


/* [] END OF FILE */
