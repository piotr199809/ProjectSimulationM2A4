#include "package.h"

Package::Package(double generate_time, int id_package, Transmitter* transmitter, double ctp) :
	generate_time_(generate_time), id_package_(id_package), transmitter_(transmitter), ctp_(ctp)
{
}

int Package::GetIdPackage()
{
	return id_package_;
}

Transmitter* Package::GetTransmitter()
{
	return transmitter_;
}

double Package::GetCtpTime()
{
	return ctp_;
}

double Package::GetGenerateTime()
{
	return generate_time_;
}

int Package::GetCounterLR()
{
	return counterLR_;
}

void Package::IncermentLR()
{
	++counterLR_;
}

void Package::SetDeletionMarker(bool i)
{
	deletion_marker_ = i;
}

bool Package::GetDeletionMarker()
{
	return deletion_marker_;
}

void Package::SetReceiveTime(double time)
{
	receive_time_ = time;
}

double Package::GetReceiveTime()
{
	return receive_time_;
}

void Package::SetServiceStartTime(double time)
{
	service_start_time_ = time;
}

double Package::GetServiceStartTime()
{
	return service_start_time_;
}










