#include "include/Jsonable.hpp"

namespace nu {

void MapJson::set(string key, void* val) {
  m_map[key] = val;
}

bool MapJson::has(string key) {
  return m_map.count(key);
}

void*& MapJson::operator[](string key) {
  if (!m_map.count(key)) {
    m_map[key] = nullptr;
  }
  return m_map.at(key);
}

}

/*
 std::string Jsonable::stringify() const {
 std::string jsn = "{\n";
 for (auto& elem : val_to_string) {
 jsn += elem.first + ",\n";
 jsn += elem.second() + ",\n";
 }
 jsn = jsn.substr(0, jsn.size() - 3) + "\n}";
 return jsn;
 }
 */
