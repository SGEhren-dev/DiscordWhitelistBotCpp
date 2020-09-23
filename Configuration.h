#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <string>
#include <iostream>
#include <fstream>

namespace DiscordWhitelistBot {
	namespace Configuration {

		int createConfigurationFile(std::string&);
		int openConfigurationFile(FILE* f);

		bool fileExists(FILE* f);
	}
}

#endif