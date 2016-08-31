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


#include <stdio.h>
#include <syslog.h>
#include <time.h>
#include <sys/time.h>

#include "precision-timer-hrt.h"

int main()
{
	while (1)
	{
		// struct timespec ts;
		//
		// clock_gettime(CLOCK_MONOTONIC, &ts);
		//
		// 	    ts.tv_sec = ts.tv_sec + 3;
		//
		// clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &ts, NULL);

		interval_wait(1000);

		struct timeval tp;
		gettimeofday(&tp, NULL);
		long int ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;
		
		syslog(LOG_ERR, "%lu", ms);
	}
}

