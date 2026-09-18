// Author: Michael Zhao

/* TI includes */
#include <LcdDriver/Crystalfontz128x128_ST7735.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

/* HAL includes */
#include <HAL/HAL.h>
#include <HAL/Timer.h>

void initGraphics(Graphics_Context *g_sContext_p)
{
    // initializing the display
    Crystalfontz128x128_Init();
    Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP);

    // setting up the graphics
    Graphics_initContext(g_sContext_p, &g_sCrystalfontz128x128,
                         &g_sCrystalfontz128x128_funcs);
    Graphics_setFont(g_sContext_p, &g_sFontFixed6x8);

    // set colors
    Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_WHITE);
    Graphics_setBackgroundColor(g_sContext_p, GRAPHICS_COLOR_BLACK);

    // apply changes by clearing background
    Graphics_clearDisplay(g_sContext_p);
}

int main(void)
{
    // Stop Watchdog Timer - THIS SHOULD ALWAYS BE THE FIRST LINE OF MAIN
    WDT_A_holdTimer();

    // MUST be called, otherwise buttons will not work
    InitSystemTiming();
    HAL hal = HAL_construct();

    // Setup the graphics so we can use the Boosterpack LCD screen
    Graphics_Context g_sContext;
    initGraphics(&g_sContext);

    Graphics_drawLineH(&g_sContext, 0, 127, 64);

    while (1) {
        HAL_refresh(&hal);

        if (Button_isPressed(&hal.boosterpackS1)) {

        }
    }
}
