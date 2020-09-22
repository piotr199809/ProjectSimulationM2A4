#ifndef NETWORK_H_
#define NETWORK_H_

#include "transmitter.h"
#include "receiver.h"
#include "channel.h"

class Channel;
class Transmitter;
class Receiver;

class Network
{
public:
	Network();
	void Initialize();
	double GetSimulationTime();
	void SetSimulationTime(double time);

	double AvgPacketErrorRate();
	double MaxPacketErrorRate();
	double AvgNumberOfRetransmission();
	double SystemBitRate(double clock);
	double AvgPacketDelay();
	double AvgWaitingTime();

	Transmitter* GetFirstTransmitter() { return first_transmitter_; };
	Transmitter* GetSecondTransmitter() { return second_transmitter_; };
	Transmitter* GetThirdTransmitter() { return third_transmitter_; };
	Transmitter* GetFourthTransmitter() { return fourth_transmitter_; };
	Transmitter* GetFifthTransmitter() { return fifth_transmitter_; };
	Transmitter* GetSixthTransmitter() { return sixth_transmitter_; };
	Transmitter* GetSeventhTransmitter() { return seventh_transmitter_; };
	Transmitter* GetEighthTransmitter() { return eighth_transmitter_; };
	
	Channel* GetChannel() { return channel_; };
	Receiver* GetReceiver() { return  receiver_; };
	
private:
	double simulation_time_{ 0 };
	double avg_packet_error_rate_{ 0 };
	double max_packet_error_rate_{ 0 };
	double system_bit_rate_{ 0 };

	Channel* channel_ = nullptr;
	Receiver* receiver_ = nullptr;
	Generator* channel_generator_ = nullptr;
	
	Transmitter* first_transmitter_ = nullptr;
	Transmitter* second_transmitter_ = nullptr;
	Transmitter* third_transmitter_ = nullptr;
	Transmitter* fourth_transmitter_ = nullptr;
	Transmitter* fifth_transmitter_ = nullptr;
	Transmitter* sixth_transmitter_ = nullptr;
	Transmitter* seventh_transmitter_ = nullptr;
	Transmitter* eighth_transmitter_ = nullptr;
	
	Generator* generatorCTP1_ = nullptr;
	Generator* generatorCGP1_ = nullptr;
	Generator* generatorCRP1_ = nullptr;

	Generator* generatorCTP2_ = nullptr;
	Generator* generatorCGP2_ = nullptr;
	Generator* generatorCRP2_ = nullptr;

	Generator* generatorCTP3_ = nullptr;
	Generator* generatorCGP3_ = nullptr;
	Generator* generatorCRP3_ = nullptr;

	Generator* generatorCTP4_ = nullptr;
	Generator* generatorCGP4_ = nullptr;
	Generator* generatorCRP4_ = nullptr;

	Generator* generatorCTP5_ = nullptr;
	Generator* generatorCGP5_ = nullptr;
	Generator* generatorCRP5_ = nullptr;

	Generator* generatorCTP6_ = nullptr;
	Generator* generatorCGP6_ = nullptr;
	Generator* generatorCRP6_ = nullptr;

	Generator* generatorCTP7_ = nullptr;
	Generator* generatorCGP7_ = nullptr;
	Generator* generatorCRP7_ = nullptr;

	Generator* generatorCTP8_ = nullptr;
	Generator* generatorCGP8_ = nullptr;
	Generator* generatorCRP8_ = nullptr;
	
};

#endif

