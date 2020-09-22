#ifndef GENERATE_PACKET_EVENT_
#define GENERATE_PACKET_EVENT_
#include "event.h"
#include "network.h"
#include "logger.h"
#include "lock_channel_event.h"
#include "transmission_packet_event.h"

class GeneratePacketEvent : public Event
{
public:
	GeneratePacketEvent(double time, double initial_time, Transmitter* transmitter, Network* network,
		Channel* channel, Receiver* receiver, Logger* logger, EventCalender* event_calender);
	void Execute() override;
private:
	double next_time_packet_{ 0 }; 
	double max_ctp_{ 0 };
	int id_package_{ 0 };
	Network* network_ = nullptr;
	Channel* channel_ = nullptr;
	Receiver* receiver_ = nullptr;
	Transmitter* transmitter_ = nullptr;
	Logger* logger_ = nullptr;
	EventCalender* event_calender_ = nullptr;
};
#endif

