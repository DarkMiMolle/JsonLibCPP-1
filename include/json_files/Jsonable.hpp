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

#define ListJsnVar void JsonInit()


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
  string to_string(T& val);

  template <typename U, typename T>
  bool assign_if(T* val, JsonTypes& e);

  template <typename T>
  std::function<void(JsonTypes)> assign_gen(T* val);

public:
  Jsonable() = default;

  string stringify() const;

  void load(Json j);

};

#include "Jsonable.hxx"

}

/*

 */
