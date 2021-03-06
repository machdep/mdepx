/*-
 * Copyright (c) 2019 Ruslan Bukin <br@bsdpad.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef	_ARM_NORDICSEMI_NRF5340_APP_CORE_H_
#define	_ARM_NORDICSEMI_NRF5340_APP_CORE_H_

#include <arm/nordicsemi/nrf_cryptocell.h>
#include <arm/nordicsemi/nrf_dppi.h>
#include <arm/nordicsemi/nrf_egu.h>
#include <arm/nordicsemi/nrf_i2s.h>
#include <arm/nordicsemi/nrf_kmu.h>
#include <arm/nordicsemi/nrf_pdm.h>
#include <arm/nordicsemi/nrf_power.h>
#include <arm/nordicsemi/nrf_pwm.h>
#include <arm/nordicsemi/nrf_saadc.h>
#include <arm/nordicsemi/nrf_spim.h>
#include <arm/nordicsemi/nrf_spis.h>
#include <arm/nordicsemi/nrf_spu.h>
#include <arm/nordicsemi/nrf_timer.h>
#include <arm/nordicsemi/nrf_uicr.h>
#include <arm/nordicsemi/nrf_wdt.h>
#include <arm/nordicsemi/nrf_gpio.h>
#include <arm/nordicsemi/nrf_gpiote.h>
#include <arm/nordicsemi/nrf_ipc.h>
#include <arm/nordicsemi/nrf_nvmc.h>
#include <arm/nordicsemi/nrf_reset.h>
#include <arm/nordicsemi/nrf_rtc.h>
#include <arm/nordicsemi/nrf_twim.h>
#include <arm/nordicsemi/nrf_twis.h>
#include <arm/nordicsemi/nrf_uarte.h>

#define	BASE_DCNF	0x40000000 /* DCNF Domain configuration */
#define	BASE_FPU	0x40000000 /* FPU Floating Point unit interrupt control */
#define	BASE_CACHE	0x50001000 /* CACHE Cache */
#define	BASE_SPU	0x50003000 /* SPU System protection unit */
#define	BASE_OSCILLATORS	0x40004000 /* OSCILLATORS Oscillator configuration */
#define	BASE_REGULATORS	0x40004000 /* REGULATORS Regulator configuration */
#define	BASE_CLOCK	0x40005000 /* CLOCK Clock control */
#define	BASE_POWER	0x40005000 /* POWER Power control */
#define	BASE_RESET	0x40005000 /* RESET Reset control and status */
#define	BASE_CTRLAPPERI	0x40006000 /* CTRLAPPERI Control access port CPU side */
#define	BASE_SPIM0	0x40008000 /* SPIM0 SPI master 0 */
#define	BASE_SPIS0	0x40008000 /* SPIS0 SPI slave 0 */
#define	BASE_TWIM0	0x40008000 /* TWIM0 Two-wire interface master 0 */
#define	BASE_TWIS0	0x40008000 /* TWIS0 Two-wire interface slave 0 */
#define	BASE_UARTE0	0x40008000 /* UARTE0 Universal asynchronous receiver/transmitter with EasyDMA 0 */
#define	BASE_SPIM1	0x40009000 /* SPIM1 SPI master 1 */
#define	BASE_SPIS1	0x40009000 /* SPIS1 SPI slave 1 */
#define	BASE_TWIM1	0x40009000 /* TWIM1 Two-wire interface master 1 */
#define	BASE_TWIS1	0x40009000 /* TWIS1 Two-wire interface slave 1 */
#define	BASE_UARTE1	0x40009000 /* UARTE1 Universal asynchronous receiver/transmitter with EasyDMA 1 */
#define	BASE_SPIM2	0x4000A000 /* SPIM SPI master 2 (high-speed) */
#define	BASE_GPIOTE0	0x5000D000 /* GPIOTE GPIO tasks and events */
#define	BASE_SAADC	0x4000E000 /* SAADC Successive approximation analog-to-digital converter */
#define	BASE_TIMER0	0x4000F000 /* TIMER0 Timer 0 */
#define	BASE_TIMER1	0x40010000 /* TIMER1 Timer 1 */
#define	BASE_TIMER2	0x40011000 /* TIMER2 Timer 2 */
#define	BASE_RTC0	0x40014000 /* RTC0 Real time counter 0 */
#define	BASE_RTC1	0x40015000 /* RTC1 Real time counter 1 */
#define	BASE_DPPIC	0x40017000 /* DPPIC DPPI controller */
#define	BASE_WDT0	0x40018000 /* WDT0 Watchdog timer 0 */
#define	BASE_WDT1	0x40019000 /* WDT1 Watchdog timer 1 */
#define	BASE_COMP	0x4001A000 /* COMP Comparator */
#define	BASE_LPCOMP	0x4001A000 /* LPCOMP Low-power comparator */
#define	BASE_EGU0	0x4001B000 /* EGU0 Event generator unit 0 */
#define	BASE_EGU1	0x4001C000 /* EGU1 Event generator unit 1 */
#define	BASE_EGU2	0x4001D000 /* EGU2 Event generator unit 2 */
#define	BASE_EGU3	0x4001E000 /* EGU3 Event generator unit 3 */
#define	BASE_EGU4	0x4001F000 /* EGU4 Event generator unit 4 */
#define	BASE_EGU5	0x40020000 /* EGU5 Event generator unit 5 */
#define	BASE_PWM0	0x40021000 /* PWM0 Pulse width modulation unit 0 */
#define	BASE_PWM1	0x40022000 /* PWM1 Pulse width modulation unit 1 */
#define	BASE_PWM2	0x40023000 /* PWM2 Pulse width modulation unit 2 */
#define	BASE_PDM	0x40026000 /* PDM Pulse density modulation (digital microphone) interface */
#define	BASE_I2S	0x40028000 /* I2S Inter-IC sound interface */
#define	BASE_IPC	0x4002A000 /* IPC Interprocessor communication */
#define	BASE_QSPI	0x4002B000 /* QSPI External memory (quad serial peripheral) interface */
#define	BASE_NFCT	0x4002D000 /* NFCT Near field communication tag */
#define	BASE_GPIOTE1	0x4002F000 /* GPIOTE GPIO tasks and events */
#define	BASE_MUTEX	0x40030000 /* MUTEX Mutual exclusive hardware support */
#define	BASE_QDEC	0x40033000 /* QDEC Quadrature decoder */
#define	BASE_USBD	0x40036000 /* USBD Universal serial bus device */
#define	BASE_USBREG	0x40037000 /* USBREG USB regulator control */
#define	BASE_KMU	0x40039000 /* KMU Key management unit */
#define	BASE_NVMC	0x40039000 /* NVMC Non-volatile memory controller */
#define	BASE_GPIO0	0x40842500 /* GPIO0 General purpose input and output, port 0 */
#define	BASE_GPIO1	0x40842800 /* GPIO1 General purpose input and output, port 1 */
#define	BASE_CRYPTOCELL	0x50844000 /* CRYPTOCELL CryptoCell subsystem control interface */
#define	BASE_VMC	0x40081000 /* VMC Volatile memory controller */
#define	BASE_CACHEDATA	0x00F00000 /* CACHEDATA Cache data */
#define	BASE_CACHEINFO	0x00F08000 /* CACHEINFO Cache info */
#define	BASE_FICR	0x00FF0000 /* FICR Factory information configuration registers */
#define	BASE_UICR	0x00FF8000 /* UICR User information configuration registers */
#define	BASE_CTI	0xE0042000 /* CTI Cross-trigger interface */
#define	BASE_TAD	0xE0080000 /* TAD Trace and debug control */

#define	BASE_TAD	0xE0080000 /* Trace and debug control */
#define	BASE_SCS	0xE000E000 /* System Control Space */
#define	BASE_SCS_NS	0xE002E000 /* System Control Space Non-Secure */

#define	NRF_SECURE_ACCESS	(1 << 28)

#define	ID_DCNF		0
#define	ID_FPU		0
#define	ID_CACHE	1
#define	ID_SPU		3
#define	ID_OSCILLATORS	4
#define	ID_REGULATORS	4
#define	ID_CLOCK	5
#define	ID_POWER	5
#define	ID_RESET	5
#define	ID_CTRLAPPERI	6
#define	ID_SPIM0	8
#define	ID_SPIS0	8
#define	ID_TWIM0	8
#define	ID_TWIS0	8
#define	ID_UARTE0	8
#define	ID_SPIM1	9
#define	ID_SPIS1	9
#define	ID_TWIM1	9
#define	ID_TWIS1	9
#define	ID_UARTE1	9
#define	ID_SPIM2	10
#define	ID_GPIOTE0	13
#define	ID_SAADC	14
#define	ID_TIMER0	15
#define	ID_TIMER1	16
#define	ID_TIMER2	17
#define	ID_RTC0		20
#define	ID_RTC1		21
#define	ID_DPPIC	23
#define	ID_WDT0		24
#define	ID_WDT1		25
#define	ID_COMP		26
#define	ID_LPCOMP	26
#define	ID_EGU0		27
#define	ID_EGU1		28
#define	ID_EGU2		29
#define	ID_EGU3		30
#define	ID_EGU4		31
#define	ID_EGU5		32
#define	ID_PWM0		33
#define	ID_PWM1		34
#define	ID_PWM2		35
#define	ID_PDM		38
#define	ID_I2S		40
#define	ID_IPC		42
#define	ID_QSPI		43
#define	ID_NFCT		45
#define	ID_GPIOTE1	47
#define	ID_MUTEX	48
#define	ID_QDEC		51
#define	ID_USBD		54
#define	ID_USBREG	55
#define	ID_KMU		57
#define	ID_NVMC		57
#define	ID_GPIO0	66
#define	ID_GPIO1	66
#define	ID_CRYPTOCELL	68
#define	ID_VMC		129

#endif /* !_ARM_NORDICSEMI_NRF5340_APP_CORE_H_ */
