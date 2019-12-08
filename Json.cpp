#include "include/json_files/Json.hpp"
#include "include/NuVector.hpp"

#include "include/JsonExeption.hpp"
#include "include/parse/JsonObj.hpp"

#include <iostream>

using namespace std;

namespace nu {

Json::Json(string str) : Json(JsonObj(str).convert()) {
  m_jsn = str;
}

Json::Json(char* str) : Json(string(str)) {}

Json& Json::parse(string str) {
  *this = JsonObj(str).convert();
  return *this;
}

string Json::getString() const {
  return m_jsn;
}

/*template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

void Json::print_map() const {
  for (auto& pair : m_map) {
    cout << pair.first << " : ";
    visit(overloaded{
      [](auto arg) { cout << arg; },
      [](Json arg) { arg.print_map(); },
      [](JsonArray arg) { cout << "array of " << arg.list.size() << " elements\n"; }
    }, pair.second);
    cout << '\n';
  }
}*/

}
