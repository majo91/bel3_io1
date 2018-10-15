/*
 * tio_delay.h
 *
 *  Created on: 08.10.2018
 *      Author: josef
 */

#ifndef _TIO_DELAY_
#define _TIO_DELAY_

#include <stdio.h>
#include <stdarg.h>

#include <GPIO.h>
#include <xmc_gpio.h>

unsigned int
	_tio_busy_waiting(unsigned int),
	_tio_busy_waiting_with_callback(unsigned int, void(*)());


#endif
/* EOF */
