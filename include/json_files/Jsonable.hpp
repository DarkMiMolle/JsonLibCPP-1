#pragma once

#include "JsonExeption.hpp"
#include "Json.hpp"
#include <map>
#include <string>

#include <iostream>

namespace nu {

using string = std::string;


#define JsnVar(type, var) set[#var] = assign_gen<type>(&var);\
val_to_string[#var] = [&](void) { return to_string<type>(var); }


template <typename T>
constexpr bool is_JsonArray = std::is_base_of_v<std::vector<int>, T>
|| std::is_base_of_v<std::vector<float>, T> ||  std::is_base_of_v<std::vector<string>, T>
|| std::is_base_of_v<std::vector<char>, T> || std::is_base_of_v<std::vector<bool>, T>
|| std::is_base_of_v<std::vector<void*>, T>;

template <typename T>
constexpr bool is_JsonTypes = std::is_same_v<int, T>
|| std::is_same_v<float, T> || std::is_same_v<char, T>
|| std::is_same_v<string, T> || std::is_same_v<bool, T>;


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
      return string() + "\"" + val + "\"";
    }
    if constexpr (std::is_arithmetic_v<T>) {
      return std::to_string(val);
    }
    if constexpr (is_JsonArray<T>) {
      string str = "[";
      for (auto& e : val) {
        str += " " + to_string(e) + ",";
      }
      str.back() = ' ';
      str += "]";
      return str;
    }
    throw val;
  }

  template <typename U, typename T>
  bool assign_if(T* val, JsonTypes& e) {
    if constexpr (std::is_base_of_v<std::vector<U>, T>) {
      val->push_back(std::get<U>(e));
      return true;
    }
    return false;
  }

  template <typename T>
  std::function<void(JsonTypes)> assign_gen(T* val) {
    if constexpr (std::is_base_of_v<Jsonable, T>) { // val is an Object.
      return [=](JsonTypes elem) {
        if (assign_if_JsonNull(val, elem)) {
          return;
        }

        try {
          val->load(std::get<Json>(elem));
        } catch (std::exception& e) {
          std::cout << e.what() << "\n\n";
        }
      };
    }
    if constexpr (is_JsonArray<T>) {
      return [=](JsonTypes elem) {
        auto array = std::get<JsonArray>(elem);

        std::cout << "gen_assign/JsonArray: " << array.list.size() << '\n';

        for (auto& e : array.list) {
          if (assign_if<int>(val, e)) return;
          if (assign_if<float>(val, e)) return;
          if (assign_if<char>(val, e)) return;
          if (assign_if<string>(val, e)) return;
          if (assign_if<bool>(val, e)) return;
          void* ptr = std::get_if<Json>(&e);
          if (ptr) {
            std::cout << "figure it out\n";
          }
          ptr = std::get_if<JsonArray>(&e);
          if (ptr) {
            std::cout << "figure it out\n";
          }
        }
      };
    }
    if constexpr(std::is_same_v<T, char>) {
      return [=](JsonTypes elem) {
        if (assign_if_JsonNull(val, elem)) {
          return;
        }

        *val = std::get<char>(elem);
      };
    }
    if constexpr (is_JsonTypes<T>) {
      return [=](JsonTypes elem) {
        if (assign_if_JsonNull(val, elem)) {
          return;
        }
        
        try {
          *val = std::get<T>(elem);
        } catch (std::exception& e) {
          std::cout << std::boolalpha << std::is_base_of_v<Jsonable, T> << '\n' <<
          e.what() << '\n';
        }
      };
    }
    return [](JsonTypes elem) {
      throw "error";
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
