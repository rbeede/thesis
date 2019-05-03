/*
 * Rodney Beede
 *
 * 2012-02-23
 *
 * Log is stored in UTF-8 encoding with the proper BOM at the beginning
 * 
*/

#ifndef _LOGGER_H
#define _LOGGER_H

#include <iostream>
#include <string>
#include <fstream>

#include <locale>

// Use of Boost's unofficial utf8_codecvt_facet is used for now because it is portable
// It isn't a very clean interface (as of Boost 1.48.0) and should be replaced when (if) a better library is developed
//	either by Boost or another party.  UTF-8 support in general in C++ isn't very easy although the C++11 has some
//	promise of improving this state of affairs.
#include "utf8_codecvt_facet.hpp"

#include "Utilities.hpp"

class Logger {
	public:
		// Constructor
		// Opens log file located at logFilePathname for writing (truncates any existing file)
		Logger(const std::string logFilePathname);
		
		// Records the message to the log preceded by a timestamp and with a newline (CRLF) added for you at the end
		void log(const std::string message);
		
		// Destructor
		// Closes log file
		~Logger();
		
	private:
		const std::string logFilePathname;
		
		std::ofstream logstream;
};


#endif  /* _LOGGER_H */

