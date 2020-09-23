#include "Configuration.h"

int DiscordWhitelistBot::Configuration::createConfigurationFile(std::string& fName) {
	std::fstream file;
	file.open(fName);

	if (!file) {
		std::cerr << "Error in creating the configuration file!";
		return -1;
	}

	std::cout << "[MAIN THREAD] Configuration Created Successfully!" << std::endl;
	return 0;
}