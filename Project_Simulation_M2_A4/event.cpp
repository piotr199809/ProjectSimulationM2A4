#include "event.h"

Event::Event(double time, double initial_phase_time) : time_(time), initial_phase_time_(initial_phase_time)
{
}

void Event::Execute()
{
}

double Event::GetTime()
{
	return time_;
}

void Event::SetTime(double time)
{
	time_ = time;
}