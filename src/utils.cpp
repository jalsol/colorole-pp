#include <regex>

#include "utils.h"

std::mt19937 randomEngine(
    std::chrono::high_resolution_clock::now().time_since_epoch().count());

bool isHexCode(const std::string &hexCode)
{
    return std::regex_match(hexCode, std::regex("^[0-9a-f]{6}$"));
}

unsigned int HexToDec(const std::string &hexCode)
{
    unsigned int value;
    std::stringstream stream;

    stream << std::hex << hexCode;
    stream >> value;

    return value;
}

int random(int a, int b)
{
    return std::uniform_int_distribution<int>(a, b)(randomEngine);
}

std::string getRandomColor()
{
    std::string value(6, '\0');

    for (int i = 0; i < 6; ++i)
    {
        value[i] = kHexCharacters[random(0, kHexCharacters.size() - 1)];
    }

    return value;
}

std::string colorOfTheDay()
{
    time_t t = time(NULL);
    tm *lt = localtime(&t);
    int seed = lt->tm_mday + lt->tm_mon + 1 + lt->tm_year + 1900;
    std::mt19937 mt(seed);
    long long int dailyRand = mt();
    if (dailyRand > 4294967295)
        return "ffffff";

    std::string value(6, '\0');

    for (int i = 0; i < 6; i++)
    {
        value[i] = kHexCharacters[dailyRand % 16];
        dailyRand /= 16;
    }

    return value;
}
