//
// Created by icelake on 24-4-23.
//

#include "error.h"

void error(size_t line, const std::string& message) {
    std::cerr << "[line: " << line << "] Error:" << message << std::endl;
}