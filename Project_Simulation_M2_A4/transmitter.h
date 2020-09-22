#ifndef TRANSMITTER_H_
#define TRANSMITTER_H_

#include <queue>
#include <vector>
#include "package.h"
#include "generator.h"
#include "network.h"
class Package;
class Network;

class Transmitter
{
public:
	Transmitter(int id, Network* network, Generator* genCTP, Generator* genCGP, Generator* genCRP);
	int GetIdTransmitter();
	int GetIdCurrentGeneratedPacket();
	int GetNumberOfWaitingPackets();
	bool QueueStatus();
	void GeneratePacket();
	void DeletePacketFromQueue();
	Package* FirstPackage();
	void AddWaitingPacketToQueue(Package* new_packet);
	void AddDamagedPacketToVector(Package* damage_packet);
	double GetNumberOfDamagedPackets();
	void IncrementSendPackets();
	double GetNumberOfSendPackets();
	Generator* GetGeneratorCTP();
	Generator* GetGeneratorCGP();
	Generator* GetGeneratorCRP();
	double IncrementNumberOfChecksChannel();
	void ResetNumberOfChecksChannel();
	
private:
	Generator* generatorCTP_ = nullptr;
	Generator* generatorCGP_ = nullptr;
	Generator* generatorCRP_ = nullptr;
	Network* network_ = nullptr;
	std::queue<Package*> waiting_packets_;
	std::vector <Package*> damaged_packets_;
	double number_of_send_packets_{ 0 };
	int id_transmitter_{ 0 };
	int id_packet_{ 0 };
	int number_of_checks_channel_{ 0 };
};
#endif

