#include "Channels.h"
#include <iostream>
#include "dependencies/sleepy-discord/include/sleepy_discord/sleepy_discord.h"
#include "MemberManager.h"
#include "dependencies/sampquerycpp-master/sampquerycpp-master/rcon.h"
#include "ChannelManager.h"

#ifndef DEBUG
#define DEBUG
#define LOG(str) std::clog << "[DEBUG] " << str << std::endl;
#else
#define LOG(str)
#endif

using namespace SleepyDiscord;

//Method prototypes
std::queue<std::string> split(const std::string& source);
void strToBinary(std::string);
std::string string_to_hex(const std::string& input);
int hex_value(unsigned char hex_digit);
std::string hex_to_string(const std::string& input);

class ClientClass : public SleepyDiscord::DiscordClient {
    MemberManager memberManager;                                    //Create a new MemberManager object each time a new ClientClass is created (On bot start)
    ChannelManager channelManager;                                  //Create a new ChannelManager object each time a new ClientClass is created (On bot start)

    std::list<ServerMember> membersOnServer;

public:
    using SleepyDiscord::DiscordClient::DiscordClient;
    //Override for onMessage
    void onMessage(SleepyDiscord::Message message) override {
        if (message.startsWith("/whitelist")) {
            LOG(message.author.username << " issued command /whitelist");
            std::queue<std::string> parameters = split(message.content);

            if (parameters.size() <= 1)
                return;

            if (parameters.size() > 2)
                sendMessage(message.channelID, "Please be sure to use /whitelist 'playerName'");

            //Remove parameters as we go
            parameters.pop();
            //If the parameters are empty, then just return
            if (parameters.empty())
                return;

            //Make sure the parameter being passed isn't NULL or 0
            if (parameters.front().size() > 0)
                sendMessage(message.channelID, "Awaiting moderator approval to whitelist " + parameters.front() + "!");

            //Send the approval message to the moderator channel
            sendMessage(CHANNEL_MODERATORS, "Awaiting approval to whitelist " + parameters.front() + "!");

            //Get rid of the last parameter
            parameters.pop();
        }
        else if (message.startsWith("/mcusername")) {
            LOG(message.author.username << " issued command /mcusername");
            std::queue<std::string> parameters = split(message.content);

            if (parameters.size() <= 1) {
                sendMessage(message.channelID, "Incorrect command usage (If username contains a space, use an underscore)! /mcusername 'username'");
                return;
            }

            if (parameters.size() > 2) {
                sendMessage(message.channelID, "Incorrect command usage (If username contains a space, use an underscore)! /mcusername 'username'");
                return;
            }

            parameters.pop();

            Member member(message.author.ID, message.author.username);                              //Create a new member to find an instance of the member
            Member instanceOfMember;                                                                //Used to store the instance of a member
            if (parameters.front().size() > 0) {
                if (memberManager.isMember(member)) {
                    instanceOfMember = memberManager.getInstanceOfMember(member);
                    instanceOfMember.setMCName(parameters.front());
                    sendMessage(message.channelID, message.author.username + " your Minecraft name has been updated!");
                }
                else {
                    member.setMCName(parameters.front());
                    sendMessage(message.channelID, message.author.username + " your Minecraft name has been set!");
                    memberManager.addMember(member);
                }
            }
            parameters.pop();                                                                       //make sure our queue is empty
        }
        else if (message.startsWith("/updateusers")) {
            LOG(message.author.username << " issued command /updateusers");
            for (ServerMember mem : membersOnServer) {
                Member member(
                    mem.user.ID,
                    mem.user.username
                );

                if (!memberManager.isMember(member))
                    memberManager.addMember(member);
            }
        }
        else if (message.startsWith("/printinfo")) {
            ServerMember mem;
            mem.user = message.author;

            Member member(
                mem.user.ID,
                mem.user.username
            );

            Member& instance = memberManager.getInstanceOfMember(member);
            sendMessage(CHANNEL_GENERAL, "[DEBUG] " + instance.getMemberID() + ", " + instance.getName() + ", " + instance.getMCName() + ".");
        }
        else if (channelManager.isInQueue(message.channelID) && (message.author.ID != this->getID())) {
            Channel messageChannel = channelManager.getInstance(message.channelID);
            LOG(message.content);
            Member member = memberManager.getInstanceOfMember(Member(
                message.author.ID,
                message.author.username
            ));
            //Debug purposes only!!!
            std::vector<Member> members = memberManager.getMemberVector();
            for (Member m : members) {
                LOG("ID: " << m.getMemberID() << ", Name: " << m.getName() << ", MCName: " << m.getMCName());
            }
            std::cout << '\n';
            LOG("ID: " << member.getMemberID() << ", Name: " << member.getName() << ", MCName: " << member.getMCName());
            std::cout << '\n';
            member.setMCName(message.content);
            std::cout << '\n';
            LOG("ID: " << member.getMemberID() << ", Name: " << member.getName() << ", MCName: " << member.getMCName());
            std::cout << '\n';
            memberManager.getInstanceOfMember(Member(
                message.author.ID,
                message.author.username
            )).setMCName(message.content);
            sendMessage(messageChannel, "Your information will be updated!");

            //Debug purposes only!!!
            std::vector<Member> members1 = memberManager.getMemberVector();
            for (Member m : members1) {
                LOG("ID: " << m.getMemberID() << ", Name: " << m.getName() << ", MCName: " << m.getMCName());
            }
        }
        else if (message.startsWith("/testdm")) {
        LOG(message.author.username << " issued command /testdm");
        //Create a DirectMessage to get the MC username of the new user
        ObjectResponse<Channel> channel = SleepyDiscord::DiscordClient::createDirectMessageChannel(message.author.ID);
        Channel castedChannel = channel.cast();
        channelManager.addChannelToQueue(castedChannel);
        sendMessage(castedChannel, "[SurvivalCraft] Please send me your Minecraft Username so I can add you to our records!");
        }
    }

    //Override for onReaction
    void onReaction(Snowflake<User> userID, Snowflake<Channel> channelID, Snowflake<Message> messageID, Emoji emoji) override {
        LOG("[EMOJI] Reacted with " + (string_to_hex(emoji.name)));                                                                         //Log every emoji sent to the server

        if (channelID == CHANNEL_MODERATORS && string_to_hex(emoji.name) == "E29D8C") {
            sendMessage(CHANNEL_MODERATORS, "They will not be added!");
            sendMessage(CHANNEL_GENERAL, "The last requested user was denied by a moderator.");
        }
        else if (channelID == CHANNEL_MODERATORS && string_to_hex(emoji.name) == "E29C85") {
            sendMessage(CHANNEL_MODERATORS, "They will now be added");
            sendMessage(CHANNEL_GENERAL, "The last requested user was approved by a moderator!");
        }
    }

    /// <summary>
    /// This method is called when the bot joins a new server.
    /// All members will be added to a list, these members will then be added to the memberManager instance for future reference,
    /// then, the user will be pulled individually and their roles will be added and updated (for Essentials support)
    /// </summary>
    /// <param name="server">The server the bot is joining</param>
    void onServer(SleepyDiscord::Server server) override {
        LOG("Joined Server");
        //Get the members from server.members and push them into the memberOnServers vector
        for (ServerMember mem : server.members) {
            membersOnServer.push_back(mem);
        }

        //Foreach member in membersOnServer, we want to create a new member object. If they don't exist, then we want to add them
        //to the memberManager
        for (ServerMember mem : membersOnServer) {
            Member member(
                mem.user.ID,
                mem.user.username
            );

            if (!memberManager.isMember(member))
                memberManager.addMember(member);
        }

        /*
        * Foreach member in membersOnServer, we want to get an instance of an existing Member, then get their roles from the server,
        * iterate through each role in the list and add it to the users role list
        */
        for (ServerMember mem : membersOnServer) {
            Member& member = memberManager.getInstanceOfMember(Member(mem.user.ID, mem.user.username));

            std::vector<Snowflake<Role>>::iterator it;

            //Iterate through the roles of the user and push them to the roles
            for (it = mem.roles.begin(); it != mem.roles.end(); it++) {
                if (!member.hasRole(member.int64tToRole(it->number()))) {
                    member.addRole(member.int64tToRole(it->number()));
                }
            }
        }

        //Debug purposes only!!!
        std::vector<Member> members = memberManager.getMemberVector();
        for (Member m : members) {
            LOG("ID: " << m.getMemberID() << ", Name: " << m.getName() << ", MCName: " << m.getMCName());
        }
    }

    //Called each time a member joins the server (Eventually will add DM support to get their usernames so they dont have to enter their username)
    void onMember(Snowflake<Server> serverID, SleepyDiscord::ServerMember member) override {
        LOG("New Member");
        if (!memberManager.isMember(Member(
            member.user.ID,
            member.user.username
        ))) {
            memberManager.addMember(Member(
                member.user.ID,
                member.user.username
            ));
        }

        //Create a DirectMessage to get the MC username of the new user
        ObjectResponse<Channel> channel = SleepyDiscord::DiscordClient::createDirectMessageChannel(member.user.ID);
        Channel castedChannel = channel.cast();
        channelManager.addChannelToQueue(castedChannel);
        sendMessage(castedChannel, "[SurvivalCraft] Please send me your Minecraft Username so I can add you to our records!");
    }
};

int main() {
    ClientClass client("", SleepyDiscord::USER_CONTROLED_THREADS);
    client.run();
}

std::queue<std::string> split(const std::string& source) {
    std::stringstream ss(source);
    std::string item;
    std::queue<std::string> target;
    while (std::getline(ss, item, ' '))
        if (!item.empty())
            target.push(item);
    return target;
}

void strToBinary(std::string s) {
    int n = s.length();

    for (int i = 0; i < n; i++) {
        int val = int(s[i]);

        std::string bin = "";
        while (val > 0) {
            (val % 2) ? bin.push_back('1') : bin.push_back('0');

            val /= 2;
        }
        std::reverse(bin.begin(), bin.end());

        std::cout << bin << " ";
    }
}

std::string string_to_hex(const std::string& input)
{
    static const char hex_digits[] = "0123456789ABCDEF";

    std::string output;
    output.reserve(input.length() * 2);
    for (unsigned char c : input)
    {
        output.push_back(hex_digits[c >> 4]);
        output.push_back(hex_digits[c & 15]);
    }
    return output;
}

#include <stdexcept>

int hex_value(unsigned char hex_digit)
{
    static const signed char hex_values[256] = {
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
         0,  1,  2,  3,  4,  5,  6,  7,  8,  9, -1, -1, -1, -1, -1, -1,
        -1, 10, 11, 12, 13, 14, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, 10, 11, 12, 13, 14, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    };
    int value = hex_values[hex_digit];
    if (value == -1) throw std::invalid_argument("invalid hex digit");
    return value;
}

std::string hex_to_string(const std::string& input)
{
    const auto len = input.length();
    if (len & 1) throw std::invalid_argument("odd length");

    std::string output;
    output.reserve(len / 2);
    for (auto it = input.begin(); it != input.end(); )
    {
        int hi = hex_value(*it++);
        int lo = hex_value(*it++);
        output.push_back(hi << 4 | lo);
    }
    return output;
}