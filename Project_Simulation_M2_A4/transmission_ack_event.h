#ifndef TRANSMISSION_ACK_EVENT_H_
#define TRANSMISSION_ACK_EVENT_H_
#include "event.h"
#include "logger.h"

class TransmissionAckEvent : public Event
{
public:
	TransmissionAckEvent(double time, double initial_time, Transmitter* transmitter, Network* network,
		Channel* channel, Receiver* receiver, Logger* logger, EventCalender* event_calender);
	void Execute() override;
private:
	Transmitter* transmitter_ = nullptr;
	Network* network_ = nullptr;
	Channel* channel_ = nullptr;
	Receiver* receiver_ = nullptr;
	Logger* logger_ = nullptr;
	EventCalender* event_calender_ = nullptr;
};
#endif

