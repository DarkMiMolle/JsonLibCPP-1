#include "../include/parse/Var.hpp"

#include <iostream>

using namespace std;

namespace jsn_parse {

Var::Var() : m_valide(false) {}

Var::Var(string& str) : m_valide(true) {
  m_var_name = unique_ptr<VarName>(new VarName(str));
  for (int i = 0; i < str.size(); ++i) {
    if (str[i] != ' ' && str[i] != ':') throw nu::JsonError("Missing ':' between VarName and Val.\n");
    else if (str[i] == ':') {
      str = str.substr(i + 1);
      m_val = unique_ptr<Val>(new Val(str));
      break;
    }
  }
}

const VarName Var::var_name() const {
  if (!m_valide) throw nu::JsonError("Error parsing");
  return *m_var_name;
}

const Val Var::val() const {
  if (!m_valide) throw nu::JsonError("Error parsing");
  return *m_val;
}

void Var::print() const{
  m_var_name->print();
  cout << ": ";
  m_val->print();
}

}
