#ifndef LOG_H
#define LOG_H

#include <string>
#include <fstream>
#include <ctime>

class Log
{
	Log(){}
	~Log();

	enum MessageType
	{
		DebugInfo,
		Info,
		Warning,
		Error,
		User
	};

	struct Message
	{
		MessageType type;
		std::string text;
		tm when;
	};

	static void SetLevel(MessageType level);
	static void SetOutput(const std::string& filename);
	static void Send(MessageType type, const std::string& text);

	static std::ofstream log_out;
	static std::string lf_name; 
	static MessageType logLevel;
};

#endif