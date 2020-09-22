#ifndef END_OF_TRANSMISSION_EVENT_H_
#define END_OF_TRANSMISSION_EVENT_H_
#include "event.h"
#include "receiver.h"
#include "logger.h"

class EndOfTransmissionEvent : public Event
{
public:
	EndOfTransmissionEvent(double time, double initial_time, Transmitter* transmitter, Network* network, 
		Channel* channel, Receiver* receiver, Logger* logger, EventCalender* event_calender);
	void Execute() override;
private:
	double end_transmission_time_{ 0 };
	Network* network_ = nullptr;
	Channel* channel_ = nullptr;
	Receiver* receiver_ = nullptr;
	Transmitter* transmitter_ = nullptr;
	Logger* logger_ = nullptr;
	EventCalender* event_calender_ = nullptr;
};

#endif
