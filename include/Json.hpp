#pragma once

#include "Jsonable.hpp"
#include "JsonExeption.hpp"
#include <variant>

namespace nu {


#define JsonTypes std::variant<bool, float, int, std::string, nu::Json>
class Json {
  using string = std::string;
private:
  template <typename T>
  void set(void*& elem, void*& to) {
    *static_cast<T*>(to) = *static_cast<T*>(elem);
    // *((T*)to) = *((T*)elem);
  }
  template <typename T>
  bool assign_type(JsonTypes& elem, void*& to) {
    void* ptr = std::get_if<T>(&elem);
    if (ptr) set<T>(ptr, to);
    return ptr;
  }
  void assign(JsonTypes& elem, void*& to) {
    if (assign_type<bool>(elem, to)) return;
    if (assign_type<int>(elem, to)) return;
    if (assign_type<float>(elem, to)) return;
    if (assign_type<string>(elem, to)) return;
    if (assign_type<Json>(elem, to)) return;
    throw TypeError();
  }
  std::map<string, JsonTypes> m_map;
  string m_jsn;
public:
  Json() = default;
  Json(string str);

  Json& parse(string str);

  template <typename Jsnable>
  Jsonable& to(Jsnable& obj);

  string getString() const;
};



template <typename Jsnable>
Jsonable& Json::to(Jsnable& obj) {
  if constexpr (!std::is_base_of_v<Jsonable, Jsnable>) {
    throw JsonError("type destination is not Jsonable");
  }
  auto& jsnObj = dynamic_cast<Jsonable&>(obj);
  if (m_map.size() == 0) parse(m_jsn);
  for (auto& pair : m_map) {
    assign(pair.second, jsnObj.m_jsnObj[pair.first]);
  }
  return jsnObj;
}



}
