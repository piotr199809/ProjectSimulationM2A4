#ifndef TRANSMISSION_PACKET_EVENT_H_
#define TRANSMISSION_PACKET_EVENT_H_
#include "event.h"
#include "end_of_transmission_event.h"
#include "retransmission_event.h"
#include "lock_channel_event.h"
#include "logger.h"

class TransmissionPacketEvent : public Event
{
public:
	TransmissionPacketEvent(double time, double initial_time, Transmitter* transmitter, Network* network,
		Channel* channel, Receiver* receiver, Logger* logger, EventCalender* event_calender);
	void Execute() override;
private:
	Network* network_ = nullptr;
	Channel* channel_ = nullptr;
	Receiver* receiver_ = nullptr;
	Transmitter* transmitter_ = nullptr;
	Logger* logger_ = nullptr;
	EventCalender* event_calender_;
};

#endif

