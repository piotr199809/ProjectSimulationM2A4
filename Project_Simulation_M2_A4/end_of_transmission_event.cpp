#include "end_of_transmission_event.h"
#include "event.h"
#include "retransmission_event.h"
#include "transmission_ack_event.h"
#include <cmath>

EndOfTransmissionEvent::EndOfTransmissionEvent(double time, double initial_time, Transmitter* transmitter,
    Network* network, Channel* channel, Receiver* receiver, Logger* logger, EventCalender* event_calender) :
	Event(time, initial_time), transmitter_(transmitter), network_(network),
	channel_(channel), receiver_(receiver), logger_(logger), event_calender_(event_calender)
{
}

void EndOfTransmissionEvent::Execute()
{
	const int CTIZ = 1;
	int LR{ 0 };
	double CRP{ 0 };

	if(transmitter_->FirstPackage()->GetDeletionMarker() == 0)
	{
		if(channel_->GetNumberOfPacketsInChannel() == 1)
		{
			bool error = channel_->GetGenerator()->RndZeroOne();
			if(error == 0)
			{
				logger_->Debug("A packet " + to_string(transmitter_->FirstPackage()->GetIdPackage())
					+ " was received from transmitter " + to_string(transmitter_->GetIdTransmitter())
					+ ", start of transmission ACK");
				event_calender_->push(new TransmissionAckEvent((time_ + CTIZ), initial_phase_time_,
					transmitter_, network_, channel_, receiver_, logger_, event_calender_));
			}
			else
			{
				double transmission_time = transmitter_->FirstPackage()->GetCtpTime();
				LR = transmitter_->FirstPackage()->GetCounterLR();
				double R = transmitter_->GetGeneratorCRP()->Rand(0, (pow(2, LR) - 1));
				CRP = R * transmission_time;
				logger_->Debug("Error in channel. Retransmission packet " +
					to_string(transmitter_->FirstPackage()->GetIdPackage()) + " from transmitter "
					+ to_string(transmitter_->GetIdTransmitter()) + " will take place in " + to_string(CRP + CTIZ));
				event_calender_->push(new RetransmissionEvent((time_ + CTIZ + CRP), initial_phase_time_,
					transmitter_, network_, channel_, receiver_, logger_, event_calender_));
				transmitter_->FirstPackage()->SetDeletionMarker(1);
				channel_->DeletePacketsFromChannel();
				channel_->SetStateOfChannel(0);
			}
		}
		else
		{
			logger_->Debug("More than one packet in channel");
			int num_of_packet = channel_->GetNumberOfPacketsInChannel();
			double transmission_time;

			for(int i = 0; i < num_of_packet; ++i)
			{
				transmitter_ = channel_->GetTransmitterWhoGeneratedPacket(i);
				transmitter_->FirstPackage()->SetDeletionMarker(1);
				transmission_time = transmitter_->FirstPackage()->GetCtpTime();
				LR = transmitter_->FirstPackage()->GetCounterLR();
				double R = transmitter_->GetGeneratorCRP()->Rand(0, (pow(2, LR) - 1));
				CRP = R * transmission_time;
				event_calender_->push(new RetransmissionEvent((time_ + CTIZ + CRP), initial_phase_time_,
					transmitter_, network_, channel_, receiver_, logger_, event_calender_));
				logger_->Debug("Retransmission packet" + to_string(transmitter_->FirstPackage()->GetIdPackage())
					+ " from transmitter " + to_string(transmitter_->GetIdTransmitter()) + " will take palace in "
					+ to_string(CRP + CTIZ));
			}
			channel_->DeletePacketsFromChannel();
			channel_->SetStateOfChannel(0);
		}
	}
}

