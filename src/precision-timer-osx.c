/*
# precision-timer-python - a precision event timer for python
# Copyright (C) 2016 Scott Wilson (thomas.scott.wilson@gmail.com)
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdint.h>
#include <stdio.h>
#include <mach/mach.h>
#include <mach/mach_time.h>
#include <time.h>

#include "machthread.h"

static uint64_t last_time = 0;
static uint64_t next_time = 0;

static mach_timebase_info_data_t timebase_info;


static inline uint64_t abs_to_nanos(uint64_t abs) 
{
    return abs * timebase_info.numer / timebase_info.denom;
}


static uint64_t nanos_to_abs(uint64_t nanos) 
{
    return nanos * timebase_info.denom / timebase_info.numer;
}


int configure_thread(uint32_t period_time_ms, uint32_t computation_time_ms, uint32_t constraint_time_ms)
{
	return set_mach_thread_policy(period_time_ms, computation_time_ms, constraint_time_ms);
}


void interval_wait(uint32_t interval_ms)
{
	/* First time around, set last time to now */
	if (last_time == 0)
	{
	    mach_timebase_info(&timebase_info);

		last_time = mach_absolute_time();
		next_time = last_time;
	}
	
	uint64_t interval_abs = nanos_to_abs(interval_ms * NANOS_PER_MSEC);

	/* last_time = the time we just woke up */
	/* next_time = the next time we should wake up */
	last_time = next_time;
	next_time = last_time + interval_abs;

	wait_until_time(next_time);	
}

