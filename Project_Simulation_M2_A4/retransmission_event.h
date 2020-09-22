#ifndef RETRANSMISSION_EVENT_H_
#define RETRANSMISSION_EVENT_H_
#include "event.h"
#include "end_of_transmission_event.h"
#include "logger.h"

class RetransmissionEvent : public Event
{
public:
	RetransmissionEvent(double time, double initial_time, Transmitter* transmitter, Network* network,
		Channel* channel, Receiver* receiver, Logger* logger, EventCalender* event_calender);
	void Execute() override;
private:
	int LR_counter_{ 0 };
	Network* network_ = nullptr;
	Channel* channel_ = nullptr;
	Receiver* receiver_ = nullptr;
	Transmitter* transmitter_ = nullptr;
	Logger* logger_ = nullptr;
	EventCalender* event_calender_ = nullptr;
};
#endif

