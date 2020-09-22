#ifndef LOCK_CHANNEL_EVENT_H_
#define LOCK_CHANNEL_EVENT_H_
#include "event.h"

class LockChannelEvent : public Event
{
public:
	LockChannelEvent(double time, double initial_time, Channel* channel, EventCalender* event_calender);
	void Execute() override;
private:
	Channel* channel_ = nullptr;
	EventCalender* event_calender_ = nullptr;
};
#endif



