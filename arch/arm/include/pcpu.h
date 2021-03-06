/*-
 * Copyright (c) 2019-2020 Ruslan Bukin <br@bsdpad.com>
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

#ifndef	_MACHINE_PCPU_H_
#define	_MACHINE_PCPU_H_

#include <sys/cpu.h>

#ifdef MDX_SCHED_SMP

static inline struct pcpu *
get_pcpu(void)
{
	struct pcpu *p;
	int cpuid;

	cpuid = cpu_coreid();

	/*
	 * Note that an interrupt could fire right here, then we appear
	 * on another CPU and return wrong pcpu.
	 * Disable interrupts if needed before call to this function.
	 */

	p = &__pcpu[cpuid];

	return (p);
}

static inline struct thread *
get_curthread(void)
{
	struct thread *td;
	struct pcpu *pcpu;
	uint32_t reg;
	int cpuid;

	/*
	 * Since we can't get curthread from curpcpu in a single instruction
	 * we have to disable interrupts.
	 * Otherwise an interrupt between these lines could lead us to return
	 * the current thread of another CPU.
	 */
	__asm __volatile("mrs %0, primask\n"
			 "cpsid i" : "=r" (reg) :: "memory");

	cpuid = cpu_coreid();

	pcpu = &__pcpu[cpuid];

	/* pc_curthread is the first member of struct pcpu. */
	td = (struct thread *)*(uintptr_t *)pcpu;

	/* Restore interrupts. */
	if ((reg & 1) == 0)
		__asm __volatile("cpsie i");

	return (td);
}

#else

static inline struct pcpu *
get_pcpu(void)
{
	struct pcpu *p;

	p = &__pcpu[0];

	return (p);
}

static inline struct thread *
get_curthread(void)
{
	struct thread *td;

	/* pc_curthread is the first member of struct pcpu. */
	td = (struct thread *)*(uintptr_t *)&__pcpu[0];

	return (td);
}

#endif

#define	curthread get_curthread()
#define	curpcpu get_pcpu()

#define	PCPU_GET(member)	(get_pcpu()->pc_ ## member)
#define	PCPU_ADD(member, value)	(get_pcpu()->pc_ ## member += (value))
#define	PCPU_INC(member)	PCPU_ADD(member, 1)
#define	PCPU_PTR(member)	(&get_pcpu()->pc_ ## member)
#define	PCPU_SET(member, value)	(get_pcpu()->pc_ ## member = (value))

#endif /* !_MACHINE_PCPU_H_ */
