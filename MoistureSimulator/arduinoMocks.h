/*
 * This file is intended as a set of copies of the standard Arduino classes and functions.
 * It is so code can pretend it is running on the Arduino board.
 */
#include <stdio.h>
#include <time.h>

// Returns the number of milliseconds passed since the Arduino board began running the current program.
// NOTE: On real Arduino boards, this number will overflow (go back to zero), after approximately 50 days.
unsigned long millis()
{
    return (unsigned long)time(NULL);
}