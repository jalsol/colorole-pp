#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <cstdlib>
#include <string>

#include <dpp/dpp.h>

const std::string    kBotToken = std::getenv("COLOROLE_TOKEN");
const dpp::snowflake kGuildId  = std::atoll(std::getenv("GUILD_ID"));

#endif // CONSTANTS_H_