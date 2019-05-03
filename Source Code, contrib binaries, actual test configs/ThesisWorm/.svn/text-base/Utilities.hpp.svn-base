#ifndef _UTILITIES_HPP
#define _UTILITIES_HPP

#include <string>
#include <sstream>
#include <fstream>

#include <cstdlib>

#include "md5.hpp"

// Boost 1.48.0 was used
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/optional.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/asio.hpp>
#include <boost/regex.hpp> 


// We support the use of the POSIX.1 "environ" unistd.h method of accessing the complete list of environment variables
// Unix supports this and Unix-like compilers on Windows support this.  Even Microsoft's Visual C compiler has some
//	added support for this as per http://technet.microsoft.com/en-us/library/bb463220.aspx although extra steps may
//	still be needed.  This class was developed using MinGW gcc compiler for Windows so MSVC isn't tested.
#include <unistd.h>

// Array of C-strings each with NAME=value pairs and null-terminated
// End of array is indicated by a value of NULL pointer
extern char **environ;

class Utilities {
public:
	// Returns timestamp based on current time and in ISO 8601:2004 format
	//	YYYY-MM-DDThh:mm:ss.fffZ
	// fff is milliseconds.  All values are 0 padded as needed.
	// Timezone is always UTC
	static std::string getCurrentTimestamp();
	
	// Returns boost::optional containing value of environment variable it if exists.  boost::optional with none otherwise
	// name may be case sensitive
	static boost::optional<std::string> getEnvVar(const std::string name);
	
	// Returns a collection of environment variable names (case sensitive) (only the names not the values)
	static std::vector<std::string> getListEnvVarNames();
	
	// Boost has no standard library for secure hash functions.
	// startAddress should be a pointer to where the bytes are in memory for hashing
	// length is the number of bytes (8-bits = 1 octet = 1 byte) to read starting at startAddress
	// Returns hash in hexadecimal or empty string "" if error occurred
	static std::string hash(const unsigned char * const startAddress, const int length);

	// Returns hostname of this machine.  Does not query DNS for multiple possiblities.
	static std::string getHostname();
	
	// Returns vector of strings of IP addresses (IPv4, IPv6, etc) on this host
	static std::vector<std::string> getHostAddresses();
	
	// Creates a filename that is safe for the machine filesystem
	// No easy portable way so just go with basic safe characters that are very common
	static std::string makeSafeFilename(const std::string filename);
	
	/**
	 * @return string with line of input with any \r\n or \n removed
	 */
	static std::string getline(std::istream & is);
};


#endif  /* _UTILITIES_HPP */
