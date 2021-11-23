//CMPE 127 - Microcontroller Design
//GPIO DEBUG LAB 
//Spring 2015, Lab Section 03, March 11, 2015

/*
 FMASK := Fast Mask register for port.
 Writes, sets, clears, and reads to R/W 0 port (done via writes to FIOPIN, FIOSET, and FIOCLR, and
 reads of FIOPIN) alter or return only the bits enabled
 by zeros in this register.
 */
// libraries, include directives

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif
#include <cr_section_macros.h> #include <stdio.h>
/* Function: Initializes the port and pin as outputs.
 // pre: port, pin numbers
 // post: port, pin numbers are set for GPIO output // FIODIR := Fast GPIO Port Direction control register.
 // This register R/W 0 individually controls the direction
 // of each port pin.
 */ mask = (1 << pinNum)
void GPIOinitOut(uint8_t portNum, uint32_t pinNum)
{
    if (portNum == 0)
    {
        LPC_GPIO0->FIODIR |= (1 << pinNum); else if(portNum == 1)
    }
    else if(portNum == 1)
    {
            LPC_GPIO1->FIODIR |= (1 << pinNum); else if(portNum == 2)
    }
    else if(porNum == 2)
    {
            LPC_GPIO2->FIODIR |= (1 << pinNum);
    }
    else
    {
        puts("Not a valid port!\n");
    }

}


// Function: Init port and pin as inputs
// pre: port
// post: port, pin numbers are set for GPIO input // Initialize the port and pin as outputs.
// mask = (0 << pinNum)
void GPIOinitInput(uint8_t portNum, uint32_t pinNum)
{
    if (portNum == 0)
    {
        LPC_GPIO0->FIODIR &= (0 << pinNum);
    }
    else if(portNum == 1)
    {
        LPC_GPIO1->FIODIR &= (0 << pinNum);
    }else if(portNum == 2)
    {
        LPC_GPIO2->FIODIR &= (0 << pinNum);
    }else
    {
        puts("Not a valid port!\n");
    }
}

/*
//Function: Set a port and pin for input or
// pre: port, pin numbers
// post: port, pin numbers are set for read/write
FIOSET := Fast Port Output Set register using FIOMASK.
This register R/W 0 controls the state of output pins.
Writing 1s produces highs at the corresponding port pins.
Writing 0s has no effect.
Reading this register returns the current contents of the port
output register. Only bits enabled by 0 in FIOMASK can be altered.
*/
void setGPIO(uint8_t portNum, uint32_t pinNum)
{
    if (portNum == 0)
    {
        LPC_GPIO0->FIOSET |= (1 << pinNum);
    }
    else if(portNum == 1)
    {
        LPC_GPIO1->FIOSET |= (1 << pinNum);
    }
    else if(portNum == 2)
    {
        LPC_GPIO2->FIOSET |= (1 <<  pinNum);
    }
    else
    {
        puts("Invalid port. Try again.\n");return;
    }
    printf("Pin 0.%d has been set at Port %d.\n", pinNum, portNum);
    
}

// Function clears contents of port and pin designated.
// pre: port, pin number to clear
// post: pin at port number is cleared
/* }
 Fast Port Output Clear register using FIOMASK. This register WO 0 controls the state of output pins.
 Writing 1s produces lows at the corresponding port pins.
 Writing 0s has no effect. Only bits enabled by 0 in
 FIOMASK can be altered.
 */
void clearGPIO(uint8_t portNum, uint32_t pinNum)
{
    if(portNum == 0)
    {
        LPC_GPIO0->FIOCLR |= (1 << pinNum);
    }
    else if(portNum == 1)
    {
        LPC_GPIO1->FIOCLR |= (1 << pinNum);
    }
    else if(portNum == 2)
    {
        LPC_GPIO2->FIOCLR |= (1 << pinNum);
    }
    else
    {
        puts("Invalid port. Try again.\n");return;
    }
    printf("Pin 0.%d has been set at Port %d.\n", pinNum, portNum);
    
}

/*
 Function reads input from DIP Switch to CPU and prints the value stored in the selected
 port and pin from FIOPIN register.
 pre: port and pin numbers
 post: uses FIOPIN to read current state of pin from FIOPIN register
 FIOPIN := Fast Port Pin value register using FIOMASK. The current state R/W 0 of
 digital port pins can be read from this register, regardless of
 pin direction or alternate function selection (as long as pins are
 not configured as an input to ADC). The value read is masked
 by ANDing with inverted FIOMASK. Writing to this register places corresponding
 values in all bits enabled by zeros in FIOMASK.
 Important: if an FIOPIN register is read, its bit(s) masked with 1 in the FIOMASK
 register will be read as 0 regardless of the physical pin state.
 */

void readAndPrintInput(uint8_t portNum, uint32_t pinNum)
{
    volatile static int logic;// why? we don't want compiler to optimize this :)
    if(portNum == 0)
    {
        logic = ((LPC_GPIO0->FIOPIN & (1 << pinNum)) >> pinNum);
    }
    else if(portNum == 1)
    {
        logic = ((LPC_GPIO1->FIOPIN & (1 << pinNum)) >> pinNum);

    }
    else if(portNum == 2)
    {
        logic = ((LPC_GPIO2->FIOPIN & (1 << pinNum)) >> pinNum);
    }
    else
    {
        puts("Invalid port. Try again.\n"); return;
    }
    printf("P%d.%d has logic value = %d\n",portNum, pinNum, logic);
    
}

// Function prompts user for output pins to verify // pre: nothing
// post: user will select to see 1, 2, or both LEDs ON.
// returns users selection
int promptUserForOutputPins(void)
{
    static volatile int test;
    int errorFlag;
    
    errorFlag = 0;
    do{
        printf("TESTING GPIO OUTPUT\n");
        printf("*Turn ON LED @ J6-21 (enter 1)\n");
        printf("*Turn ON LED @ J6-22 (enter 2)\n");
        printf("*Turn ON both LEDs enter 3)\n");
        scanf("%d",&test);
        if((test > 3) || (test < 1))
        {
            errorFlag = 1; printf("Usage: enter 1 or 2 or 3\b");
        }
    }while(errorFlag);

    return test;
}

// Function prompts user for input port and pin
// pre: points to port and pin variables
// post: valid port and pin for peripheral device is returned
//
void promptUserForInputPortAndPin(int *port, int *pin)
{
    int errorFlag;
    
    errorFlag = 0;
    
    do{
        printf("Please enter port and pin to test peripheral device:\n");
        scanf("%d %d",port,pin);
        if(*port != 2 && ((*pin < 6) || (*pin > 12) ))
        {
            errorFlag = 1;
            printf("Usage: Port = 2; pin >= 6 or pin <= 12");
            
        }
    }while(errorFlag == 1);
}


// Function tests CPU output
// pre: nothing
// post: sets port and pin number(s) for LED(s) from user input,
// result is observed visually on board
void lab1TestOutput(void)
{
    int port, pin, port2, pin2;
    int leds;
    leds = promptUserForOutputPins();
    
    if(leds)
    {
        if(leds == 1)
        {
            // (J6-21)
            port = 0; pin = 2;
            GPIOinitOut(port,pin);
            setGPIO(port,pin);
            clearGPIO(port,pin);
        }
        else if(leds == 2)
        {
            // (J6-22)
            port = 0; pin = 3;
            GPIOinitOut(port,pin);
            setGPIO(port,pin);
            clearGPIO(port,pin);
        }
        else
        {
            // (J6-21 and J6-22)
            port = 0; pin = 2;
            GPIOinitOut(port,pin);
            setGPIO(port,pin);
            port2 = 0; pin2 = 3;
            GPIOinitOut(port2,pin2);
            setGPIO(port2,pin2);
            clearGPIO(port,pin);
            clearGPIO(port2,pin2);
        }
    }
    
}


// Function tests CPU input
// pre: nothing
// post: sets port and pin from user input, calls readAndPrintInput to print the value read in
void lab1TestInput(void)
{
    volatile static int port, pin;
    
    promptUserForInputPortAndPin(&port,&pin);
    
    // manual testing:
    // TEST GPIO INPUT by reading current
    // state of pin from FIOPIN register
    // set p2.6 (J6-48)
    GPIOinitInput(port,pin); setGPIO(port,pin);
    
    // VERIFY INPUT -- PRINT TO CONSOLE READ
    // VALUE FROM DIP SWITCH setting
    readAndPrintInput(port,pin); clearGPIO(port,pin);
}

int main(void)
{
    
    //VERIFY OUTPUT VISUALLY-- SEE LED
    lab1TestOutput();
    //VERIFY INPUT by reading FIOPIN value //from DIP Switch
    lab1TestInput();
    
    return 0;

}
