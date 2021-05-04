/*******************************************************************************
* File Name: MotorISR.c  
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
#include <MotorISR.h>
#include "cyapicallbacks.h"

#if !defined(MotorISR__REMOVED) /* Check for removal by optimization */

/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START MotorISR_intc` */
    #include "MotorTimer.h"
    #include "Motor.h"
    #include "UART.h"
    #include "stdio.h"
    volatile char mFlag;
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
* Function Name: MotorISR_Start
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
void MotorISR_Start(void)
{
    /* For all we know the interrupt is active. */
    MotorISR_Disable();

    /* Set the ISR to point to the MotorISR Interrupt. */
    MotorISR_SetVector(&MotorISR_Interrupt);

    /* Set the priority. */
    MotorISR_SetPriority((uint8)MotorISR_INTC_PRIOR_NUMBER);

    /* Enable it. */
    MotorISR_Enable();
}


/*******************************************************************************
* Function Name: MotorISR_StartEx
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
void MotorISR_StartEx(cyisraddress address)
{
    /* For all we know the interrupt is active. */
    MotorISR_Disable();

    /* Set the ISR to point to the MotorISR Interrupt. */
    MotorISR_SetVector(address);

    /* Set the priority. */
    MotorISR_SetPriority((uint8)MotorISR_INTC_PRIOR_NUMBER);

    /* Enable it. */
    MotorISR_Enable();
}


/*******************************************************************************
* Function Name: MotorISR_Stop
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
void MotorISR_Stop(void)
{
    /* Disable this interrupt. */
    MotorISR_Disable();

    /* Set the ISR to point to the passive one. */
    MotorISR_SetVector(&IntDefaultHandler);
}


/*******************************************************************************
* Function Name: MotorISR_Interrupt
********************************************************************************
*
* Summary:
*   The default Interrupt Service Routine for MotorISR.
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
CY_ISR(MotorISR_Interrupt)
{
    #ifdef MotorISR_INTERRUPT_INTERRUPT_CALLBACK
        MotorISR_Interrupt_InterruptCallback();
    #endif /* MotorISR_INTERRUPT_INTERRUPT_CALLBACK */ 

    /*  Place your Interrupt code here. */
    /* `#START MotorISR_Interrupt` */
    char a[1];
        if(mFlag == 'f')
        {
            if(Motor_Read() == 0xA)
            {
                Motor_Write(0x9);
            }
            else if(Motor_Read() == 0x9)
            {
                Motor_Write(0x5);   
            }
            else if(Motor_Read() == 0x5)
            {
                Motor_Write(0x6);   
            }
            else
            {
                Motor_Write(0xA);
            }
        }
        else if(mFlag == 'b')
        {
            if(Motor_Read() == 0xA)
            {
                Motor_Write(0x6);
            }
            else if(Motor_Read() == 0x6)
            {
                Motor_Write(0x5);   
            }
            else if(Motor_Read() == 0x5)
            {
                Motor_Write(0x9);   
            }
            else
            {
                Motor_Write(0xA);   
            }
        }
        MotorTimer_ReadStatusRegister();
    /* `#END` */
}


/*******************************************************************************
* Function Name: MotorISR_SetVector
********************************************************************************
*
* Summary:
*   Change the ISR vector for the Interrupt. Note calling MotorISR_Start
*   will override any effect this method would have had. To set the vector 
*   before the component has been started use MotorISR_StartEx instead.
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
void MotorISR_SetVector(cyisraddress address)
{
    cyisraddress * ramVectorTable;

    ramVectorTable = (cyisraddress *) *CYINT_VECT_TABLE;

    ramVectorTable[CYINT_IRQ_BASE + (uint32)MotorISR__INTC_NUMBER] = address;
}


/*******************************************************************************
* Function Name: MotorISR_GetVector
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
cyisraddress MotorISR_GetVector(void)
{
    cyisraddress * ramVectorTable;

    ramVectorTable = (cyisraddress *) *CYINT_VECT_TABLE;

    return ramVectorTable[CYINT_IRQ_BASE + (uint32)MotorISR__INTC_NUMBER];
}


/*******************************************************************************
* Function Name: MotorISR_SetPriority
********************************************************************************
*
* Summary:
*   Sets the Priority of the Interrupt. 
*
*   Note calling MotorISR_Start or MotorISR_StartEx will 
*   override any effect this API would have had. This API should only be called
*   after MotorISR_Start or MotorISR_StartEx has been called. 
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
void MotorISR_SetPriority(uint8 priority)
{
    *MotorISR_INTC_PRIOR = priority << 5;
}


/*******************************************************************************
* Function Name: MotorISR_GetPriority
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
uint8 MotorISR_GetPriority(void)
{
    uint8 priority;


    priority = *MotorISR_INTC_PRIOR >> 5;

    return priority;
}


/*******************************************************************************
* Function Name: MotorISR_Enable
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
void MotorISR_Enable(void)
{
    /* Enable the general interrupt. */
    *MotorISR_INTC_SET_EN = MotorISR__INTC_MASK;
}


/*******************************************************************************
* Function Name: MotorISR_GetState
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
uint8 MotorISR_GetState(void)
{
    /* Get the state of the general interrupt. */
    return ((*MotorISR_INTC_SET_EN & (uint32)MotorISR__INTC_MASK) != 0u) ? 1u:0u;
}


/*******************************************************************************
* Function Name: MotorISR_Disable
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
void MotorISR_Disable(void)
{
    /* Disable the general interrupt. */
    *MotorISR_INTC_CLR_EN = MotorISR__INTC_MASK;
}


/*******************************************************************************
* Function Name: MotorISR_SetPending
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
void MotorISR_SetPending(void)
{
    *MotorISR_INTC_SET_PD = MotorISR__INTC_MASK;
}


/*******************************************************************************
* Function Name: MotorISR_ClearPending
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
void MotorISR_ClearPending(void)
{
    *MotorISR_INTC_CLR_PD = MotorISR__INTC_MASK;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
