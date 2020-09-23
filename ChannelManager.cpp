#include "ChannelManager.h"

void ChannelManager::addChannelToQueue(SleepyDiscord::Channel channel) {
	awaitingDM.push_back(channel);
}

bool ChannelManager::isInQueue(SleepyDiscord::Snowflake<SleepyDiscord::Channel> channel) {
	std::list<SleepyDiscord::Channel>::iterator it = awaitingDM.begin();

	for (it; it != awaitingDM.end(); ++it) {
		if (*it == channel)
			return true;
	}
	return false;
}

SleepyDiscord::Channel ChannelManager::getInstance(SleepyDiscord::Snowflake<SleepyDiscord::Channel> channel) {
	std::list<SleepyDiscord::Channel>::iterator it = awaitingDM.begin();

	for (it; it != awaitingDM.end(); ++it) 
		if (*it == channel)
			return *it;
}