/*-
 * Copyright (c) 2021 Ruslan Bukin <br@bsdpad.com>
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

#include <sys/cdefs.h>
#include <sys/systm.h>
#include <sys/callout.h>
#include <sys/thread.h>

#include <arm/raspberrypi/rp2040_timer.h>

#define	RP2040_TIMER_DEBUG
#undef	RP2040_TIMER_DEBUG

#ifdef	RP2040_TIMER_DEBUG
#define	dprintf(fmt, ...)	printf(fmt, ##__VA_ARGS__)
#else
#define	dprintf(fmt, ...)
#endif

#define	RD4(_sc, _reg)		\
	*(volatile uint32_t *)((_sc)->base + _reg)
#define	WR4(_sc, _reg, _val)	\
	*(volatile uint32_t *)((_sc)->base + _reg) = _val

void
rp2040_timer_intr(void *arg, int irq)
{
	struct rp2040_timer_softc *sc;
	int cpuid;

	sc = arg;

	cpuid = PCPU_GET(cpuid);

	dprintf("%s%d\n", __func__, cpuid);

	WR4(sc, RP2040_TIMER_INTR, (1 << cpuid));

	mdx_callout_callback(&sc->mt);
}

void
rp2040_timer_udelay(struct rp2040_timer_softc *sc, uint32_t ticks)
{

	/* TODO */
}

static void
rp2040_timer_start(void *arg, uint32_t ticks)
{
	struct rp2040_timer_softc *sc;
	uint32_t val;
	int cpuid;

	sc = arg;

	KASSERT(curthread->td_critnest > 0,
	    ("%s: Not in critical section.", __func__));

	cpuid = PCPU_GET(cpuid);

	dprintf("%s%d: %d\n", __func__, PCPU_GET(cpuid), ticks);

	/* At least 2 ticks needed to avoid the race (based on experiments). */
	if (ticks < 100)
		ticks = 100;

	val = RD4(sc, RP2040_TIMER_TIMERAWL);
	val += ticks;
	if (cpuid == 0)
		WR4(sc, RP2040_TIMER_ALARM0, val);
	else
		WR4(sc, RP2040_TIMER_ALARM1, val);
}

static void
rp2040_timer_stop(void *arg)
{
	struct rp2040_timer_softc *sc;
	int cpuid;

	KASSERT(curthread->td_critnest > 0,
	    ("%s: Not in critical section.", __func__));

	sc = arg;

	cpuid = PCPU_GET(cpuid);

	dprintf("%s%d\n", __func__, PCPU_GET(cpuid));

	WR4(sc, RP2040_TIMER_ARMED, (1 << cpuid));
}

static uint32_t
rp2040_timer_count(void *arg)
{
	struct rp2040_timer_softc *sc;
	uint32_t reg;

	sc = arg;

	reg = RD4(sc, RP2040_TIMER_TIMERAWL);

	return (reg);
}

int
rp2040_timer_init(struct rp2040_timer_softc *sc,
    uint32_t base, uint32_t freq)
{

	sc->base = base;
	sc->freq = freq;

	bzero(&sc->mt, sizeof(struct mi_timer));
	sc->mt.start = rp2040_timer_start;
	sc->mt.stop = rp2040_timer_stop;
	sc->mt.count = rp2040_timer_count;
	sc->mt.maxcnt = 0xffffffff;
	sc->mt.frequency = freq;
	sc->mt.arg = sc;
	mdx_callout_register(&sc->mt);

	WR4(sc, RP2040_TIMER_ALARM0, 0);
	WR4(sc, RP2040_TIMER_ALARM1, 0);
	WR4(sc, RP2040_TIMER_INTE, 0x3);

	return (0);
}
