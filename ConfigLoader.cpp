#include "ConfigLoader.h"
#include <fstream>
#include <iostream>
#include <format>
#include <string>
#include <print>
#include <any>

std::unordered_map<std::string, std::any> ConfigLoader::load(const std::string& filePath)
{
    std::ifstream file(filePath);

    try
    {
        checkFile(file, filePath);
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return {};
    }

    // Config to return
    std::unordered_map<std::string, std::any> config;

    std::string line;
    while (std::getline(file, line))
    {
        // Check if line is comment, if is then skip
        // # comment
        if (!line.empty() && line.at(0) == '#')
            continue;

        // Delete test after '#'
        // value = key # comment
        size_t commentPos = line.find('#');
        if (commentPos != std::string::npos)
            line.erase(commentPos, line.length());

        size_t pos = line.find('=');
        if (pos == std::string::npos)
            continue;

        std::string key  = line.substr(0, pos);
        std::string value = line.substr(pos + 1);

        deleteSpaces(value);
        deleteSpaces(key);


        config[key] = parseValue(value);
    }

    // For now
    return config;
};

void ConfigLoader::checkFile(const std::ifstream& file, const std::string& filePath)
{
    if (!file.is_open())
    {
        throw std::runtime_error(std::format("ConfigLoader: '{}' Not found", filePath));
    }
}

void ConfigLoader::deleteSpaces(std::string &line)
{
    if (line.empty())
        return;

    const size_t start = line.find_first_not_of(' ');

    if (start == std::string::npos)
    {
        line.clear();
        return;
    }

    // Delete from left site
    line.erase(0,start);

    const size_t end = line.find_last_not_of(' ');

    // Delete from right site
    line.erase(end + 1);
}

std::any ConfigLoader::parseValue(const std::string &value)
{
    // Try int
    try { return std::stoi(value); } catch (...) {}

    // Try double
    try { return std::stod(value); } catch (...) {}

    // Try bool
    if (value == "true") return true;
    if (value == "false") return false;

    return value;

}

std::any ConfigLoader::getValue(const std::string &key)
{
    if (key.empty())
    {
        std::println("ConfigLoader: Key cannot be empty");
        return {};
    }

    try
    {
        return config.at(key);
    }
    catch (std::out_of_range& e)
    {
        std::println("ConfigLoader: Not Found");
        return {};
    }
}