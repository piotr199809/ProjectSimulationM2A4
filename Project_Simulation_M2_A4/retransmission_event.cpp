#include "retransmission_event.h"
#include "lock_channel_event.h"
#include "transmission_packet_event.h"

RetransmissionEvent::RetransmissionEvent(double time, double initial_time, Transmitter* transmitter,
    Network* network, Channel* channel, Receiver* receiver, Logger* logger, EventCalender* event_calender) :
	Event(time, initial_time), transmitter_(transmitter), network_(network),
	channel_(channel), receiver_(receiver), logger_(logger), event_calender_(event_calender)
{
}

void RetransmissionEvent::Execute()
{
	double CP{ 0 };
	
	transmitter_->FirstPackage()->IncermentLR();
	logger_->Debug("Retransmission packet " + to_string(transmitter_->FirstPackage()->GetIdPackage())
		+ " from transmitter " + to_string(transmitter_->GetIdTransmitter()) + ". LR = "
		+ to_string(transmitter_->FirstPackage()->GetCounterLR()));

	transmitter_->FirstPackage()->SetDeletionMarker(0);

	if(transmitter_->FirstPackage()->GetCounterLR() < 10)
	{
		double transmission_time = transmitter_->FirstPackage()->GetCtpTime();

		if(channel_->GetStateOfChannel() == 0)
		{
			channel_->AddPacketToChannel(transmitter_->FirstPackage());
			logger_->Debug("Start transmission packet " + to_string(transmitter_->FirstPackage()->GetIdPackage())
				+ ". Transmission time: " + to_string(transmitter_->FirstPackage()->GetCtpTime()));
			event_calender_->push(new EndOfTransmissionEvent((time_ + transmission_time), initial_phase_time_,
				transmitter_, network_, channel_, receiver_, logger_, event_calender_));
			event_calender_->push(new LockChannelEvent((time_ + 0.001), initial_phase_time_, channel_, event_calender_));
		}
		else
		{
			int t = transmitter_->IncrementNumberOfChecksChannel();
			double T = transmitter_->GetGeneratorCTP()->Rand(0, (pow(2, t) - 1));
			CP = T * transmission_time;
			
			logger_->Debug("Channel is busy, waiting for release ");
			event_calender_->push(new TransmissionPacketEvent(time_ + CP, initial_phase_time_,
				transmitter_, network_, channel_, receiver_, logger_, event_calender_));
		}
	}
	else
	{
		logger_->Debug("removing the packet, number of retransmission > 10");
		if (time_ >= initial_phase_time_) transmitter_->AddDamagedPacketToVector(transmitter_->FirstPackage());
		transmitter_->DeletePacketFromQueue();
		if(!(transmitter_->QueueStatus()))
		{
			logger_->Debug("Transmitter " + to_string(transmitter_->GetIdTransmitter()) + ": Attempt to send next packet");
			event_calender_->push(new TransmissionPacketEvent(time_, initial_phase_time_,
				transmitter_, network_, channel_, receiver_, logger_, event_calender_));
		}
	}
}

