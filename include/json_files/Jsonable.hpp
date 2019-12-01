#pragma once

#include "JsonExeption.hpp"
#include "Json.hpp"
#include <map>
#include <string>

namespace nu {

using string = std::string;


#define JsnVar(type, var) set[#var] = assign_gen<type>(&var);\
val_to_string[#var] = [&](void) { return to_string<type>(var); }

class Jsonable {
protected:
  std::map<string, std::function<void(JsonTypes)>> set;
  std::map<string, std::function<string(void)>> val_to_string;
  template <typename T>
  string to_string(T& val) {
    if constexpr (std::is_base_of_v<Jsonable, T>) {
      return val.stringify();
    }
    if constexpr (std::is_same_v<T, std::string>) {
      return "\"" + val + "\"";
    }
    if constexpr (std::is_same_v<T, char>) {
      return string(1, val);
    }
    if constexpr (std::is_arithmetic_v<T>) {
      return std::to_string((float)val);
    }
    throw val;
  }

  template <typename T>
  std::function<void(JsonTypes)> assign_gen(T* val) {
    if constexpr (std::is_base_of_v<Jsonable, T>) { // val is an Object.
      return [=](JsonTypes elem) {
        val->load(std::get<Json>(elem));
      };
    }
    if constexpr (std::is_array_v<T>) {
      // FIXME
    }
    if constexpr(std::is_same_v<T, char>) {
      return [=](JsonTypes elem) {
        *val = std::get<char>(elem);
      };
    }
    return [=](JsonTypes elem) {
      *val = std::get<T>(elem);
    };
  }

public:
  Jsonable() = default;

  string stringify() const;

  void load(Json j);

};


}

/*

 */
