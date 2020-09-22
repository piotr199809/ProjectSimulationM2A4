#include "network.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

Network::Network()
{
}

void Network::Initialize()
{
	int n{ 0 };
	std::ifstream seeds;
	std::string temp;
	std::vector<int> kernels;
	
	std::cout << "Select a seeds file[1-10]: ";
	std::cin >> n;

	if(n > 0 && n < 11)
	{
		seeds.open("seeds" + std::to_string(n) + ".txt");
	}
	else
	{
		seeds.open("seeds1.txt");
	}

	while(std::getline(seeds, temp))
	{
		kernels.push_back(stoi(temp));
	}
	seeds.close();
	
	double lambda;
	double p;

	std::cout << "Enter lambda value: ";
	std::cin >> lambda;
	std::cout << "Enter the probability of error: ";
	std::cin >> p;

	generatorCTP1_ = new Generator(kernels[0], lambda, p);
	generatorCGP1_ = new Generator(kernels[1], lambda, p);
	generatorCRP1_ = new Generator(kernels[2], lambda, p);

	generatorCTP2_ = new Generator(kernels[3], lambda, p);
	generatorCGP2_ = new Generator(kernels[4], lambda, p);
	generatorCRP2_ = new Generator(kernels[5], lambda, p);

	generatorCTP3_ = new Generator(kernels[6], lambda, p);
	generatorCGP3_ = new Generator(kernels[7], lambda, p);
	generatorCRP3_ = new Generator(kernels[8], lambda, p);

	generatorCTP4_ = new Generator(kernels[9], lambda, p);
	generatorCGP4_ = new Generator(kernels[10], lambda, p);
	generatorCRP4_ = new Generator(kernels[11], lambda, p);

	generatorCTP5_ = new Generator(kernels[12], lambda, p);
	generatorCGP5_ = new Generator(kernels[13], lambda, p);
	generatorCRP5_ = new Generator(kernels[14], lambda, p);

	generatorCTP6_ = new Generator(kernels[15], lambda, p);
	generatorCGP6_ = new Generator(kernels[16], lambda, p);
	generatorCRP6_ = new Generator(kernels[17], lambda, p);

	generatorCTP7_ = new Generator(kernels[18], lambda, p);
	generatorCGP7_ = new Generator(kernels[19], lambda, p);
	generatorCRP7_ = new Generator(kernels[20], lambda, p);

	generatorCTP8_ = new Generator(kernels[21], lambda, p);
	generatorCGP8_ = new Generator(kernels[22], lambda, p);
	generatorCRP8_ = new Generator(kernels[23], lambda, p);
	
	channel_generator_ = new Generator(kernels[24], lambda, p);

	first_transmitter_ = new Transmitter(1, this, generatorCTP1_, generatorCGP1_, generatorCRP1_);
	second_transmitter_ = new Transmitter(2, this, generatorCTP2_, generatorCGP2_, generatorCRP2_);
	third_transmitter_ = new Transmitter(3, this, generatorCTP3_, generatorCGP3_, generatorCRP3_);
	fourth_transmitter_ = new Transmitter(4, this, generatorCTP4_, generatorCGP4_, generatorCRP4_);
	fifth_transmitter_ = new Transmitter(5, this, generatorCTP5_, generatorCGP5_, generatorCRP5_);
	sixth_transmitter_ = new Transmitter(6, this, generatorCTP6_, generatorCGP6_, generatorCRP6_);
	seventh_transmitter_ = new Transmitter(7, this, generatorCTP7_, generatorCGP7_, generatorCRP7_);
	eighth_transmitter_ = new Transmitter(8, this, generatorCTP8_, generatorCGP8_, generatorCRP8_);

	channel_ = new Channel(channel_generator_);
	receiver_ = new Receiver();
	
}

double Network::GetSimulationTime()
{
	return simulation_time_;
}

void Network::SetSimulationTime(double time)
{
	simulation_time_ = time;
}

double Network::AvgPacketErrorRate()
{
	double number_of_damaged_packets{ 0 };
	double number_of_received_packets{ 0 };

	number_of_received_packets = (receiver_->GetNumberOfReceivedPackets());
	number_of_damaged_packets = (first_transmitter_->GetNumberOfDamagedPackets() + second_transmitter_->GetNumberOfDamagedPackets()
		+ third_transmitter_->GetNumberOfDamagedPackets() + fourth_transmitter_->GetNumberOfDamagedPackets()
		+ fifth_transmitter_->GetNumberOfDamagedPackets() + sixth_transmitter_->GetNumberOfDamagedPackets()
		+ seventh_transmitter_->GetNumberOfDamagedPackets() + eighth_transmitter_->GetNumberOfDamagedPackets());

	avg_packet_error_rate_ = number_of_damaged_packets / number_of_received_packets;
	return avg_packet_error_rate_;
}

double Network::MaxPacketErrorRate()
{
	std::vector<double>results;
	results.push_back(first_transmitter_->GetNumberOfDamagedPackets() / first_transmitter_->GetNumberOfSendPackets());
	results.push_back(second_transmitter_->GetNumberOfDamagedPackets() / second_transmitter_->GetNumberOfSendPackets());
	results.push_back(third_transmitter_->GetNumberOfDamagedPackets() / third_transmitter_->GetNumberOfSendPackets());
	results.push_back(fourth_transmitter_->GetNumberOfDamagedPackets() / fourth_transmitter_->GetNumberOfSendPackets());
	results.push_back(fifth_transmitter_->GetNumberOfDamagedPackets() / fifth_transmitter_->GetNumberOfSendPackets());
	results.push_back(sixth_transmitter_->GetNumberOfDamagedPackets() / sixth_transmitter_->GetNumberOfSendPackets());
	results.push_back(seventh_transmitter_->GetNumberOfDamagedPackets() / seventh_transmitter_->GetNumberOfSendPackets());
	results.push_back(eighth_transmitter_->GetNumberOfDamagedPackets() / eighth_transmitter_->GetNumberOfSendPackets());

	max_packet_error_rate_ = *std::max_element(results.begin(), results.end());
	return max_packet_error_rate_;
}

double Network::AvgNumberOfRetransmission()
{
	return receiver_->AvgNumberOfRetransmission();
}

double Network::SystemBitRate(double clock)
{
	double time_units = clock / 1000;
	double number_of_received_packets = receiver_->GetNumberOfReceivedPackets();
	system_bit_rate_ = number_of_received_packets / time_units;
	return system_bit_rate_;
}

double Network::AvgPacketDelay()
{
	return receiver_->AvgPacketDelay();
}

double Network::AvgWaitingTime()
{
	return receiver_->AvgWaitingTime();
}






