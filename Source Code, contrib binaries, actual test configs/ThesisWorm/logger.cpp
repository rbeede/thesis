#include "logger.hpp"

		
void Logger::log(const std::string message) {
	logstream << Utilities::getCurrentTimestamp();
	logstream << "\t";
	logstream << message;
	logstream << "\r\n";
	logstream.flush();
}
		
		
Logger::~Logger() { logstream.close(); }


Logger::Logger(const std::string logFilePathname)
	: logFilePathname(logFilePathname)
{
	std::locale utf8locale(std::locale(), new boost::unofficial::library::utf8_codecvt_facet);
	
	logstream.imbue(utf8locale);  // recommended to do before open call as some platforms get inconsistent otherwise
			
	// Setup the log file
	logstream.open(logFilePathname.c_str(), std::ios::out | std::ios::binary);
	//TODO check open results incase it failed
	// Write the UTF-8 BOM
	logstream << (unsigned char) 0xEF << (unsigned char) 0xBB << (unsigned char) 0xBF;
}
