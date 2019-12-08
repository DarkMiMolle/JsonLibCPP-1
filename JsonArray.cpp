#include "include/parse/JsonArray.hpp"

#include <iostream>

using namespace std;

JsonArray::JsonArray(string& str) : is_null(false) {

  if (str.front() != '[') throw nu::JsonError("Error, missing '['.\n");
  str = str.substr(1);
  m_list = JsnList<Val>(str);
  if (str.front() != ']') throw nu::JsonError("Error, missing ']'.\n");
  str = str.substr(1);
}

JsonArray::JsonArray(void*) : is_null(true) {}

const Val& JsonArray::operator[](int i) const {
  return m_list.list()[i];
}

void JsonArray::print() const {
  if (is_null) {
    cout << "null";
    return;
  }
  cout << "[ ";
  m_list.print();
  cout << " ]";
}


JsonArray::TypeDest JsonArray::convert() const {
  TypeDest array;
  for (auto& val : m_list.list()) {
    array.list.push_back(val.convert());
  }
  return array;
}
