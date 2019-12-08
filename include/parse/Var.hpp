#pragma once

#include <memory>
#include "VarName.hpp"
#include "Val.hpp"

namespace jsn_parse {


class Var {
  using string = std::string;
public:
  Var();
  Var(string& str);

  const VarName var_name() const;
  const Val val() const;
  void print() const;
private:
  std::unique_ptr<VarName> m_var_name;
  std::unique_ptr<Val> m_val;
  const bool m_valide;
};



}
