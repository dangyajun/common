/******************************************************************************

    @file    DemOS: os.c
    @author  Rajmund Szymański
    @date    16.03.2023
    @brief   This file provides set of functions for DemOS.

 ******************************************************************************

   Copyright (c) 2018-2023 Rajmund Szymanski. All rights reserved.

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to
   deal in the Software without restriction, including without limitation the
   rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
   sell copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included
   in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
   THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
   FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
   IN THE SOFTWARE.

 ******************************************************************************/

#include "os.h"

/* --------------------------------------------------------------------------------------------- */

static
tsk_t  MAIN = { 0, ID_RIP, 0, NULL, &MAIN };

tsk_t *sys_current = &MAIN;

/* --------------------------------------------------------------------------------------------- */

void tsk_start( tsk_t *tsk )
{
	static
	tsk_t *tail = &MAIN;

	if (tsk->id == ID_RIP)
	{
		tsk->state = 0;
		tsk->id = ID_RDY;

		if (tsk->next == NULL)
		{
			tsk->next = tail->next;
			tail->next = tsk;
			tail = tsk;
		}
	}
}

/* --------------------------------------------------------------------------------------------- */

void sys_stop( void )
{
	tsk_t *tsk = &MAIN;

	while ((tsk = tsk->next) != &MAIN)
		tsk->id = ID_RIP;
}

/* --------------------------------------------------------------------------------------------- */

static cnt_t get_counter( void )
{
	cnt_t result;
	do result = sys_counter; while (result != sys_counter);
	return result;
}

/* --------------------------------------------------------------------------------------------- */

void sys_delay( cnt_t millis )
{
	cnt_t cnt;
	cnt_t start = get_counter();
	do cnt = get_counter(); while (cnt - start < millis);
}

/* --------------------------------------------------------------------------------------------- */
