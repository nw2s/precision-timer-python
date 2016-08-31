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
#include <pthread.h>
#include <mach/mach.h>
#include <mach/mach_time.h>
#include <time.h>

#include "machthread.h"

int set_mach_thread_policy(uint32_t period_time_ms, uint32_t computation_time_ms, uint32_t constraint_time_ms)
{
	/* Set up the current thread to be real-time priority */

	mach_timebase_info_data_t timebase_info;
	mach_timebase_info(&timebase_info);

	double clock2abs = ((double)timebase_info.denom / (double)timebase_info.numer) * NANOS_PER_MSEC;

	thread_time_constraint_policy_data_t policy;
	policy.period = period_time_ms;
	policy.computation = (uint32_t)(computation_time_ms * clock2abs); // 5 ms of work
	policy.constraint  = (uint32_t)(constraint_time_ms * clock2abs);
	policy.preemptible = FALSE;

	int kr = thread_policy_set(pthread_mach_thread_np(pthread_self()), THREAD_TIME_CONSTRAINT_POLICY, (thread_policy_t)&policy, THREAD_TIME_CONSTRAINT_POLICY_COUNT);

	if (kr != KERN_SUCCESS) 
	{
		//TODO: Convert to syslog
	    mach_error("Error setting thread policy: ", kr);
	    return 1;
	}
	
	return 0;
}


void wait_until_time(uint64_t wait_time)
{		
	mach_wait_until(wait_time);
}



