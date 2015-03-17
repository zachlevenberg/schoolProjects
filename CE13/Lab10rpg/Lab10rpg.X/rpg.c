// **** Include libraries here ****
// Standard libraries
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

// Microchip libraries
#include <xc.h>
#include <plib.h>

// User libraries
#include "HardwareDefs.h"
#include "Oled.h"
#include "Buttons.h"
#include "Game.h"
#include "Leds.h"
#include "Adc.h"

// **** Set any macros or preprocessor directives here ****

// **** Declare any data types here ****

// **** Define any global or external variables here ****

static uint8_t buttonEvent = 0;
static uint16_t adcValue = 0;
static char title[GAME_MAX_ROOM_TITLE_LENGTH];
static char desc[GAME_MAX_ROOM_DESC_LENGTH];
static char oledScreen[GAME_MAX_ROOM_TITLE_LENGTH + 3*(OLED_CHARS_PER_LINE + 1)];
static char oledScreenFormat1[] = "%s\n\n\n%s";
static char oledScreenFormat2[] = "%s";
static bool oneHundHzFlag = 0;

// **** Declare any function prototypes here ****
void UpdateAll(void);
void Scroll(void);
// Configuration Bit settings
// SYSCLK = 80 MHz (8MHz Crystal/ FPLLIDIV * FPLLMUL / FPLLODIV)
// PBCLK = 20 MHz
// Primary Osc w/PLL (XT+,HS+,EC+PLL)
#pragma config FPLLIDIV   = DIV_2     // Set the PLL input divider to 2
#pragma config FPLLMUL    = MUL_20    // Set the PLL multiplier to 20
#pragma config FPLLODIV   = DIV_1     // Don't modify the PLL output.
#pragma config FNOSC      = PRIPLL    // Set the primary oscillator to internal RC w/ PLL
#pragma config FSOSCEN    = OFF       // Disable the secondary oscillator
#pragma config IESO       = OFF       // Internal/External Switch O
#pragma config POSCMOD    = XT        // Primary Oscillator Configuration
#pragma config OSCIOFNC   = OFF       // Disable clock signal output
#pragma config FPBDIV     = DIV_4     // Set the peripheral clock to 1/4 system clock
#pragma config FCKSM      = CSECMD    // Clock Switching and Monitor Selection
#pragma config WDTPS      = PS1       // Specify the watchdog timer interval (unused)
#pragma config FWDTEN     = OFF       // Disable the watchdog timer
#pragma config ICESEL     = ICS_PGx2  // Allow for debugging with the Uno32
#pragma config PWP        = OFF       // Keep the program flash writeable
#pragma config BWP        = OFF       // Keep the boot flash writeable
#pragma config CP         = OFF       // Disable code protect

int main()
{
    // Configure the device for maximum performance but do not change the PBDIV
    // Given the options, this function will change the flash wait states, RAM
    // wait state and enable prefetch cache but will not change the PBDIV.
    // The PBDIV value is already set via the pragma FPBDIV option above..
    SYSTEMConfig(F_SYS, SYS_CFG_WAIT_STATES | SYS_CFG_PCACHE);

    // Auto-configure the PIC32 for optimum performance at the specified operating frequency.
    SYSTEMConfigPerformance(F_SYS);

    // osc source, PLL multipler value, PLL postscaler , RC divisor
    OSCConfig(OSC_POSC_PLL, OSC_PLL_MULT_20, OSC_PLL_POST_1, OSC_FRC_POST_1);

    // Configure the PB bus to run at 1/4th the CPU frequency, so 20MHz.
    OSCSetPBDIV(OSC_PB_DIV_4);

    // Enable multi-vector interrupts
    INTEnableSystemMultiVectoredInt();
    INTEnableInterrupts();

    // Configure Timer 2 using PBCLK as input. We configure it using a 1:16 prescalar, so each timer
    // tick is actually at F_PB / 16 Hz, so setting PR2 to F_PB / 16 / 100 yields a .01s timer.
    OpenTimer2(T2_ON | T2_SOURCE_INT | T2_PS_1_16, F_PB / 16 / 100);

    // Set up the timer interrupt with a medium priority of 4.
    INTClearFlag(INT_T2);
    INTSetVectorPriority(INT_TIMER_2_VECTOR, INT_PRIORITY_LEVEL_4);
    INTSetVectorSubPriority(INT_TIMER_2_VECTOR, INT_SUB_PRIORITY_LEVEL_0);
    INTEnable(INT_T2, INT_ENABLED);

/******************************** Your custom code goes below here ********************************/
ButtonsInit();
OledInit();
LEDS_INIT();
GameInit();
AdcInit();

UpdateAll();
Scroll();

while(1){
    if(AdcChanged() && oneHundHzFlag){
        oneHundHzFlag = 0;
        adcValue = AdcRead();
        Scroll();
    }

if(buttonEvent & BUTTON_EVENT_4UP){
    buttonEvent &= ~BUTTON_EVENT_4UP;
    if(GameGetCurrentRoomExits() & GAME_ROOM_EXIT_NORTH_EXISTS){
        GameGoNorth();
        UpdateAll();
    }
}

if(buttonEvent & BUTTON_EVENT_3UP){
    buttonEvent &= ~BUTTON_EVENT_3UP;
    if(GameGetCurrentRoomExits() & GAME_ROOM_EXIT_EAST_EXISTS){
        GameGoEast();
        UpdateAll();
    }
}

if(buttonEvent & BUTTON_EVENT_2UP){
    buttonEvent &= ~BUTTON_EVENT_2UP;
    if(GameGetCurrentRoomExits() & GAME_ROOM_EXIT_SOUTH_EXISTS){
        GameGoSouth();
        UpdateAll();
    }
}

if(buttonEvent & BUTTON_EVENT_1UP){
    buttonEvent &= ~BUTTON_EVENT_1UP;
    if(GameGetCurrentRoomExits() & GAME_ROOM_EXIT_WEST_EXISTS){
        GameGoWest();
        UpdateAll();
    }
}

}

/**************************************************************************************************/
    while (1);
}

/**
 * Timer2 interrupt. Checks for button events.
 */
void __ISR(_TIMER_2_VECTOR, ipl4) TimerInterrupt100Hz(void)
{
    static int count = 0;
    count++;
    if(count == 50){
        oneHundHzFlag = 1;
        count = 0;
    }
    buttonEvent = ButtonsCheckEvents();
    // Clear the interrupt flag.
    IFS0CLR = 1 << 8;
}

void UpdateAll(void)
{
        GameGetCurrentRoomTitle(title);
        GameGetCurrentRoomDescription(desc);
        sprintf(oledScreen, oledScreenFormat1, title, desc);
        OledClear(OLED_COLOR_BLACK);
        OledDrawString(oledScreen);
        OledUpdate();
        LEDS_SET(GameGetCurrentRoomExits());
}

void Scroll(void)
{
    int length = strlen(desc);
    int numberOfScreens = ((((length - OLED_CHARS_PER_LINE) / OLED_CHARS_PER_LINE) / 4) + 2);
    int percent = (adcValue * 100) / 1023;
    int screenNumber = (1 + (percent * numberOfScreens) / 100);
    if (screenNumber <= 1) {
        sprintf(oledScreen, oledScreenFormat1, title, desc);
    } else {
        char descLine[(OLED_CHARS_PER_LINE*4) + 1];
        int i = 0;
        for (i = 0; i <= OLED_CHARS_PER_LINE*4; i++) {
            descLine[i] = desc[i + OLED_CHARS_PER_LINE*(1 + 4*(screenNumber - 2))];
        }
        descLine[i] = NULL;
        sprintf(oledScreen, oledScreenFormat2, descLine);
    }
    OledClear(OLED_COLOR_BLACK);
    OledDrawString(oledScreen);
    OledUpdate();
}