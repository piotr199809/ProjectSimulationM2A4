#ifndef RECEIVER_H_
#define RECEIVER_H_

#include "package.h"
#include <vector>
class Package;

class Receiver
{
public:
	Receiver();
	void AddPacketToReceived(Package* received_packet);
	int GetNumberOfReceivedPackets();
	double AvgNumberOfRetransmission();
	double AvgPacketDelay();
	double AvgWaitingTime();
private:
	std::vector<Package*> received_packets_;
	double avg_number_of_retransmission_{ 0 };
	double avg_packet_delay_{ 0 };
	double avg_waiting_time_{ 0 };
};

#endif
