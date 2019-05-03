#include "Configuration.hpp"

/* C++ requires that static members be initialized too */
std::string Configuration::wormBinaryFullPathname;
std::string Configuration::wormOptionsFileFullPathname;
std::string Configuration::updateBinaryFullPathname;

std::string Configuration::rootSeed;
std::deque<std::string> Configuration::targets;

bool Configuration::isRootSeed;