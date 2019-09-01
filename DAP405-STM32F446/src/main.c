/*
 * main.c
 *
 *  Created on: Sep 1, 2019
 *      Author: technix
 */

#include <stm32f4xx.h>

#include "rcc.h"

void SystemInit(void)
{
	rcc_init();
}

int main(void)
{
	for (;;)
		__WFE();
}
