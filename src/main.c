/**
   @mainpage XMC Barebone Template

   @section Usage

   This project is intended to be used along with Eclipse or from the CMD-Line
   using a Makefile. The latter provides the following commands:

   @verbatim
   make                        # build the project
   make debug                  # build the project and start the debugger
   make flash                  # flash the application
   make doc                    # generate the documentation
   make clean                  # delete intermediate files
   @endverbatim

   @section Folders

   The code is organized in various folders - checkout the comments below:

   @verbatim
   Makefile          # top level Makefile used for the command-line variant
   doxygen           # doxygen configuration file
   inc/              # the place for your header files
   src/              # the place for your source files
   bin/              # output folder - here you will find listings and binaries
   Debug/            # this fiolder is only used by Eclipse
   doc/              # here the generated documentation is found
   system/           # CMSIS library, Infineon header files, linker script, etc.
   xmclib/           # low-level XMC library
   @endverbatim

   @file main.c
   @date 08 Sep, 2015
   @version 1.0.0

   GPIO toggle example flashes the leds of the board with a periodic rate.
   LED1 is connected to P1.10
   LED2 is connected to P1.11
   LED3 is connected to P1.12

   History <br>

   Version 1.0.0 Initial <br>
 */

#include <debug_lib.h>
#include <stdio.h>
#include <xmc_gpio.h>
#include "test_uart.h"
#include "tio_delay.h"

#define TICKS_PER_SECOND 1000
#define TICKS_WAIT 500

#define LED1 P1_10
#define LED2 P1_11
#define LED3 P1_12
#define PinOut P1_6

#define RX_BUFFER_SIZE 64

void SysTick_Handler(void) {
	static uint32_t ticks = 0;
	static int32_t cnt = 0;

	ticks++;
	if (ticks == TICKS_WAIT) {
		XMC_GPIO_ToggleOutput(LED1);
		XMC_GPIO_ToggleOutput(LED2);
		printf("Testing... %d\n", (int)cnt++);

		ticks = 0;
	}
}

void activALL(){
	XMC_GPIO_SetOutputHigh(LED1);
	XMC_GPIO_SetOutputHigh(LED2);
	XMC_GPIO_SetOutputHigh(LED3);
	_tio_busy_waiting(50000000);
}

void clearALL(){
	XMC_GPIO_SetOutputLow(LED1);
	XMC_GPIO_SetOutputLow(LED2);
	XMC_GPIO_SetOutputLow(LED3);
	_tio_busy_waiting(5000000);
}

int main(void) {
	XMC_GPIO_CONFIG_t config;
	int i=5000000;
	int y=0;
	initRetargetSwo();
	void (*fptr)() = &activALL;

	config.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL;
	config.output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH;
	config.output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM;

	XMC_GPIO_Init(LED1, &config);

	config.output_level = XMC_GPIO_OUTPUT_LEVEL_LOW;
	XMC_GPIO_Init(LED2, &config);
	XMC_GPIO_Init(LED3, &config);
	XMC_GPIO_Init(PinOut, &config);

	while(1) {
		XMC_GPIO_SetOutputHigh(LED1);
		_tio_busy_waiting(i);
		XMC_GPIO_SetOutputLow(LED1);
		XMC_GPIO_SetOutputHigh(LED2);
		_tio_busy_waiting(i);
		XMC_GPIO_SetOutputLow(LED2);
		XMC_GPIO_SetOutputHigh(PinOut);
		_tio_busy_waiting(i);
		XMC_GPIO_SetOutputLow(PinOut);
		XMC_GPIO_ToggleOutput(LED3);
		_tio_busy_waiting(i);
		XMC_GPIO_ToggleOutput(LED3);
		_tio_busy_waiting(i);
		XMC_GPIO_ToggleOutput(LED3);
		_tio_busy_waiting(i);
		XMC_GPIO_ToggleOutput(LED3);
		_tio_busy_waiting(i);
		//activALL();
		//_tio_busy_waiting(i);
		clearALL();
		_tio_busy_waiting_with_callback(i, fptr);
		clearALL(y);
	}
}

/* EOF */
