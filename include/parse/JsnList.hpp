#pragma once

#include "Var.hpp"
#include "../NuVector.hpp"

#include <iostream>

namespace jsn_parse {


template <typename T>
class JsnList {
  using string = std::string;
public:
  JsnList() = default;
  JsnList(string& str);

  const nu::Vector<T>& list() const;
  void print() const;
private:
  nu::Vector<T> m_list;
};

#include "JsnList.hxx"

}
