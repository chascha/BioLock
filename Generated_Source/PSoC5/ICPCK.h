/*******************************************************************************
* File Name: ICPCK.h  
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

#if !defined(CY_PINS_ICPCK_H) /* Pins ICPCK_H */
#define CY_PINS_ICPCK_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "ICPCK_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 ICPCK__PORT == 15 && ((ICPCK__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    ICPCK_Write(uint8 value);
void    ICPCK_SetDriveMode(uint8 mode);
uint8   ICPCK_ReadDataReg(void);
uint8   ICPCK_Read(void);
void    ICPCK_SetInterruptMode(uint16 position, uint16 mode);
uint8   ICPCK_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the ICPCK_SetDriveMode() function.
     *  @{
     */
        #define ICPCK_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define ICPCK_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define ICPCK_DM_RES_UP          PIN_DM_RES_UP
        #define ICPCK_DM_RES_DWN         PIN_DM_RES_DWN
        #define ICPCK_DM_OD_LO           PIN_DM_OD_LO
        #define ICPCK_DM_OD_HI           PIN_DM_OD_HI
        #define ICPCK_DM_STRONG          PIN_DM_STRONG
        #define ICPCK_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define ICPCK_MASK               ICPCK__MASK
#define ICPCK_SHIFT              ICPCK__SHIFT
#define ICPCK_WIDTH              1u

/* Interrupt constants */
#if defined(ICPCK__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in ICPCK_SetInterruptMode() function.
     *  @{
     */
        #define ICPCK_INTR_NONE      (uint16)(0x0000u)
        #define ICPCK_INTR_RISING    (uint16)(0x0001u)
        #define ICPCK_INTR_FALLING   (uint16)(0x0002u)
        #define ICPCK_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define ICPCK_INTR_MASK      (0x01u) 
#endif /* (ICPCK__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define ICPCK_PS                     (* (reg8 *) ICPCK__PS)
/* Data Register */
#define ICPCK_DR                     (* (reg8 *) ICPCK__DR)
/* Port Number */
#define ICPCK_PRT_NUM                (* (reg8 *) ICPCK__PRT) 
/* Connect to Analog Globals */                                                  
#define ICPCK_AG                     (* (reg8 *) ICPCK__AG)                       
/* Analog MUX bux enable */
#define ICPCK_AMUX                   (* (reg8 *) ICPCK__AMUX) 
/* Bidirectional Enable */                                                        
#define ICPCK_BIE                    (* (reg8 *) ICPCK__BIE)
/* Bit-mask for Aliased Register Access */
#define ICPCK_BIT_MASK               (* (reg8 *) ICPCK__BIT_MASK)
/* Bypass Enable */
#define ICPCK_BYP                    (* (reg8 *) ICPCK__BYP)
/* Port wide control signals */                                                   
#define ICPCK_CTL                    (* (reg8 *) ICPCK__CTL)
/* Drive Modes */
#define ICPCK_DM0                    (* (reg8 *) ICPCK__DM0) 
#define ICPCK_DM1                    (* (reg8 *) ICPCK__DM1)
#define ICPCK_DM2                    (* (reg8 *) ICPCK__DM2) 
/* Input Buffer Disable Override */
#define ICPCK_INP_DIS                (* (reg8 *) ICPCK__INP_DIS)
/* LCD Common or Segment Drive */
#define ICPCK_LCD_COM_SEG            (* (reg8 *) ICPCK__LCD_COM_SEG)
/* Enable Segment LCD */
#define ICPCK_LCD_EN                 (* (reg8 *) ICPCK__LCD_EN)
/* Slew Rate Control */
#define ICPCK_SLW                    (* (reg8 *) ICPCK__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define ICPCK_PRTDSI__CAPS_SEL       (* (reg8 *) ICPCK__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define ICPCK_PRTDSI__DBL_SYNC_IN    (* (reg8 *) ICPCK__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define ICPCK_PRTDSI__OE_SEL0        (* (reg8 *) ICPCK__PRTDSI__OE_SEL0) 
#define ICPCK_PRTDSI__OE_SEL1        (* (reg8 *) ICPCK__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define ICPCK_PRTDSI__OUT_SEL0       (* (reg8 *) ICPCK__PRTDSI__OUT_SEL0) 
#define ICPCK_PRTDSI__OUT_SEL1       (* (reg8 *) ICPCK__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define ICPCK_PRTDSI__SYNC_OUT       (* (reg8 *) ICPCK__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(ICPCK__SIO_CFG)
    #define ICPCK_SIO_HYST_EN        (* (reg8 *) ICPCK__SIO_HYST_EN)
    #define ICPCK_SIO_REG_HIFREQ     (* (reg8 *) ICPCK__SIO_REG_HIFREQ)
    #define ICPCK_SIO_CFG            (* (reg8 *) ICPCK__SIO_CFG)
    #define ICPCK_SIO_DIFF           (* (reg8 *) ICPCK__SIO_DIFF)
#endif /* (ICPCK__SIO_CFG) */

/* Interrupt Registers */
#if defined(ICPCK__INTSTAT)
    #define ICPCK_INTSTAT            (* (reg8 *) ICPCK__INTSTAT)
    #define ICPCK_SNAP               (* (reg8 *) ICPCK__SNAP)
    
	#define ICPCK_0_INTTYPE_REG 		(* (reg8 *) ICPCK__0__INTTYPE)
#endif /* (ICPCK__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_ICPCK_H */


/* [] END OF FILE */
