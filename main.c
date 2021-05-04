/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include "stdio.h"

extern volatile char mFlag;
extern volatile unsigned int mPos;
extern volatile int motorTime;
extern volatile uint8 FPSID;
extern volatile uint8 buttonID;
extern volatile uint8 FPSmPos;
extern volatile uint8 cycleFlag;

void zeroEEPROM(uint8 addr)
{
    uint8 arr[2];
    char array[2];
    do
    {
        arr[0] = addr;
        arr[1] = 1;
        
        I2C_MasterWriteBuf(0b01010000, arr, 2, I2C_MODE_COMPLETE_XFER);
        while (!(I2C_MasterStatus() & I2C_MSTAT_WR_CMPLT));
        I2C_MasterClearStatus();
        CyDelay(5);
        
        sprintf(array, " %d %d\n\r", arr[0], arr[1]);
        UART_PutString(array);
        addr++;
    }while(addr != 10);
}

 void storeTestValues( uint8 addr)
{
    uint8 arr[2];
    char array[2];
    uint8 num = 5;
    char cpos[1];

    do
    {
        arr[0] = addr;
        arr[1] = num;
        
        I2C_MasterWriteBuf(0b01010000, arr, 2, I2C_MODE_COMPLETE_XFER);
        while (!(I2C_MasterStatus() & I2C_MSTAT_WR_CMPLT));
        I2C_MasterClearStatus();
        CyDelay(5);
        
        sprintf(array, " %d %d\n\r", arr[0], arr[1]);
        UART_PutString(array);
        addr++;
        num+=2;
    }while(addr != 10);
    LCD_I2C_clear();
    LCD_I2C_setCursor(0,0);
    LCD_I2C_print("ECE405 Biolock");
    CyDelay(3000);
    LCD_I2C_clear();
    sprintf(cpos, "%d", mPos);
    LCD_I2C_setCursor(0,1);
    LCD_I2C_print("cPos:");
    LCD_I2C_print(cpos);

    I2C_Stop();
}


int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    UART_Start();
    LCD_I2C_start();
    I2C_Start();
    MotorTimer_Start();
    
    DebounceCLK_Start();
    MotorCLK_Start();
    
    CycleISR_Start();
    ConfirmISR_Start();
    OverwriteISR_Start();
    ForwardISR_Start();
    BackISR_Start();
    ICPCK_ISR_Start();
    ENCISR_Start();
    MotorISR_Start();
    
    
    mPos = 1;
    FPSmPos = 1;
    buttonID = 0;
    //MotorTimer_WritePeriod(9999);
    zeroEEPROM(0);
    storeTestValues(0);
    
    char arr[1];
    for(;;)
    {
        
    }
}

/* [] END OF FILE */
