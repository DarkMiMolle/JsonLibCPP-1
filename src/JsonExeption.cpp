#include "JsonExeption.hpp"

#define ITLC \x1b[3m
#define NRM \x1b[0m

using namespace std;

namespace nu {

JsonError::JsonError(std::string msg): msg(msg) {}
const char* JsonError::what() const noexcept {
  return msg.c_str();
}

JsonError::JsonError(const char* msg) : msg(msg) {}


TypeError::TypeError(): JsonError("unknown type.\n") {}
TypeError::TypeError(string type): JsonError("invalide type: ITLC" + type + "NRM for a Json.\n") {}

ParseError::ParseError(char near): JsonError("parse error near: `ITLC" + string(0, near) + "NRM`.\n") {}

}

#undef ITLC
#undef NRM
