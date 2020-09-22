#ifndef EVENT_H_
#define EVENT_H_

#include <queue>
#include <vector>
#include <functional>
#include "network.h"
#include "transmitter.h"
#include "channel.h"
#include "receiver.h"

using namespace std;

class Event
{
public:
	explicit Event(double time, double initial_phase_time);
	virtual void Execute() = 0;
	double GetTime();
	void SetTime(double time);
	typedef  priority_queue<Event*, vector<Event*>, function<bool(Event*, Event*)>> EventCalender;
protected:
	double time_ = 0;
	double initial_phase_time_ = 0;
};
#endif

