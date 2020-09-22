#include "generate_packet_event.h"
#include "lock_channel_event.h"
#include "end_of_transmission_event.h"
#include "transmission_packet_event.h"
#include <string>
#include <cmath>

GeneratePacketEvent::GeneratePacketEvent(double time, double initial_time, Transmitter* transmitter, Network* network,
    Channel* channel, Receiver* receiver, Logger* logger, EventCalender* event_calender) :
	Event(time, initial_time), transmitter_(transmitter), network_(network),
	channel_(channel), receiver_(receiver), logger_(logger), event_calender_(event_calender)
{
}

void GeneratePacketEvent::Execute()
{
	transmitter_->GeneratePacket();
	logger_->Debug("Transmitter " + to_string(transmitter_->GetIdTransmitter()) +
		": Generate packet " + to_string(transmitter_->GetIdCurrentGeneratedPacket()));
	double CGP = transmitter_->GetGeneratorCGP()->RndExp();
	double transmission_time = (transmitter_->FirstPackage()->GetCtpTime());
	const int CTIZ = 1;
	double CP{ 0 };

	event_calender_->push(new GeneratePacketEvent((time_ + CGP), initial_phase_time_,
		transmitter_, network_, channel_, receiver_, logger_, event_calender_));

	if(channel_->GetStateOfChannel() == 0 && transmitter_->GetNumberOfWaitingPackets() == 1)
	{
		//Channel free
		transmitter_->FirstPackage()->SetServiceStartTime(time_);
		channel_->AddPacketToChannel(transmitter_->FirstPackage());
		event_calender_->push(new LockChannelEvent((time_ + 0.001), initial_phase_time_, channel_, event_calender_));
		logger_->Debug("Start transmission packet " + to_string(transmitter_->FirstPackage()->GetIdPackage())
			+ ". Transmission time: " + to_string(transmitter_->FirstPackage()->GetCtpTime()));
		event_calender_->push(new EndOfTransmissionEvent((time_ + transmission_time), initial_phase_time_, transmitter_,
			network_, channel_, receiver_, logger_, event_calender_));
		
	}
	else if(channel_->GetStateOfChannel() == 1 && transmitter_->GetNumberOfWaitingPackets() == 1)
	{
		//Channel busy
		int t = transmitter_->IncrementNumberOfChecksChannel();
		double T = transmitter_->GetGeneratorCTP()->Rand(0, (pow(2, t) - 1));
		CP = T * transmission_time;
		
		event_calender_->push(new TransmissionPacketEvent((time_ + CP), initial_phase_time_, transmitter_,
			network_, channel_, receiver_, logger_, event_calender_));
		logger_->Debug("Channel is busy, waiting for release");
	}
	else if(transmitter_->GetNumberOfWaitingPackets() > 1)
	{
		logger_->Debug("More than one packet in waiting_packets queue");
	}
}

