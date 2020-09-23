#ifndef MEMBER_H
#define MEMBER_H

#include <string>
#include <vector>

namespace DiscordWhitelistBot {
	enum Role {
		OWNER,
		HEADADMIN,
		MODERATOR,
		SURVIVALCRAFT,
		FTB,
		STREAMER,
		YOUTUBE
	};
}

class Member {
	std::string Name;
	std::string MinecraftName;
	std::string MemberID;

	std::vector<DiscordWhitelistBot::Role> memberRoles;

public:
	Member();
	Member(std::string, std::string);
	Member(std::string, std::string, std::string);
	Member(std::string, std::string, std::string, DiscordWhitelistBot::Role);

	std::vector<DiscordWhitelistBot::Role>& getRoles();
	std::string& getName();
	std::string& getMCName();
	std::string& getMemberID();

	std::string roleToString(DiscordWhitelistBot::Role&);
	std::string int64tToString(int64_t& t);

	void addRole(DiscordWhitelistBot::Role);
	void setName(std::string);
	void setMCName(std::string);
	void setMemberID(std::string);

	DiscordWhitelistBot::Role stringToRole(std::string&);
	DiscordWhitelistBot::Role int64tToRole(int64_t t);

	bool hasRole(DiscordWhitelistBot::Role);
};

#endif