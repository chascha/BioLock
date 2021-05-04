/*******************************************************************************
* File Name: UpdateTimer_PM.c
* Version 2.80
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "UpdateTimer.h"

static UpdateTimer_backupStruct UpdateTimer_backup;


/*******************************************************************************
* Function Name: UpdateTimer_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  UpdateTimer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void UpdateTimer_SaveConfig(void) 
{
    #if (!UpdateTimer_UsingFixedFunction)
        UpdateTimer_backup.TimerUdb = UpdateTimer_ReadCounter();
        UpdateTimer_backup.InterruptMaskValue = UpdateTimer_STATUS_MASK;
        #if (UpdateTimer_UsingHWCaptureCounter)
            UpdateTimer_backup.TimerCaptureCounter = UpdateTimer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!UpdateTimer_UDB_CONTROL_REG_REMOVED)
            UpdateTimer_backup.TimerControlRegister = UpdateTimer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: UpdateTimer_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  UpdateTimer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void UpdateTimer_RestoreConfig(void) 
{   
    #if (!UpdateTimer_UsingFixedFunction)

        UpdateTimer_WriteCounter(UpdateTimer_backup.TimerUdb);
        UpdateTimer_STATUS_MASK =UpdateTimer_backup.InterruptMaskValue;
        #if (UpdateTimer_UsingHWCaptureCounter)
            UpdateTimer_SetCaptureCount(UpdateTimer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!UpdateTimer_UDB_CONTROL_REG_REMOVED)
            UpdateTimer_WriteControlRegister(UpdateTimer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: UpdateTimer_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  UpdateTimer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void UpdateTimer_Sleep(void) 
{
    #if(!UpdateTimer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(UpdateTimer_CTRL_ENABLE == (UpdateTimer_CONTROL & UpdateTimer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            UpdateTimer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            UpdateTimer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    UpdateTimer_Stop();
    UpdateTimer_SaveConfig();
}


/*******************************************************************************
* Function Name: UpdateTimer_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  UpdateTimer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void UpdateTimer_Wakeup(void) 
{
    UpdateTimer_RestoreConfig();
    #if(!UpdateTimer_UDB_CONTROL_REG_REMOVED)
        if(UpdateTimer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                UpdateTimer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
