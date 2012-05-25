/*
 * timer.cpp
 *
 * Created on: Nov 11, 2011
 *     Author: George Stark <george-u@yandex.com>
 *
 * License: GNU GPL v2
 *
 */

#include <stdio.h>
#include "timer.h"

//==============================================================================
Timer::Timer()
{
	start();
}


//==============================================================================
void Timer::start()
{
	start_time_ = get_tick_count(); elapsed_time_ = 0;
}

//==============================================================================
String Timer::elapsed_time()
{
	elapsed_time_ = get_tick_count() - start_time_;

	char buf[16];
	sprintf(buf, "%.02f s.", (float)elapsed_time_ / 1000);
	return buf;
}
