#ifndef LOGGER_H_
#define LOGGER_H_
#include <string>
using namespace std;

class Logger
{
public:
	enum class Action
	{
		All,
		Info,
		Debug,
		Error
	};
	Logger();
	~Logger();
	Logger(int i);
	void SetAction(Action action);
	void Info(string message);
	void Error(string message);
	void Debug(string message);
private:
	Action action_ = Action::All;
};
#endif

