#pragma once

#include "JsonExeption.hpp"
#include "NuVector.hpp"

#include <variant>
#include <map>
#include <string>
#include <variant>

namespace nu {

using string = std::string;

class Json;

#define JsonBasicTypes bool, float, int, std::string, char
using JsonObj = Json;
using JsonArray = std::variant<nu::Vector<int>, nu::Vector<std::string>, nu::Vector<float>, nu::Vector<bool>, nu::Vector<JsonObj>>;
using JsonTypes = std::variant<JsonBasicTypes, JsonObj, JsonArray>;
#undef JsonBasicTypes

class Json {
  friend class Jsonable;
private:
  std::map<string, JsonTypes> m_map;
  string m_jsn;
public:
  Json() = default;
  Json(string str);

  Json& parse(string str);


  string getString() const;

  void print_map() const;
};



}
