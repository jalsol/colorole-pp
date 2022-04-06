#include <cassert>
#include <string>
#include <regex>

#include <dpp/dpp.h>
#include <dpp/fmt/format.h>

#include "constants.h"
#include "utils.h"

bool IsHexCode(const std::string& hex_code) {
    return std::regex_match(hex_code, std::regex("^[0-9A-F]{6}$"));
}

void ClearPreviousRoles(dpp::cluster& cluster,
                        const dpp::guild_member& member)
{
    for (const auto& role_id : member.roles) {
        dpp::role* role_ptr = dpp::find_role(role_id);
        assert(role_ptr != nullptr);

        if (!IsHexCode(role_ptr->name)) {
            continue;
        }

        cluster.guild_member_delete_role(
            kGuildId,
            member.user_id,
            role_id
        );

        if (role_ptr->get_members().size() == 0) {
            cluster.role_delete(kGuildId, role_id);
        }
    }
}

bool UpdateRole(dpp::cluster& cluster,
                const dpp::guild_member& member,
                const std::string& hex_code)
{
    if (!IsHexCode(hex_code)) return false;

    ClearPreviousRoles(cluster, member);

    // TODO: implement this

    return true;
}

void UpdateChosenRole(const dpp::interaction_create_t& event) {
    // TODO: implement this

    event.reply("update!");
}

void UpdateRandomRole(const dpp::interaction_create_t& event) {
    // TODO: implement this

    event.reply("random!");
}