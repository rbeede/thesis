#include "Utilities.hpp"

std::string Utilities::getCurrentTimestamp() {
	std::stringstream ss;


	// Note that Windows systems don't achieve very accurate millisecond resolution
	// but that is okay as we don't need super accuracy
	boost::posix_time::ptime time = boost::posix_time::microsec_clock::universal_time();

	// We need this to extract milliseconds
	boost::posix_time::time_duration duration(time.time_of_day());
	const int milliseconds = (duration.total_milliseconds() % 1000);

	// Add the first part of the formatted time
	boost::posix_time::time_facet* facet = new boost::posix_time::time_facet("%Y-%m-%dT%H:%M:%S");
	ss.imbue(std::locale(ss.getloc(), facet));
	ss << time;
	ss << "," << milliseconds;
	ss << "Z";  // always UTC

	
	return ss.str();
}


boost::optional<std::string> Utilities::getEnvVar(const std::string name) {
	char * value = std::getenv(name.c_str());  // API promises null termination or NULL
	
	if(NULL == value) {
		return boost::none;
	} else {
		return std::string(value);  //auto-wrapped into boost::optional
	}	
}


std::vector<std::string> Utilities::getListEnvVarNames() {
	std::vector<std::string> names;
	
	for(int i = 0; NULL != environ[i]; i++) {
		std::vector<std::string> tokens;
		
		boost::split(tokens, environ[i], boost::is_any_of("="));
		// Just need the first token which is the name
		names.push_back(tokens.front());
	}
	
	return names;
}


std::string Utilities::hash(const unsigned char * const startAddress, const int length) {
	boost::md5 hashEngine(startAddress, length);
	
	return std::string(hashEngine.digest().hex_str_value(), 32);
}


std::string Utilities::getHostname() {
	return boost::asio::ip::host_name();
}


std::vector<std::string> Utilities::getHostAddresses() {
	boost::asio::io_service io_service;
	boost::asio::ip::tcp::resolver resolver(io_service);
	// Query against the local machine
	boost::asio::ip::tcp::resolver::query query(boost::asio::ip::host_name(),"");

	std::vector<std::string> addresses;
	
	// Loop until end of iterator [end represented by boost::asio::ip::tcp::resolver::iterator()]
	for(boost::asio::ip::tcp::resolver::iterator queryResultIterator = resolver.resolve(query); boost::asio::ip::tcp::resolver::iterator() != queryResultIterator; queryResultIterator++) {
		boost::asio::ip::address addr = queryResultIterator->endpoint().address();

		addresses.push_back(addr.to_string());
	}
	
	return addresses;
}


std::string Utilities::makeSafeFilename(const std::string filename) {
	const boost::regex pattern ("[^a-zA-Z0-9._\\-,]");  // match anything not these
	return boost::regex_replace(filename, pattern, "");
}


std::string Utilities::getline(std::istream & is) {
	std::string line;
	
	std::getline(is, line);
	if(line.size() > 0 && line[line.size() - 1] == '\r') {
		line.resize(line.size() - 1);
	}
	
	return line;
}