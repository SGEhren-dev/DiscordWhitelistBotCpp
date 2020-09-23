cmake_minimum_required(VERSION 3.6)
project(DiscordWhitelistBot)

add_executable(DiscordWhitelistBot main.cpp Channels.h Member.h MemberManager.h MemberManager.cpp Member.cpp    "Configuration.h" "Configuration.cpp" "ChannelManager.h" "ChannelManager.cpp")

#Link sleepy-discord
add_subdirectory(dependencies/sleepy-discord)
target_link_libraries(DiscordWhitelistBot sleepy-discord)