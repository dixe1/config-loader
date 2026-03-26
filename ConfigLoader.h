#pragma once
#include <string>
#include <unordered_map>
#include <array>
#include <any>

class ConfigLoader
{
public:
    static std::unordered_map<std::string, std::any>
    load(const std::string& filePath);

    ConfigLoader(const std::string& filePath)
    {
        config = load(filePath);
    }

    std::any getValue(const std::string& key);

    template<typename T>
    T get(const std::string &key)
    {
        std::any value = getValue(key);
        return std::any_cast<T>(value);
    }

private:
    std::unordered_map<std::string, std::any> config;   // Main config variable

    static void checkFile(const std::ifstream& file, const std::string& filePath);
    static void deleteSpaces(std::string& line);
    static std::any parseValue(const std::string& value);
};