#include <regex>

#include "utils.h"

std::mt19937 randomEngine(
    std::chrono::high_resolution_clock::now().time_since_epoch().count());

bool isHexCode(const std::string& hexCode) {
    return std::regex_match(hexCode, std::regex("^[0-9a-f]{6}$"));
}

unsigned int HexToDec(const std::string& hexCode) {
    unsigned int value;
    std::stringstream stream;

    stream << std::hex << hexCode;
    stream >> value;

    return value;
}

int random(int a, int b) {
    return std::uniform_int_distribution<int>(a, b)(randomEngine);
}

std::string getRandomColor() {
    std::string value(6, '\0');

    for (int i = 0; i < 6; ++i) {
        value[i] = kHexCharacters[random(0, kHexCharacters.size() - 1)];
    }

    return value;
}

bool fixMessage(std::string& color) {
    color.erase(0, 2);
    bool isRandom = (color == "random");

    std::transform(
        color.begin(), color.end(), color.begin(),
        [](char c) { return std::tolower(c); }
    );

    if (!isHexCode(color) && !isRandom) {
        return false;
    }

    if (isRandom) {
        color = getRandomColor();
    }

    return true;
}
