#pragma once

#include <string>

namespace jsn_parse {

class VarName {
  using string = std::string;
public:
  VarName() = delete;
  VarName(string& str);

  bool operator==(const string str) const;

  const string name() const;
  void print() const;
private:
  string m_name;
};



}
