#ifndef PACKAGE_H
#define PACKAGE_H

#include "transmitter.h"
class Transmitter;

class Package
{
public:
	Package(double generate_time, int id_package, Transmitter* transmitter, double ctp);
	int GetIdPackage();
	Transmitter* GetTransmitter();
	double GetCtpTime();
	double GetGenerateTime();
	int GetCounterLR();
	void IncermentLR();
	void SetDeletionMarker(bool i);
	bool GetDeletionMarker();
	void SetReceiveTime(double time);
	double GetReceiveTime();
	void SetServiceStartTime(double time);
	double GetServiceStartTime();
private:
	double generate_time_;
	double ctp_{ 0 };	 
	double receive_time_{ 0 }; 
	double service_start_time_{ 0 };
	int id_package_;	
	Transmitter* transmitter_;  
	int counterLR_{ 0 };
	bool deletion_marker_{ 0 };
};

#endif
