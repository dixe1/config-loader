#pragma once
#include <string>
#include <unordered_map>
#include <any>

class ConfigLoader
{
public:
    static std::unordered_map<std::string, std::any>
    load(const std::string& filePath);

    std::any getValue(const std::string& key);

    ConfigLoader(const std::string& filePath)
    {
        config = load(filePath);
    }

private:
    std::unordered_map<std::string, std::any> config;

    static void checkFile(const std::ifstream& file, const std::string& filePath);
    static void deleteSpaces(std::string& line);
    static std::any parseValue(const std::string& value);
};