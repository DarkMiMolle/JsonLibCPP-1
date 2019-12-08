#include "include/JsonExeption.hpp"
#include "include/parse/VarName.hpp"

#include <iostream>

using namespace std;

VarName::VarName(string& str) {
  for (int i = 0; i < str.size(); ++i) {
    if (str[i] == '"') {
      str = str.substr(i);
      break;
    }
    if (str[i] != ' ') {
      throw nu::JsonError(string() + "invalide character: " + str[i]);
    }
  }
  if (str.front() != '"') throw nu::JsonError(string() + "invalide character: " + str.front());
  str = str.substr(1);

  for (int i = 0; i < str.size(); ++i) {
    if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')) {
      m_name += str[i];
    } else if (m_name.size() >= 1 && ((str[i] >= '0' && str[i] <= '9') || str[i] == '-' || str[i] == '_')) {
      m_name += str[i];
    } else if (str[i] == '"') {
      str = str.substr(i + 1);
      break;
    } else { // char not allowed
      throw nu::JsonError(string() + "invalide character for VarName: " + str[i]);
    }
  }
}

const string VarName::name() const {
  return m_name;
}

bool VarName::operator==(const string str) const {
  return m_name == str;
}

void VarName::print() const {
  cout << '"' << m_name << '"';
}
