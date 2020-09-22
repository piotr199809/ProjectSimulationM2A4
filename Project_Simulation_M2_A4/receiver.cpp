#include "receiver.h"

Receiver::Receiver()
{
}

void Receiver::AddPacketToReceived(Package* received_packet)
{
	received_packets_.push_back(received_packet);
}

int Receiver::GetNumberOfReceivedPackets()
{
	return received_packets_.size();
}

double Receiver::AvgNumberOfRetransmission()
{
	double counter_all_LR{ 0 };
	for(int i = 0; i < received_packets_.size(); ++i)
	{
		counter_all_LR += received_packets_[i]->GetCounterLR();
	}
	avg_number_of_retransmission_ = counter_all_LR / received_packets_.size();
	return avg_number_of_retransmission_;
}

double Receiver::AvgPacketDelay()
{
	double delay{ 0 };
	for(int i = 0; i < received_packets_.size(); ++i)
	{
		delay += received_packets_[i]->GetReceiveTime() - received_packets_[i]->GetGenerateTime();
	}
	avg_packet_delay_ = delay / received_packets_.size();
	return avg_packet_delay_;
}

double Receiver::AvgWaitingTime()
{
	double waitig_time{ 0 };
	for(int i = 0; i < received_packets_.size(); ++i)
	{
		waitig_time += received_packets_[i]->GetServiceStartTime() - received_packets_[i]->GetGenerateTime();
	}
	avg_waiting_time_ = waitig_time / received_packets_.size();
	return avg_waiting_time_;
}





