#include "../include/json_files/Jsonable.hpp"

namespace nu {

std::string Jsonable::stringify() const {
  std::string jsn = "{\n";
  for (auto& elem : val_to_string) {
    jsn += "\"" + elem.first + "\": ";
    jsn += elem.second() + ",\n";
  }
  jsn = jsn.substr(0, jsn.size() - 2) + "\n}";
  return jsn;
}

void Jsonable::load(Json j) {
  if (j.m_map.size() == 0) j.parse(j.m_jsn);
  for (auto& pair : j.m_map) {
    set[pair.first](pair.second);
  }
}

}

/*

 */
