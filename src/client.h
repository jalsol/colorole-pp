#ifndef CLIENT_H_
#define CLIENT_H_

#include <unordered_set>

#include "sleepy_discord/sleepy_discord.h"

#include "utils.h"

namespace sd = SleepyDiscord;

class ClientClass : public sd::DiscordClient {
    std::vector<sd::ServerMember> serverMembers;
    std::unordered_set <sd::Snowflake<sd::Role>> rolesInUse;
    bool memberChunkLoaded = false;
    
    void removeRolesFromUser(
        sd::Server                  server,
        sd::Snowflake<sd::Server> serverID,
        sd::ServerMember            member,
        sd::Snowflake<sd::User>     userID
    );

    void deleteAllUnusedRoles(sd::Snowflake<sd::Server> serverID);

    void assignNewRoleToUser(
        sd::Server                  server,
        sd::Snowflake<sd::Server> serverID,
        sd::Snowflake<sd::User>     userID,
        const std::string&           color
    );

public:
	using sd::DiscordClient::DiscordClient;

    void onMemberChunk(sd::ServerMembersChunk memberChunk) override;
    void onMessage(sd::Message message) override;
};

#endif // CLIENT_H_
