#include "sleepy_discord/sleepy_discord.h"

#include "client.h"

void ClientClass::removeRolesFromUser(
    sd::Server                  server,
    sd::Snowflake<sd::Server> serverID,
    sd::ServerMember            member,
    sd::Snowflake<sd::User>     userID
) {
    std::vector<sd::Snowflake<sd::Role>> memberRoleIDs = member.roles;

    for (auto roleID : memberRoleIDs) {
        auto roleItr = server.findRole(roleID);

        if (isHexCode(roleItr->name)) {
            removeRole(serverID, userID, roleID);
        }
    }
}

void ClientClass::deleteAllUnusedRoles(sd::Snowflake<sd::Server> serverID) {
    sd::ServerMembersRequest request;
    request.serverID = serverID;
    request.presence = true;
    request.query = "";
    request.limit = 0;

    requestServerMembers(request);

    // fake sync until request is responded
    memberChunkLoaded = false;
    while (!memberChunkLoaded);

    rolesInUse.clear();

    for (const auto& member : serverMembers) {
        for (const auto& roleID : member.roles) {
            rolesInUse.insert(roleID);
        }
    }

    std::vector<sd::Role> serverRoles = getRoles(serverID).vector();

    for (const auto& role : serverRoles) { 
        if (!isHexCode(role.name)) {
            continue;
        }

        bool roleNotInUse = rolesInUse.find(role.ID) == rolesInUse.end();

        if (roleNotInUse) {
            deleteRole(serverID, role.ID);
        }
    }
}

void ClientClass::assignNewRoleToUser(
    sd::Server                  server,
    sd::Snowflake<sd::Server> serverID,
    sd::Snowflake<sd::User>     userID,
    const std::string& color
) {
    auto roleItr = std::find_if(rolesInUse.begin(),rolesInUse.end(),
        [&](sd::Snowflake<sd::Role> roleID) {
            auto it = server.findRole(roleID);
            return it->name == color;
        }
    );

    // TODO: add role
    if (roleItr == rolesInUse.end()) {
        sd::Role newRole = createRole(
            serverID,
            color,
            sd::Permission::NONE,
            HexToDec(color)
        ).cast();

        addRole(serverID, userID, newRole.ID);
    } else {
        addRole(serverID, userID, *roleItr);
    }
}

void ClientClass::onMemberChunk(sd::ServerMembersChunk memberChunk) {
    serverMembers = std::move(memberChunk.members);
    memberChunkLoaded = true;
}

void ClientClass::onMessage(sd::Message message) {
    if (!message.startsWith("$#")) return;

    std::string color = message.content;
    if (!fixMessage(color)) return;

    sd::Snowflake<sd::Server> serverID = message.serverID;
    sd::Server server = getServer(serverID).cast();

    sd::Snowflake<sd::User> userID = message.author.ID;

    removeRolesFromUser(
        server,
        serverID,
        message.member,
        userID
    );

    deleteAllUnusedRoles(serverID);

    assignNewRoleToUser(
        server,
        serverID,
        userID,
        color
    );
}
