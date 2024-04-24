//
// Created by Ice-bubble on 24-4-21.
//
#include "FileHandler.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

bool FileHandler::readFile(const std::string &filename, std::string &content, std::string &errorMessage)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        errorMessage = "Failed to open file: " + filename;
        return false;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    content = buffer.str();
    return true;
}

bool FileHandler::writeFile(const std::string &filename, const std::string &content, std::string &errorMessage)
{
    std::ofstream file(filename);
    if (!file.is_open())
    {
        errorMessage = "Failed to open file for writing: " + filename;
        return false;
    }

    file << content;
    file.close();

    if (file.fail())
    {
        errorMessage = "Error occurred while writing to file: " + filename;
        return false;
    }

    return true;
}
