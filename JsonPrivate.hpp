#pragma once

#include "include/NuVector.hpp"
#include "include/Json.hpp"

nu::Vector<std::string> cut_var(std::string str);

constexpr bool isVar(char c);

JsonTypes to_type(std::string str);

std::pair<std::string, JsonTypes> parse_var(std::string str);

