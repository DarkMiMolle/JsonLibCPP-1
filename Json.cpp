#include "include/json_files/Json.hpp"
#include "include/NuVector.hpp"

#include "include/JsonExeption.hpp"

#include <iostream>

using namespace std;

/*--------------- PRIVATE FUNC ------------------*/


nu::Vector<string> cut_var(string str) {
  nu::Vector<string> array;
  array.push_back("");
  auto isObj = str.front() == '{';
  if (isObj && str.back() != '}') throw nu::ParseError(str.back());

  if (isObj) str = str.substr(1, str.size() - 1);
  else {
    array.back() = str;
    return array;
  }
  auto open = 0;
  auto close = false;
  auto obj = 0;
  for (auto& c : str) {
    if (c == '{') ++obj;
    if (c == '}') --obj;
    if (obj > 0) {
      array.back() += c;
      continue;
    }
    if (c == '"' && open % 2 == 0 && open) --open;
    else if (c == '"') ++open; // open = 0 || 1
    if (c == ',' && open == 2) {
      close = true;
      open = 0;
    } else if (open) {
      array.back() += c;
    }
    if (close) {
      // std::cout << "cut_var: " << array.back() << '\n';
      array.push_back(string());
      close = false;
    }
  }
  array.back() = array.back().substr(0, array.back().size() - 1);
  return array;
}

constexpr bool isVar(char c) {
  return c == '"' || (c > '0' && c <= '9') || c == '{'; // || c == '["
}

nu::JsonTypes to_type(string str) {
  // std::cout << "to_type: " << str << '\n';
  if (str.front() == '"' && str.back() == '"') {
    auto val = str.substr(1, str.size() - 2);
    if (val.size() == 1) {
      return val[0];
    }
    return val;
  } else if (str.front() > '0' && str.back() <= '9') {
    if (str.find('.') != string::npos) {
      return std::stof(str);
    }
    return std::stoi(str);
  } else if (str == "true" || str == "false") {
    return str == "true";
  } else if (str.front() == '{' && str.back() == '}') {
    return nu::Json().parse(str);
  }
  throw "invalid value, type error";
}

std::pair<string, nu::JsonTypes> parse_var(string str) {
  str = str.substr(1);
  string varName = "";
  size_t i = 0;
  for (; str[i] != '"'; ++i) varName += str[i];
  for (; str[i] != ':' && str[i]; ++i);
  for (; !isVar(str[i]) && str[i]; ++i);
  return std::pair(varName, to_type(str.substr(i)));
}

/*-----------------------------------------------*/

namespace nu {

Json::Json(string str) : m_jsn(str) {}

Json& Json::parse(string str) {
  auto var_line = cut_var(str);
  var_line.map([&](string& elem) {
    auto e = parse_var(elem);
    m_map.insert(e);
  });
  return *this;
}

string Json::getString() const {
  return m_jsn;
}


}
