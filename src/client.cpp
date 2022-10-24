#include "client.h"

void ClientClass::removeRolesFromUser(
    sd::Server server,
    sd::Snowflake<sd::User> userID
) {
    const auto& userRoleIDs = getMember(server.ID, userID).cast().roles;
    
    for (auto roleID : userRoleIDs) {
        auto roleItr = server.findRole(roleID);

        if (isHexCode(roleItr->name)) {
            removeRole(server.ID, userID, roleID);
        }
    }
}

void ClientClass::getCurrentServerRoles(sd::Snowflake<sd::Server> serverID) {
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
}

void ClientClass::deleteUnusedServerRoles(sd::Snowflake<sd::Server> serverID) {
    const auto& serverRoles = getRoles(serverID).vector();

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

void ClientClass::addRoleToUser(
    sd::Server server,
    sd::Snowflake<sd::User> userID,
    const std::string& color
) {
    auto roleItr = std::find_if(rolesInUse.begin(),rolesInUse.end(),
        [&](sd::Snowflake<sd::Role> roleID) {
            auto it = server.findRole(roleID);
            return it->name == color;
        }
    );

    if (roleItr == rolesInUse.end()) {
        sd::Role newRole = createRole(
            server.ID,
            color,
            sd::Permission::NONE,
            HexToDec(color)
        ).cast();

        addRole(server.ID, userID, newRole.ID);
    } else {
        addRole(server.ID, userID, *roleItr);
    }
}

void ClientClass::assignSpecificRoleToUser(
    sd::Server server,
    sd::Snowflake<sd::User> userID,
    const std::string& color
) {
    removeRolesFromUser(server, userID);

    getCurrentServerRoles(server.ID);

    deleteUnusedServerRoles(server.ID);

    addRoleToUser(server, userID, color);
}

std::string ClientClass::getRoleOfUser(
    sd::Server server,
    sd::Snowflake<sd::User> userID
) {
    const auto& userRoleIDs = getMember(server.ID, userID).cast().roles;

    auto roleItr = std::find_if(userRoleIDs.begin(), userRoleIDs.end(),
        [&](sd::Snowflake<sd::Role> roleID) {
            auto it = server.findRole(roleID);
            return isHexCode(it->name);
        }
    );


    if (roleItr == userRoleIDs.end()) {
        return "";
    }

    return server.findRole(*roleItr)->name;
}

void ClientClass::onMemberChunk(sd::ServerMembersChunk memberChunk) {
    serverMembers = std::move(memberChunk.members);
    memberChunkLoaded = true;
}

void ClientClass::onMessage(sd::Message message) {
    if (!message.startsWith("$#")) return;

    std::string command = message.content;
    command.erase(0, 2);
    std::transform(
        command.begin(), command.end(), command.begin(),
        [](char c) { return std::tolower(c); }
    );

    // store to save API call
    sd::Server server = getServer(message.serverID).cast();

    if (command.substr(0, 4) == "copy") {
        if (message.mentions.empty()) {
            sendMessage(message.channelID, "Mention a user to copy their role.");
            return;
        }

        command = getRoleOfUser(
            server,
            message.mentions.front().ID
        );

        if (command == "") {
            return;
        }
    }

    if (command == "random") {
        command = getRandomColor();
    }

    if (command == "daily") {
        command = colorOfTheDay();
    }

    if (!isHexCode(command)) {
        sendMessage(message.channelID, "Not a valid command.");
        return;
    }

    assignSpecificRoleToUser(
        server,
        message.author.ID,
        command
    );

    sendMessage(
        message.channelID,
        "<@" + message.author.ID + "> → **#" + command + "**"
    );
}