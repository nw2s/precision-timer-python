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

static const uint64_t NANOS_PER_USEC = 1000ULL;
static const uint64_t NANOS_PER_MSEC = 1000ULL * NANOS_PER_USEC;
static const uint64_t NANOS_PER_SEC = 1000ULL * NANOS_PER_MSEC;


int set_mach_thread_policy(uint32_t period_time_ms, uint32_t computation_time_ms, uint32_t constraint_time_ms);

void wait_until_time(uint64_t interval_ms);
