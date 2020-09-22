#ifndef CHANNEL_H_
#define CHANNEL_H_

#include <vector>
#include "generator.h"
#include "transmitter.h"
#include "package.h"
class Transmitter;
class Package;

class Channel
{
public:
	Channel(Generator* generator);
	bool GetStateOfChannel();
	void SetStateOfChannel(bool state = 0);
	void AddPacketToChannel(Package* transmit_packet);
	Transmitter* GetTransmitterWhoGeneratedPacket(int i);
	Generator* GetGenerator();
	void DeletePacketsFromChannel();
	int GetNumberOfPacketsInChannel();
private:
	bool access_to_channel_{ 0 };
	Transmitter* transmitter_ = nullptr;
	Generator* generator_ = nullptr;
	std::vector<Package*> current_transmit_packets_;
};

#endif

