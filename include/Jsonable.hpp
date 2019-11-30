#pragma once

#include <map>
#include <string>

namespace nu {

class MapJson {
  using string = std::string;
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

#define JsnVar(var) m_jsnObj[#var] = &var

class Jsonable {
private:
  friend class Json;
protected:
  MapJson m_jsnObj;
public:
  Jsonable() = default;

};

}

/*
 #define JsnVar(type, var) m_jsnObj[#var] = &var;\
 val_to_string[#var] = [&](void) { return to_string<type>(var); }

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
 public:
 Jsonable() = default;

 std::string stringify() const;
 };
 */
