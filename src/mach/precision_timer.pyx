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

from libc.stdint cimport uint32_t, int64_t

cdef extern from "precision-timer-osx.h":

	int configure_thread(uint32_t period_time_ms, uint32_t computation_time_ms, uint32_t constraint_time_ms)

	void interval_wait(uint32_t interval_ms)
	
	double get_absolute_time()

	void absolute_wait(double t)
	
	
def configurethread(period_time_ms, computation_time_ms, constraint_time_ms):

	configure_thread(period_time_ms, computation_time_ms, constraint_time_ms)

def intervalwait(interval_ms):

	interval_wait(interval_ms)
			
def getabsolutetime():

	return get_absolute_time()

def absolutewait(double t):

	absolute_wait(t)

	