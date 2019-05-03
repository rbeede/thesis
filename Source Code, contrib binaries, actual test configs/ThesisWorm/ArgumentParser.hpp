/* 
 * File:   ArgumentParser.hpp
 * Author: rbeede
 *
 * Created on March 21, 2012, 6:54 PM
 */

#ifndef ARGUMENTPARSER_HPP
#define	ARGUMENTPARSER_HPP

#include <string>
#include <fstream>
#include <iostream>

#include <locale>

// Use of Boost's unofficial utf8_codecvt_facet is used for now because it is portable
// It isn't a very clean interface (as of Boost 1.48.0) and should be replaced when (if) a better library is developed
//	either by Boost or another party.  UTF-8 support in general in C++ isn't very easy although the C++11 has some
//	promise of improving this state of affairs.
#include "utf8_codecvt_facet.hpp"


// Need to use v3 to ensure we get boost::filesystem::complete (which is now named absolute(...))
#define BOOST_FILESYSTEM_NO_DEPRECATED

#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"


#include "logger.hpp"
extern Logger * logger;

#include "Configuration.hpp"

#include "Utilities.hpp"


class ArgumentParser {
public:
	/**
	 * Parses arguments and sets global variables or configuration as needed
	 * 
	 * If arguments are invalid should output to global extern "logger" variable which is already available
	 * 
	 * Returns:  true if successful, false otherwise.
	 */
	static bool parse(const int argc, const char * const argv[]);
	
};

#endif	/* ARGUMENTPARSER_HPP */

