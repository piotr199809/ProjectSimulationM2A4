#include "lock_channel_event.h"

LockChannelEvent::LockChannelEvent(double time, double initial_time, Channel* channel, EventCalender* event_calender):
	Event(time, initial_time), channel_(channel), event_calender_(event_calender)
{
}

void LockChannelEvent::Execute()
{
	channel_->SetStateOfChannel(1);
}

