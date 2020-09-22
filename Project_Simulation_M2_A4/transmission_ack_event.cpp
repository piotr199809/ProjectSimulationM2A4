#include "transmission_ack_event.h"
#include "transmission_packet_event.h"

TransmissionAckEvent::TransmissionAckEvent(double time, double initial_time, Transmitter* transmitter, 
	Network* network, Channel* channel, Receiver* receiver, Logger* logger, EventCalender* event_calender) :
	Event(time, initial_time), transmitter_(transmitter), network_(network),
	channel_(channel), receiver_(receiver), logger_(logger), event_calender_(event_calender)
{
}

void TransmissionAckEvent::Execute()
{
	logger_->Debug("End of transmission ACK.");
	logger_->Debug("Transmitter " + to_string(transmitter_->GetIdTransmitter())
		+ ": Delete packet " + to_string(transmitter_->FirstPackage()->GetIdPackage()));

	if(time_ >= initial_phase_time_)
	{
		transmitter_->FirstPackage()->SetReceiveTime(time_);
		receiver_->AddPacketToReceived(transmitter_->FirstPackage());
		transmitter_->IncrementSendPackets();
	}

	transmitter_->DeletePacketFromQueue();
	channel_->SetStateOfChannel(0);
	channel_->DeletePacketsFromChannel();

	if(!(transmitter_->QueueStatus()))
	{
		logger_->Debug("Transmitter " + to_string(transmitter_->GetIdTransmitter())
			+ ": Attempt to send next packet");
		event_calender_->push(new TransmissionPacketEvent(time_, initial_phase_time_, 
			transmitter_, network_, channel_, receiver_, logger_, event_calender_));
	}
}

