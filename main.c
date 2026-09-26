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

#define FPS_30 100000

const Graphics_Image *frames64_get_frame(uint32_t index);
extern const uint32_t frames64_count;

void initGraphics(Graphics_Context *g_sContext_p)
{
    // initializing the display
    Crystalfontz128x128_Init();
    Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP);

    // setting up the graphics
    Graphics_initContext(g_sContext_p, &g_sCrystalfontz128x128,
                         &g_sCrystalfontz128x128_funcs);
//    Graphics_setFont(g_sContext_p, &g_sFontFixed6x8);

    // set colors
    Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_WHITE);
    Graphics_setBackgroundColor(g_sContext_p, GRAPHICS_COLOR_BLACK);

    // apply changes by clearing background
    Graphics_clearDisplay(g_sContext_p);
}

void playVideo(Graphics_Context *g_sContext_p) {
    Timer32_setCount(TIMER32_0_BASE, FPS_30);
    Timer32_startTimer(TIMER32_0_BASE, true);

    int i = 0;
    while (i < frames64_count) {
        if (Timer32_getValue(TIMER32_0_BASE) == 0) {
            Graphics_drawImage(g_sContext_p, frames64_get_frame(i), 0, 0);
            i++;

            // since the timer is in one-shot mode, we have to restart it to get a periodic behavior
            Timer32_setCount(TIMER32_0_BASE, FPS_30);
            Timer32_startTimer(TIMER32_0_BASE, true);
        }
    }
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

    Timer32_initModule(TIMER32_0_BASE, // There are two timers, we are using the one with the index 0
                       TIMER32_PRESCALER_1, // The prescaler value is 1; The clock is not divided before feeding the counter
                       TIMER32_32BIT, // The counter is used in 32-bit mode; the alternative is 16-bit mode
                       TIMER32_PERIODIC_MODE); //This options is irrelevant for a one-shot timer

    while (1) {
        HAL_refresh(&hal);
        if (Button_isPressed(&hal.boosterpackS1)) {
            playVideo(&g_sContext);
            break;
        }
    }
}
