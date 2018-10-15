/*
 * tio_delay.c
 *
 *  Created on: 08.10.2018
 *      Author: josef
 */


#include <tio_delay.h>

/******************************************************************** DEFINES */


/****************************************************************** FUNCTIONS */

/*!
*  @brief function is waiting for the delayTime (1 delayTime ~ 10 CPU ticks)
*  @param
		delayTime ... how long the programm should wait
*  @return
		0 ... success
		1 ... error: no time to wait
*/
unsigned int
_tio_busy_waiting (unsigned int delayTime)
{
	while(delayTime--)
	{
		__NOP();
	}

	return 0;
}

/*!
*  @brief function is waiting for the delayTime (1 delayTime ~ 10 CPU ticks) afterwards a function gets executes
*  @param
		delayTime ... time to wait
		fprt ........ function which gets executed after the delayTime is over
*  @return
		0 ... success
		1 ... error: no time to wait
*/
unsigned int
_tio_busy_waiting_with_callback (unsigned int delayTime, void(*fptr)(void))
{
	while(delayTime--)
	{
		__NOP();
	}

	(*fptr)();

	return 0;
}

/* EOF */
