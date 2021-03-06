/* 
 * File:   Configuration.hpp
 * Author: rbeede
 *
 * Created on March 21, 2012, 6:58 PM
 */

#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP


#include <string>
#include <deque>


class Configuration {
public:
	/* Global variables set by other parts */

	static std::string wormBinaryFullPathname;

	static std::string wormOptionsFileFullPathname;
	
	static std::string updateBinaryFullPathname;
        
	static std::string rootSeed;
	
	static bool isRootSeed;

	static std::deque<std::string> targets;  // Those that still need to be done
};


#endif	/* CONFIGURATION_HPP */

