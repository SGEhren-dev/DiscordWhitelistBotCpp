#include "Member.h"

Member::Member() {
	this->MemberID = "0";
	this->Name = "NULL";
	this->MinecraftName = "NULL";
	this->memberRoles.push_back(DiscordWhitelistBot::SURVIVALCRAFT);
}

Member::Member(std::string id, std::string name) {
	this->MemberID = id;
	this->Name = name;
	this->MinecraftName = "NULL";
	this->memberRoles.push_back(DiscordWhitelistBot::SURVIVALCRAFT);
}
Member::Member(std::string id, std::string name, std::string mcName) {
	this->MemberID = id;
	this->Name = name;
	this->MinecraftName = mcName;
	this->memberRoles.push_back(DiscordWhitelistBot::SURVIVALCRAFT);
}

Member::Member(std::string id, std::string name, std::string mcName, DiscordWhitelistBot::Role role) {
	this->MemberID = id;
	this->Name = name;
	this->MinecraftName = mcName;
	this->memberRoles.push_back(role);
}

void Member::setMemberID(std::string id) {
	this->MemberID = id;
}

void Member::setName(std::string str) {
	this->Name = str;
}

void Member::setMCName(std::string str) {
	this->MinecraftName = str;
}

void Member::addRole(DiscordWhitelistBot::Role r) {
	this->memberRoles.push_back(r);
}

DiscordWhitelistBot::Role Member::stringToRole(std::string& str) {
	if (str == "699103543562469376")
		return DiscordWhitelistBot::OWNER;
	else if (str == "712668602221985824")
		return DiscordWhitelistBot::HEADADMIN;
	else if (str == "747194790717947943")
		return DiscordWhitelistBot::MODERATOR;
	else if (str == "712696925778083880")
		return DiscordWhitelistBot::YOUTUBE;
	else if (str == "712696764011905054")
		return DiscordWhitelistBot::STREAMER;
	else if (str == "757331872962576436")
		return DiscordWhitelistBot::SURVIVALCRAFT;
	else if (str == "757331960128340008")
		return DiscordWhitelistBot::FTB;
	else
		return DiscordWhitelistBot::SURVIVALCRAFT;
}

std::string& Member::getMemberID() { return this->MemberID; }
std::string& Member::getName() { return this->Name; }
std::string& Member::getMCName() { return this->MinecraftName; }
std::vector<DiscordWhitelistBot::Role>& Member::getRoles() { return this->memberRoles; }

std::string Member::roleToString(DiscordWhitelistBot::Role& r) {
	switch (r) {
	case DiscordWhitelistBot::OWNER:
		return "Owner";
	case DiscordWhitelistBot::HEADADMIN:
		return "Head Admin";
	case DiscordWhitelistBot::MODERATOR:
		return "Moderator";
	case DiscordWhitelistBot::SURVIVALCRAFT:
		return "SurvivalCraft";
	case DiscordWhitelistBot::FTB:
		return "FTB";
	case DiscordWhitelistBot::STREAMER:
		return "Streamer";
	case DiscordWhitelistBot::YOUTUBE:
		return "Youtube";
	default:
		return "Member";
	}
}

DiscordWhitelistBot::Role Member::int64tToRole(int64_t t) {
	if (t == (int64_t)699103543562469376)
		return DiscordWhitelistBot::OWNER;

	else if (t == (int64_t)712668602221985824)
		return DiscordWhitelistBot::HEADADMIN;

	else if (t == (int64_t)712696764011905054)
		return DiscordWhitelistBot::STREAMER;

	else if (t == (int64_t)712696925778083880)
		return DiscordWhitelistBot::YOUTUBE;

	else if (t == (int64_t)747194790717947943)
		return DiscordWhitelistBot::MODERATOR;

	else if (t == (int64_t)757331872962576436)
		return DiscordWhitelistBot::SURVIVALCRAFT;

	else if (t == (int64_t)757331960128340008)
		return DiscordWhitelistBot::FTB;
	
	else {
		return DiscordWhitelistBot::SURVIVALCRAFT;
	}
}

bool Member::hasRole(DiscordWhitelistBot::Role r) {
	std::vector<DiscordWhitelistBot::Role>::iterator it = memberRoles.begin();

	for (it; it != memberRoles.end(); it++) {
		if (*it == r)
			return true;
	}

	return false;
}