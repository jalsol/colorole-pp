#ifndef UTILS_H_
#define UTILS_H_

#include <string>
#include <chrono>
#include <random>

const std::string kHexCharacters = "0123456789abcdef";

extern std::mt19937 randomEngine;

bool isHexCode(const std::string &hexCode);
unsigned int HexToDec(const std::string &hexCode);

int random(int a, int b);
std::string getRandomColor();
std::string colorOfTheDay();
#endif // UTILS_H_
