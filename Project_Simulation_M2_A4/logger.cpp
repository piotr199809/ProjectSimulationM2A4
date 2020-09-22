#include "logger.h"
#include <iostream>

Logger::Logger()
{
}

Logger::~Logger()
{
}

Logger::Logger(int i)
{
	switch (i)
	{
	case 1:
		action_ = Logger::Action::All; break;
	case 2:
		action_ = Logger::Action::Info; break;
	case 3:
		action_ = Logger::Action::Debug; break;
	}
}

void Logger::SetAction(Action action)
{
	action_ = action;
}

void Logger::Info(string message)
{
	if(action_ == Action::Info || action_ == Action::All)
	{
		std::cout << "[Info]: " << message << endl;
	}
}

void Logger::Debug(string message)
{
	if (action_ == Action::Debug || action_ == Action::All)
	{
		std::cout << "[Debug]: " << message << endl;
	}
}

void Logger::Error(string message)
{
	if (action_ == Action::Error || action_ == Action::All)
	{
		std::cout << "[Error]: " << message << endl;
	}
}

