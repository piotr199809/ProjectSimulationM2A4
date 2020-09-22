


#include "transmission_packet_event.h"

TransmissionPacketEvent::TransmissionPacketEvent(double time, double initial_time, Transmitter* transmitter,
	Network* network, Channel* channel, Receiver* receiver, Logger* logger, EventCalender* event_calender) :
	Event(time, initial_time), transmitter_(transmitter), network_(network), channel_(channel),
	receiver_(receiver), logger_(logger), event_calender_(event_calender)
{
}

void TransmissionPacketEvent::Execute()
{
	double transmission_time = transmitter_->FirstPackage()->GetCtpTime();
	double CP{ 0 };
	

	if(channel_->GetStateOfChannel() == 0)
	{
		transmitter_->ResetNumberOfChecksChannel();
		if(transmitter_->FirstPackage()->GetCounterLR() == 0)
		{
			transmitter_->FirstPackage()->SetServiceStartTime(time_);
		}
		channel_->AddPacketToChannel(transmitter_->FirstPackage());
		event_calender_->push(new LockChannelEvent((time_ + 0.001), initial_phase_time_, channel_, event_calender_));
		logger_->Debug("Transmitter " + to_string(transmitter_->GetIdTransmitter()) 
			+ " Start transmission packet " + to_string(transmitter_->FirstPackage()->GetIdPackage())
			+ ". Transmission time: " + to_string(transmitter_->FirstPackage()->GetCtpTime()));
		event_calender_->push(new EndOfTransmissionEvent((time_ + transmission_time), initial_phase_time_,
			transmitter_, network_, channel_, receiver_, logger_, event_calender_));
	}
	else
	{
		int t = transmitter_->IncrementNumberOfChecksChannel();
		double T = transmitter_->GetGeneratorCTP()->Rand(0, (pow(2, t) - 1));
		CP = T * transmission_time;
		event_calender_->push(new TransmissionPacketEvent(time_ + CP, initial_phase_time_, transmitter_, network_,
			channel_, receiver_, logger_, event_calender_));
	}
}

