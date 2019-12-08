#include "include/parse/Val.hpp"
#include "include/parse/JsonObj.hpp"
#include "include/parse/JsonArray.hpp"
#include "include/JsonExeption.hpp"
#include <map>

#include <iostream>

using namespace std;


static const map<string, char> SpeTransform = {
  {"\\n", '\n'},
  {"\\\"", '"'}
};

void Val::build_string(string &str) {
  std::string val;
  for (int i = 1; i < str.size(); ++i) {
    if (str[i] == '\\' && i + 1 < str.size()) {
      auto escaped = str.substr(i, i + 1);
      try {
        val += SpeTransform.at(escaped);
        ++i;
      } catch (std::exception& e) {
        throw nu::JsonError(string() + "invalid escap char: \'" + escaped + "'.\n");
      }
    } else if (str[i] == '"') {
      str = str.substr(i + 1);
      if (val.size() == 1) {
        m_val = val.front();
      } else {
        m_val = val;
      }
      return;
    } else {
      val += str[i];
    }
  }
  throw nu::JsonError(string() + "unterminated string value.\n");
}

void Val::build_number(string &str) {
  string val;
  bool comma = false;
  for (int i = 0; i < str.size(); ++i) {
    if ((str[i] >= '0' && str[i] <= '9') || str[i] == '.') {
      if (str[i] == '.' && comma) throw nu::JsonError("invalid number.\n");
      else if (str[i] == '.') comma = true;
      val += str[i];
    } else {
      str = str.substr(i);
      if (comma) {
        m_val = stof(val);
      } else {
        m_val = stoi(val);
      }
      return;
    }
  }
}

void Val::build_obj(string &str) {
  m_val = Ref<JsonObj>(new JsonObj(str));
}

void Val::build_array(string &str) {
  m_val = Ref<JsonArray>(new JsonArray(str));
}

Val::Val(string& str) {
  for (int i = 0; i < str.size(); ++i) {
    if (str[i] != ' ') {
      str = str.substr(i);
      break;
    }
  }

  if (str.front() == '"') { // string
    build_string(str);
  } else if (str.front() >= '0' && str.front() <= '9') { // number
    build_number(str);
  } else if (str.front() == '{') { // JsonObj
    build_obj(str);
  } else if (str.front() == '[') { // JsonArray
    build_array(str);
  } else {
    if (str.substr(0, 5) == "false") {
      m_val = false;
      str = str.substr(5);
    } else if (str.substr(0, 4) == "true") {
      str = str.substr(4);
      m_val = true;
    } else if (str.substr(0, 4) == "null") {
      m_val = (void*)nullptr;
      str = str.substr(4);
    }
  }
}

template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

void Val::print() const {
  std::visit(overloaded {
    [](auto arg) { std::cout << arg; },
    [](string arg) { std::cout << '"' << arg << '"'; },
    [](Ref<JsonObj> arg) { arg.get().print(); },
    [](Ref<JsonArray> arg) { arg.get().print(); },
    [](void* arg) { std::cout << "null"; }
  }, m_val);
}

nu::JsonTypes Val::convert() const {
  return nullptr;
}
