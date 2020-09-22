#include "transmitter.h"

Transmitter::Transmitter(int id, Network* network, Generator* genCTP, Generator* genCGP, Generator* genCRP) :
	id_transmitter_(id), network_(network), generatorCTP_(genCTP), generatorCGP_(genCGP), generatorCRP_(genCRP)
{
}

int Transmitter::GetIdTransmitter()
{
	return id_transmitter_;
}

int Transmitter::GetIdCurrentGeneratedPacket()
{
	return id_packet_;
}

int Transmitter::GetNumberOfWaitingPackets()
{
	return waiting_packets_.size();
}

bool Transmitter::QueueStatus()
{
	return waiting_packets_.empty();
}

void Transmitter::GeneratePacket()
{
	++id_packet_;
	double ctp = generatorCTP_->Rand(1, 10);
	Package* new_packet = new Package(network_->GetSimulationTime(), id_packet_, this, ctp);
	AddWaitingPacketToQueue(new_packet);
}

void Transmitter::DeletePacketFromQueue()
{
	waiting_packets_.pop();
}

Package* Transmitter::FirstPackage()
{
	Package* first_package = waiting_packets_.front();
	return first_package;
}

void Transmitter::AddWaitingPacketToQueue(Package* new_packet)
{
	waiting_packets_.push(new_packet);
}

void Transmitter::AddDamagedPacketToVector(Package* damage_packet)
{
	damaged_packets_.push_back(damage_packet);
}

double Transmitter::GetNumberOfDamagedPackets()
{
	return damaged_packets_.size();
}

void Transmitter::IncrementSendPackets()
{
	++number_of_send_packets_;
}

double Transmitter::GetNumberOfSendPackets()
{
	return number_of_send_packets_;
}

Generator* Transmitter::GetGeneratorCTP()
{
	return generatorCTP_;
}

Generator* Transmitter::GetGeneratorCGP()
{
	return generatorCGP_;
}

Generator* Transmitter::GetGeneratorCRP()
{
	return generatorCRP_;
}

double Transmitter::IncrementNumberOfChecksChannel()
{
	++number_of_checks_channel_;
	return number_of_checks_channel_;
}

void Transmitter::ResetNumberOfChecksChannel()
{
	number_of_checks_channel_ = 0;
}




