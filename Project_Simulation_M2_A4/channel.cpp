#include "channel.h"

Channel::Channel(Generator* generator) : generator_(generator)
{
}

bool Channel::GetStateOfChannel()
{
	return access_to_channel_;
}

void Channel::SetStateOfChannel(bool state)
{
	access_to_channel_ = state;
}

void Channel::AddPacketToChannel(Package* transmit_packet)
{
	current_transmit_packets_.push_back(transmit_packet);
}

void Channel::DeletePacketsFromChannel()
{
	current_transmit_packets_.clear();
}

int Channel::GetNumberOfPacketsInChannel()
{
	return current_transmit_packets_.size();
}

Transmitter* Channel::GetTransmitterWhoGeneratedPacket(int i)
{
	return current_transmit_packets_[i]->GetTransmitter();
}

Generator* Channel::GetGenerator()
{
	return generator_;
}







