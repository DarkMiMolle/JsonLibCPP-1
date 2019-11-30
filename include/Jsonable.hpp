#pragma once

#include "JsonExeption.hpp"
#include <map>
#include <string>

namespace nu {

using string = std::string;

class MapJson {
private:
  std::map<string, void*> m_map;
public:
  template<typename T>
  T get(string key) {
    if constexpr ((std::is_class_v<T> || std::is_enum_v<T>) && !std::is_same_v<T, string>) {

    }
    return *((T*)m_map.at(key));
  }

  void set(string key, void* val);

  bool has(string key);

  void*& operator[](string key);

};

/*#define JsnVar(type, var) m_jsnObj[#var] = &var;\
val_to_string[#var] = [&](void) { return to_string<type>(var); }*/
#define JsnVar(type, var) _set_up_<type>(#type, #var, var);

class Jsonable {
private:
  friend class Json;
protected:
  nu::MapJson m_jsnObj;
  std::map<std::string, std::function<std::string(void)>> val_to_string;
  template <typename T>
  std::string to_string(T& val) {
    if constexpr (std::is_base_of_v<Jsonable, T>) {
      return val.stringify();
    }
    if constexpr (std::is_same_v<T, std::string>) {
      return val;
    }
    if constexpr (std::is_arithmetic_v<T>) {
      return std::to_string((float)val);
    }
    throw val;
  }

  template <typename T>
  void _set_up_(string type, string var_name, T& var) {
    if constexpr (std::is_pointer_v<T>) {
      throw TypeError("pointer");
    } else if constexpr (!(std::is_same_v<T, int>
                           || std::is_same_v<T, float>
                           || std::is_same_v<T, string>
                           || std::is_same_v<T, bool>
                           || std::is_base_of_v<Jsonable, T>)) {
      throw TypeError(type);
    }
    m_jsnObj[var_name] = &var;
    val_to_string[var_name] = [&](void) { return to_string<T>(var);};
  }
public:
  Jsonable() = default;

  std::string stringify() const;
};

}

/*

 */
