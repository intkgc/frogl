//
// Created by kirbo on 12.03.2022.
//

#include <string>
#include <regex>
#include <iostream>

#include "compiler.h"

using namespace std;

static const std::regex spaces_r(R"(\s+)");
static const std::regex function_r(R"([a-zA-Z_0-9]*\([a-zA-Z_0-9,]*\)=[a-zA-Z_0-9\*\-\+/]*)");
static const std::regex var_r(R"([a-zA-Z_0-9]*=[a-zA-Z_0-9\*\-\+/]*)");

bool froglm::compiler::is_function(std::string str) {
    return std::regex_match(without_spaces(str).data(), function_r);
}

bool froglm::compiler::is_variable(std::string str) {
    return std::regex_match(without_spaces(str).data(), var_r);
}

std::string froglm::compiler::without_spaces(std::string str) {
    return regex_replace(str, spaces_r, "");
}
