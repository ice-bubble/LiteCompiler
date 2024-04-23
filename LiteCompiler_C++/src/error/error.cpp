//
// Created by icelake on 24-4-23.
//

#include <iostream>
#include "error.h"

void error(size_t line, std::string message) {
    std::cerr << "[line: " << line << "] Error:" << message << std::endl;
}
