/*
 * rcc.c
 *
 *  Created on: Sep 1, 2019
 *      Author: technix
 */

#include "rcc.h"

void rcc_init(void)
{
	// This chip needs three frequencies derived from the same crystal.
	RCC->CR |= RCC_CR_HSEON;
	while (!(RCC->CR & RCC_CR_HSERDY));

	// Each frequency taking up one of the three PLL's.
	// Frequency 1: MCLK = 180MHz. 16MHz / 8 * 180 / 2 = 180MHz. Main PLL-P.
	RCC->PLLCFGR =
			(8 << RCC_PLLCFGR_PLLM_Pos) |
			(180 << RCC_PLLCFGR_PLLN_Pos) |
			(0b00 << RCC_PLLCFGR_PLLP_Pos) | // / 2
			RCC_PLLCFGR_PLLSRC_HSE;
	RCC->CR |= RCC_CR_PLLON;
	while (!(RCC->CR & RCC_CR_PLLRDY));

	// Apply Frequency 1.
	FLASH->ACR =
			(8 << FLASH_ACR_LATENCY_Pos) |
			FLASH_ACR_PRFTEN |
			FLASH_ACR_ICEN |
			FLASH_ACR_DCEN;
	SET_FIELD(RCC->CFGR, RCC_CFGR_PPRE1_Msk | RCC_CFGR_PPRE2_Msk, RCC_CFGR_PPRE1_DIV4 | RCC_CFGR_PPRE2_DIV2);
	__DSB();
	SET_FIELD(RCC->CFGR, RCC_CFGR_SW_Msk, RCC_CFGR_SW_PLL);
	while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);

	// Frequency 2: USBFSCLK = 48MHz. 16MHz / 8 * 96 / 4 = 48MHz. PLLSAI-P
	RCC->PLLSAICFGR =
			(8 << RCC_PLLSAICFGR_PLLSAIM_Pos) |
			(96 << RCC_PLLSAICFGR_PLLSAIN_Pos) |
			(0b01 << RCC_PLLSAICFGR_PLLSAIP_Pos); // / 4
	RCC->CR |= RCC_CR_PLLSAION;
	while (!(RCC->CR & RCC_CR_PLLSAIRDY));

	// Apply Frequency 2
	RCC->DCKCFGR2 |= RCC_DCKCFGR2_CK48MSEL;

	// Frequency 3: USBHSCLK = 26MHz. 16MHz / 8 * 52 / 4 = 26MHz. PLLI2S-R
	RCC->PLLI2SCFGR =
			(8 << RCC_PLLI2SCFGR_PLLI2SM_Pos) |
			(52 << RCC_PLLI2SCFGR_PLLI2SN_Pos) |
			(4 << RCC_PLLI2SCFGR_PLLI2SR_Pos);
	RCC->CR |= RCC_CR_PLLI2SON;
	while (!(RCC->CR & RCC_CR_PLLI2SRDY));

	// Apply frequency 3
	SET_FIELD(RCC->CFGR, RCC_CFGR_MCO2PRE_Msk | RCC_CFGR_MCO2_Msk, (0b000 << RCC_CFGR_MCO2PRE_Pos) | (0b01 << RCC_CFGR_MCO2_Pos));
}

