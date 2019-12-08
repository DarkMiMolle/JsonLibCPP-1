#include "include/parse/JsonObj.hpp"

#include <iostream>

using namespace std;


JsonObj::JsonObj(string& str) : is_null(false) {
  if (str.front() != '{') throw nu::JsonError("Error, missing '{'.\n");
  str = str.substr(1);
  m_list = JsnList<Var>(str);
  if (str.front() != '}') throw nu::JsonError("Error, missing '}'.\n");
  str = str.substr(1);
}

JsonObj::JsonObj(void* null) : is_null(true) {}

const JsnList<Var>& JsonObj::attributs() const {
  return m_list;
}

const Val JsonObj::operator[](string name) const {
  for (auto& var : m_list.list()) {
    if (var.var_name() == name) {
      return var.val();
    }
  }
  throw nu::JsonError("no such " + name + "in this Json.\n");
}


void JsonObj::print() const {
  if (is_null) {
    cout << "null";
    return;
  }
  cout << "{";
  m_list.print();
  cout << "}";
}

nu::Json JsonObj::convert() const {
  return nu::Json();
}
