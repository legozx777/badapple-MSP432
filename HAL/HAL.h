/*
 * HAL.h
 *
 *  Created on: Dec 29, 2019
 *      Author: Matthew Zhong
 *  Supervisor: Leyla Nazhand-Ali
 */

#ifndef HAL_HAL_H_
#define HAL_HAL_H_

#include <HAL/Button.h>
#include <HAL/Timer.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>


/**============================================================================
 * The main HAL struct. This struct encapsulates all of the other input structs
 * in this application as individual members. This includes all LEDs, all
 * Buttons, one HWTimer from which all software timers should reference, the
 * Joystick, and any other peripherals with which you wish to interface.
 * ============================================================================
 * USAGE WARNINGS
 * ============================================================================
 * YOU SHOULD HAVE EXACTLY ONE HAL STRUCT IN YOUR ENTIRE PROJECT. We recommend
 * you put this struct inside of a main [Application] object so that every
 * single function in your application has access to the main inputs and outputs
 * which interface with the hardware on the MSP432.
 */
struct _HAL
{
    // Buttons - Boosterpack S1
    Button boosterpackS1;
};
typedef struct _HAL HAL;

// Constructs an HAL object by calling the constructor of each individual member
HAL HAL_construct();

// Refreshes all necessary inputs in the HAL
void HAL_refresh(HAL* api);


#endif /* HAL_HAL_H_ */
