#include "simulation.h"
#include "event.h"
#include "generate_packet_event.h"
#include <iostream>
#include <ctime>
#include <vector>
#include <fstream>

using namespace std;

Simulation::Simulation(Network* network) : network_(network)
{
}

double Simulation::GetSimulationTime()
{
	return clock_;
}

void Simulation::StartSimulation(double time, double initial_phase_time)
{
	//Main Loop
	int logger_mode{ 1 };
	int mode{ 0 };
	int second = 1000;
	clock_ = 0;
	auto cmp = [](Event* left, Event* right) {return left->GetTime() > right->GetTime(); };
	Event::EventCalender event_calender(cmp);

	cout << "Logger mode[1-All] [2-Info] [3-Debug]: ";
	cin >> logger_mode;
	Logger logger = Logger(logger_mode);
	cout << "Simulation mode: [1-Continuous] [2-Stepper]: ";
	cin >> mode;

	network_->Initialize();

	event_calender.push(new GeneratePacketEvent(network_->GetFirstTransmitter()->GetGeneratorCGP()->RndExp(), initial_phase_time,
		network_->GetFirstTransmitter(), network_, network_->GetChannel(), network_->GetReceiver(), &logger, &event_calender));

	event_calender.push(new GeneratePacketEvent(network_->GetSecondTransmitter()->GetGeneratorCGP()->RndExp(), initial_phase_time,
		network_->GetSecondTransmitter(), network_, network_->GetChannel(), network_->GetReceiver(), &logger, &event_calender));

	event_calender.push(new GeneratePacketEvent(network_->GetThirdTransmitter()->GetGeneratorCGP()->RndExp(), initial_phase_time,
		network_->GetThirdTransmitter(), network_, network_->GetChannel(), network_->GetReceiver(), &logger, &event_calender));

	event_calender.push(new GeneratePacketEvent(network_->GetFourthTransmitter()->GetGeneratorCGP()->RndExp(), initial_phase_time,
		network_->GetFourthTransmitter(), network_, network_->GetChannel(), network_->GetReceiver(), &logger, &event_calender));

	event_calender.push(new GeneratePacketEvent(network_->GetFifthTransmitter()->GetGeneratorCGP()->RndExp(), initial_phase_time,
		network_->GetFifthTransmitter(), network_, network_->GetChannel(), network_->GetReceiver(), &logger, &event_calender));

	event_calender.push(new GeneratePacketEvent(network_->GetSixthTransmitter()->GetGeneratorCGP()->RndExp(), initial_phase_time,
		network_->GetSixthTransmitter(), network_, network_->GetChannel(), network_->GetReceiver(), &logger, &event_calender));

	event_calender.push(new GeneratePacketEvent(network_->GetSeventhTransmitter()->GetGeneratorCGP()->RndExp(), initial_phase_time,
		network_->GetSeventhTransmitter(), network_, network_->GetChannel(), network_->GetReceiver(), &logger, &event_calender));

	event_calender.push(new GeneratePacketEvent(network_->GetEighthTransmitter()->GetGeneratorCGP()->RndExp(), initial_phase_time,
		network_->GetEighthTransmitter(), network_, network_->GetChannel(), network_->GetReceiver(), &logger, &event_calender));

	if(mode == 1)
	{
		while(clock_< time)
		{
			Event* event = event_calender.top();
			clock_ = event->GetTime();
			network_->SetSimulationTime(clock_);
			event_calender.pop();
			event->Execute();
			logger.Debug("Simulation Time: " + to_string(clock_) + "\n");

			if(clock_ >= time)
			{
				double i = network_->AvgPacketErrorRate();
				logger.Info("Average packet error rate: " + to_string(i));
				i = network_->MaxPacketErrorRate();
				logger.Info("Maximum packet error rate: " + to_string(i));
				i = network_->AvgNumberOfRetransmission();
				logger.Info("Average number of retransmissions: " + to_string(i));
				i = network_->SystemBitRate(clock_);
				logger.Info("System bit rate [time = " + to_string(clock_ / 1000) + "s]: " + to_string(i));
				i = network_->AvgPacketDelay();
				logger.Info("Average packet delay: " + to_string(i));
				i = network_->AvgWaitingTime();
				logger.Info("Average waiting time: " + to_string(i));
				i = network_->GetFirstTransmitter()->GetNumberOfSendPackets()
					+ network_->GetSecondTransmitter()->GetNumberOfSendPackets()
					+ network_->GetThirdTransmitter()->GetNumberOfSendPackets()
					+ network_->GetFourthTransmitter()->GetNumberOfSendPackets()
					+ network_->GetFifthTransmitter()->GetNumberOfSendPackets()
					+ network_->GetSixthTransmitter()->GetNumberOfSendPackets()
					+ network_->GetSeventhTransmitter()->GetNumberOfSendPackets()
					+ network_->GetEighthTransmitter()->GetNumberOfSendPackets();
				logger.Info("Number of send packets: " + to_string(i));
			}
		}
	}
	else
	{
		while(clock_ < time)
		{
			Event* event = event_calender.top();
			clock_ = event->GetTime();
			event_calender.pop();
			logger.Debug("Simulation Time: " + to_string(clock_));
			event->Execute();
			cin.get();

			if(clock_ >= time)
			{
				double i = network_->AvgPacketErrorRate();
				logger.Info("Average packet error rate: " + to_string(i));
				i = network_->MaxPacketErrorRate();
				logger.Info("Maximum packet error rate: " + to_string(i));
				i = network_->AvgNumberOfRetransmission();
				logger.Info("Average number of retransmissions: " + to_string(i));
				i = network_->SystemBitRate(clock_);
				logger.Info("System bit rate [time = " + to_string(clock_ / 1000) + "s]: " + to_string(i));
				i = network_->AvgPacketDelay();
				logger.Info("Average packet delay: " + to_string(i));
				i = network_->AvgWaitingTime();
				logger.Info("Average waiting time: " + to_string(i));
			}
		}
	}
}


