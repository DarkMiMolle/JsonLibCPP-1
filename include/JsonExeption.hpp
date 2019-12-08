#pragma once

#include <exception>
#include <string>

namespace nu {


class JsonError : public std::exception {
private:
  std::string msg;
public:
  JsonError(std::string msg);
  JsonError(const char* msg);
  virtual const char* what() const noexcept override;
};

class TypeError : public JsonError {
public:
  TypeError();
  TypeError(std::string type);
};

class ParseError : public JsonError {
private:
  std::string msg;
public:
  ParseError(char near);
};

}

