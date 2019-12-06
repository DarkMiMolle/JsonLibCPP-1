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


using JsonNull = void*;
using JsonObj = Json;
template <typename T>
using JArray = nu::Vector<T>;
//using JsonArray = std::variant<JArray<int>, JArray<string>, JArray<float>, JArray<bool>, JArray<JsonObj>, JArray<JsonNull>>;
#define JsonBasicTypes bool, float, int, std::string, char, JsonNull
struct JsonArray {
  nu::Vector<std::variant<JsonBasicTypes, Json, JsonArray>> list;
};

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
  Json(char* str);

  Json& parse(string str);


  string getString() const;

  void print_map() const;
};


inline bool is_JsonNull(JsonTypes& j) {
  return std::get_if<JsonNull>(&j) != nullptr;
}

template <typename T>
inline bool assign_if_JsonNull(T* val, JsonTypes& j) {
  if (is_JsonNull(j)) {
    *val = T();
    return true;
  }
  return false;
}

}
