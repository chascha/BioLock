/*******************************************************************************
* File Name: CycleISR.c  
* Version 1.71
*
*  Description:
*   API for controlling the state of an interrupt.
*
*
*  Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/


#include <cydevice_trm.h>
#include <CyLib.h>
#include <CycleISR.h>
#include "cyapicallbacks.h"

#if !defined(CycleISR__REMOVED) /* Check for removal by optimization */

/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START CycleISR_intc` */
    volatile uint8 FPSID;
    volatile uint8 FPSmPos;
    volatile unsigned int mPos;
    volatile char mFlag;
    uint8 addre = 0x00;
    uint8 readPos;
    
    #include "stdio.h"
    #include "UART.h"
    #include "I2C.h"
    #include "LCD_I2C_FUNCS.h"

    
   
/* `#END` */

#ifndef CYINT_IRQ_BASE
#define CYINT_IRQ_BASE      16
#endif /* CYINT_IRQ_BASE */
#ifndef CYINT_VECT_TABLE
#define CYINT_VECT_TABLE    ((cyisraddress **) CYREG_NVIC_VECT_OFFSET)
#endif /* CYINT_VECT_TABLE */

/* Declared in startup, used to set unused interrupts to. */
CY_ISR_PROTO(IntDefaultHandler);


/*******************************************************************************
* Function Name: CycleISR_Start
********************************************************************************
*
* Summary:
*  Set up the interrupt and enable it. This function disables the interrupt, 
*  sets the default interrupt vector, sets the priority from the value in the
*  Design Wide Resources Interrupt Editor, then enables the interrupt to the 
*  interrupt controller.
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
void CycleISR_Start(void)
{
    /* For all we know the interrupt is active. */
    CycleISR_Disable();

    /* Set the ISR to point to the CycleISR Interrupt. */
    CycleISR_SetVector(&CycleISR_Interrupt);

    /* Set the priority. */
    CycleISR_SetPriority((uint8)CycleISR_INTC_PRIOR_NUMBER);

    /* Enable it. */
    CycleISR_Enable();
}


/*******************************************************************************
* Function Name: CycleISR_StartEx
********************************************************************************
*
* Summary:
*  Sets up the interrupt and enables it. This function disables the interrupt,
*  sets the interrupt vector based on the address passed in, sets the priority 
*  from the value in the Design Wide Resources Interrupt Editor, then enables 
*  the interrupt to the interrupt controller.
*  
*  When defining ISR functions, the CY_ISR and CY_ISR_PROTO macros should be 
*  used to provide consistent definition across compilers:
*  
*  Function definition example:
*   CY_ISR(MyISR)
*   {
*   }
*   Function prototype example:
*   CY_ISR_PROTO(MyISR);
*
* Parameters:  
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void CycleISR_StartEx(cyisraddress address)
{
    /* For all we know the interrupt is active. */
    CycleISR_Disable();

    /* Set the ISR to point to the CycleISR Interrupt. */
    CycleISR_SetVector(address);

    /* Set the priority. */
    CycleISR_SetPriority((uint8)CycleISR_INTC_PRIOR_NUMBER);

    /* Enable it. */
    CycleISR_Enable();
}


/*******************************************************************************
* Function Name: CycleISR_Stop
********************************************************************************
*
* Summary:
*   Disables and removes the interrupt.
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
void CycleISR_Stop(void)
{
    /* Disable this interrupt. */
    CycleISR_Disable();

    /* Set the ISR to point to the passive one. */
    CycleISR_SetVector(&IntDefaultHandler);
}


/*******************************************************************************
* Function Name: CycleISR_Interrupt
********************************************************************************
*
* Summary:
*   The default Interrupt Service Routine for CycleISR.
*
*   Add custom code between the coments to keep the next version of this file
*   from over writting your code.
*
* Parameters:  
*
* Return:
*   None
*
*******************************************************************************/
CY_ISR(CycleISR_Interrupt)
{
    #ifdef CycleISR_INTERRUPT_INTERRUPT_CALLBACK
        CycleISR_Interrupt_InterruptCallback();
    #endif /* CycleISR_INTERRUPT_INTERRUPT_CALLBACK */ 

    /*  Place your Interrupt code here. */
    /* `#START CycleISR_Interrupt` */
    char a[2];
    char addr[1];
    char mpos[1];
    char cpos[1];
    I2C_Start();
        // LOOPING THRU EEPROM UNTIL VALID mPos IS FOUND //
        if(addre < 10)
        {
            
            I2C_MasterWriteBuf(0b01010000, &addre, 1, I2C_MODE_COMPLETE_XFER);
            while (!(I2C_MasterStatus() & I2C_MSTAT_WR_CMPLT));
            I2C_MasterClearStatus();
            CyDelay(5);

            I2C_MasterReadBuf(0b01010000, &readPos, 1, I2C_MODE_COMPLETE_XFER);
            while (!(I2C_MasterStatus() & I2C_MSTAT_RD_CMPLT));
            I2C_MasterClearStatus();
            
            LCD_I2C_clear();
            
            LCD_I2C_setCursor(0,0);
            LCD_I2C_print("ID: ");
            sprintf(addr, "%d", addre);
            LCD_I2C_print(addr);
            
            LCD_I2C_setCursor(6,0);
            LCD_I2C_print("rPos: ");
            sprintf(mpos, "%d", readPos);
            LCD_I2C_print(mpos);
            
            LCD_I2C_setCursor(0,1);
            LCD_I2C_print("cPos: ");
            sprintf(cpos, "%d", mPos);
            LCD_I2C_print(cpos);

            FPSID = addre;
            FPSmPos = readPos;
            addre++;
        }
        else
        {
            addre = 0;
            I2C_Stop();
        }
        
        
    /*
        Read until valid id is found, when found, read data
        Reads and Displays, does not set motor position or unlock yet.
    
        ID:
        Motor Position:
    
    
    */
    
    /* `#END` */
}


/*******************************************************************************
* Function Name: CycleISR_SetVector
********************************************************************************
*
* Summary:
*   Change the ISR vector for the Interrupt. Note calling CycleISR_Start
*   will override any effect this method would have had. To set the vector 
*   before the component has been started use CycleISR_StartEx instead.
* 
*   When defining ISR functions, the CY_ISR and CY_ISR_PROTO macros should be 
*   used to provide consistent definition across compilers:
*
*   Function definition example:
*   CY_ISR(MyISR)
*   {
*   }
*
*   Function prototype example:
*     CY_ISR_PROTO(MyISR);
*
* Parameters:
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void CycleISR_SetVector(cyisraddress address)
{
    cyisraddress * ramVectorTable;

    ramVectorTable = (cyisraddress *) *CYINT_VECT_TABLE;

    ramVectorTable[CYINT_IRQ_BASE + (uint32)CycleISR__INTC_NUMBER] = address;
}


/*******************************************************************************
* Function Name: CycleISR_GetVector
********************************************************************************
*
* Summary:
*   Gets the "address" of the current ISR vector for the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   Address of the ISR in the interrupt vector table.
*
*******************************************************************************/
cyisraddress CycleISR_GetVector(void)
{
    cyisraddress * ramVectorTable;

    ramVectorTable = (cyisraddress *) *CYINT_VECT_TABLE;

    return ramVectorTable[CYINT_IRQ_BASE + (uint32)CycleISR__INTC_NUMBER];
}


/*******************************************************************************
* Function Name: CycleISR_SetPriority
********************************************************************************
*
* Summary:
*   Sets the Priority of the Interrupt. 
*
*   Note calling CycleISR_Start or CycleISR_StartEx will 
*   override any effect this API would have had. This API should only be called
*   after CycleISR_Start or CycleISR_StartEx has been called. 
*   To set the initial priority for the component, use the Design-Wide Resources
*   Interrupt Editor.
*
*   Note This API has no effect on Non-maskable interrupt NMI).
*
* Parameters:
*   priority: Priority of the interrupt, 0 being the highest priority
*             PSoC 3 and PSoC 5LP: Priority is from 0 to 7.
*             PSoC 4: Priority is from 0 to 3.
*
* Return:
*   None
*
*******************************************************************************/
void CycleISR_SetPriority(uint8 priority)
{
    *CycleISR_INTC_PRIOR = priority << 5;
}


/*******************************************************************************
* Function Name: CycleISR_GetPriority
********************************************************************************
*
* Summary:
*   Gets the Priority of the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   Priority of the interrupt, 0 being the highest priority
*    PSoC 3 and PSoC 5LP: Priority is from 0 to 7.
*    PSoC 4: Priority is from 0 to 3.
*
*******************************************************************************/
uint8 CycleISR_GetPriority(void)
{
    uint8 priority;


    priority = *CycleISR_INTC_PRIOR >> 5;

    return priority;
}


/*******************************************************************************
* Function Name: CycleISR_Enable
********************************************************************************
*
* Summary:
*   Enables the interrupt to the interrupt controller. Do not call this function
*   unless ISR_Start() has been called or the functionality of the ISR_Start() 
*   function, which sets the vector and the priority, has been called.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void CycleISR_Enable(void)
{
    /* Enable the general interrupt. */
    *CycleISR_INTC_SET_EN = CycleISR__INTC_MASK;
}


/*******************************************************************************
* Function Name: CycleISR_GetState
********************************************************************************
*
* Summary:
*   Gets the state (enabled, disabled) of the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   1 if enabled, 0 if disabled.
*
*******************************************************************************/
uint8 CycleISR_GetState(void)
{
    /* Get the state of the general interrupt. */
    return ((*CycleISR_INTC_SET_EN & (uint32)CycleISR__INTC_MASK) != 0u) ? 1u:0u;
}


/*******************************************************************************
* Function Name: CycleISR_Disable
********************************************************************************
*
* Summary:
*   Disables the Interrupt in the interrupt controller.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void CycleISR_Disable(void)
{
    /* Disable the general interrupt. */
    *CycleISR_INTC_CLR_EN = CycleISR__INTC_MASK;
}


/*******************************************************************************
* Function Name: CycleISR_SetPending
********************************************************************************
*
* Summary:
*   Causes the Interrupt to enter the pending state, a software method of
*   generating the interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
* Side Effects:
*   If interrupts are enabled and the interrupt is set up properly, the ISR is
*   entered (depending on the priority of this interrupt and other pending 
*   interrupts).
*
*******************************************************************************/
void CycleISR_SetPending(void)
{
    *CycleISR_INTC_SET_PD = CycleISR__INTC_MASK;
}


/*******************************************************************************
* Function Name: CycleISR_ClearPending
********************************************************************************
*
* Summary:
*   Clears a pending interrupt in the interrupt controller.
*
*   Note Some interrupt sources are clear-on-read and require the block 
*   interrupt/status register to be read/cleared with the appropriate block API 
*   (GPIO, UART, and so on). Otherwise the ISR will continue to remain in 
*   pending state even though the interrupt itself is cleared using this API.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void CycleISR_ClearPending(void)
{
    *CycleISR_INTC_CLR_PD = CycleISR__INTC_MASK;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
