#ifndef CHANNEL_MANAGER_H
#define CHANNEL_MANAGER_H

#include <list>
#include "dependencies/sleepy-discord/include/sleepy_discord/sleepy_discord.h"

class ChannelManager {
	std::list<SleepyDiscord::Channel> awaitingDM;

public:
	void addChannelToQueue(SleepyDiscord::Channel);

	bool isInQueue(SleepyDiscord::Snowflake<SleepyDiscord::Channel>);

	SleepyDiscord::Channel getInstance(SleepyDiscord::Snowflake<SleepyDiscord::Channel>);
};

#endif