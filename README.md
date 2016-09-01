# precision-timer-python

Provides an interval-based, high precision timer in C and python assuming your kernel has compiled support. These libraries do not require the process to have elevated priveliges. Accuracy <1ms are easily acheivable and even greater accuracy may be obtained depending on the hardware and software architecture. From my observation, the linux timers running on a TI AM57X (ARM processor) have significantly greater accuracy and smaller drift than my MacBook Pro. The OS and hardware has significant effect. 

The project is set up with separate, but similar projects per-platform. This is due to the fact that the APIs for each platform are different enough that I did not want to build to the lowest common denominator with tons of #ifdefs obfuscating the code. 

## Operation

The general operation principal is that the interval_wait method is intended to be called repeatedly, each time sleeping only as much as is requred to hit the next interval from the start time of the last interval. The first time it's called, the timer will wait the number of milliseconds passed in. Subsequent calls will sleep only as much time as needed. 

As long as you can finish your work before the next timer would have gone off, you can guarantee that the events will fire at regular intervals, not impacted by the time of the amount of work that needed to take place. In practice, this may be a bit more difficult than it sounds, but it will work as long as you observe typical practices for real-time programming. 

## OS X Examples

OS X Requires the thread requesting high-precision timers to have the thread be pre-configured to access these special timers. This is done by making a cal to configure\_thread() with a set of parameters describing the conditions the thread will be operating under. For details about proper configuration of the thread, please see https://developer.apple.com/library/ios/technotes/tn2169/_index.html 

### C

	if (configure_thread(0, 5, 10))
	{
		return 1;
	}
	
	while (1)
	{
		interval_wait(1000);
		
		struct timeval tp;
		gettimeofday(&tp, NULL);
		long int ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;
		
		syslog(LOG_ERR, "%lu", ms);
	}

### Python

	while 1:
		precision_timer.intervalwait(1000)
		print time.time()



