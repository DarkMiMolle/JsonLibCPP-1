#include "include/Json.hpp"
#include "include/NuVector.hpp"

#include "JsonPrivate.hpp"

using namespace std;

namespace nu {

nu::Json::Json(string str) : m_jsn(str) {}

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
