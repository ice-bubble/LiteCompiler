//
// Created by Ice-bubble on 24-4-21.
//

#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <string>

class FileHandler
{
public:
    static bool readFile(const std::string &filename, std::string &content, std::string &errorMessage);
};

#endif // FILE_HANDLER_H
