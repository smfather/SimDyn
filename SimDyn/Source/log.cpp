#include "log.h"
#include <iostream>

std::string Log::lf_name;
std::ofstream Log::log_out;
Log::MessageType Log::logLevel = Log::DebugInfo;

void Log::Send(MessageType type, const std::string& text)
{
	if ((int)type < (int)logLevel)
		return;

	Log::Message m;
	m.type = type;
	m.text = text;
	time_t t = time(NULL);
	localtime_s(&m.when, &t);

	if (log_out.is_open()){
		char buffer[9];
		strftime(buffer, 9, "%X", &m.when);
		log_out << buffer;

		switch (type)
		{
		case DebugInfo: log_out << " | debug   | "; break;
		case Info:		log_out << " | info    | "; break;
		case Warning:   log_out << " | warning | "; break;
		case Error:     log_out << " | ERROR   | "; break;
		default:		log_out << " | user    | ";
		}
		log_out << text << std::endl;
	}
}

void Log::SetOutput(const std::string& filename)
{
	lf_name = filename;

	// close old one
	if (log_out.is_open())
		log_out.close();

	// create file
	log_out.open(filename.c_str());
}

void Log::SetLevel(MessageType level)
{
	logLevel = level;
}

Log::~Log()
{
	if (log_out.is_open())
		log_out.close();
}