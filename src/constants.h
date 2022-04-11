#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <string>
#include <cstdlib>

const std::string kBotToken = std::getenv(
#ifdef DEVELOPMENT
    "COLOROLE_TOKEN_DEVELOPMENT"
#else
    "COLOROLE_TOKEN"
#endif // DEVELOPMENT
);

#endif // CONSTANTS_H_
