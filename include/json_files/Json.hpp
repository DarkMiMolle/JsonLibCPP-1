#pragma once

#include "JsonExeption.hpp"
#include "NuVector.hpp"

#include <variant>
#include <map>
#include <string>
#include <variant>

namespace jsn_parse {
  class JsonObj;
}

namespace nu {

using string = std::string;

class Json;


using JsonNull = void*;
template <typename T>
using JArray = nu::Vector<T>;

#define JsonBasicTypes bool, float, int, std::string, char, JsonNull
struct JsonArray {
  nu::Vector<std::variant<JsonBasicTypes, Json, nu::JsonArray>> list;
};

using JsonTypes = std::variant<JsonBasicTypes, Json, JsonArray>;
#undef JsonBasicTypes

class Json {
  friend class Jsonable;
  friend class jsn_parse::JsonObj;
private:
  std::map<string, JsonTypes> m_map;
  string m_jsn;
public:
  Json() = default;
  Json(string str);
  Json(char* str);

  Json& parse(string str);


  string getString() const;

  //void print_map() const;
};

}
