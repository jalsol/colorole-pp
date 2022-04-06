#ifndef UTILS_H_
#define UTILS_H_

#include <string>

#include <dpp/dpp.h>

bool IsHexCode(const std::string& hex_code);

void ClearPreviousRoles(dpp::cluster& cluster,
                        const dpp::guild_member& member);

bool UpdateRole(dpp::cluster& cluster,
                const dpp::guild_member& member,
                const std::string& hex_code);

void UpdateChosenRole(const dpp::interaction_create_t& event);
void UpdateRandomRole(const dpp::interaction_create_t& event);

#endif // UTILS_H_