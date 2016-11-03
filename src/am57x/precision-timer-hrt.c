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
#include <time.h>
#include <sys/time.h>

#include "tsutil/ts_util.h"

static struct timespec last_time = { 0, 0 };
static struct timespec next_time = { 0, 0 };


static void ms2ts(struct timespec *ts, uint32_t ms)
{
    ts->tv_sec = ms / 1000;
    ts->tv_nsec = (ms % 1000) * 1000000;
}

double get_absolute_time()
{
	timespec t;
	
	clock_gettime(CLOCK_MONOTONIC, &t);

	return tsFloat(t);
}

void absolute_wait(double t)
{
	timespec ts;
	
	ts = tsCreateF(t);
	
	return t;
}

void interval_wait(uint32_t interval_ms)
{
	/* First time around, set last time to now */
	if (last_time.tv_sec == 0)
	{
		clock_gettime(CLOCK_MONOTONIC, &last_time);
		next_time = last_time;
	}
	
	/* Convert the incoming interval to ts */
	struct timespec interval_ts;
	ms2ts(&interval_ts, interval_ms);
	
	/* last_time = the time we just woke up */
	/* next_time = the next time we should wake up */
	last_time = next_time;
	next_time = tsAdd(last_time, interval_ts);

	clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &next_time, NULL);
}

