#pragma once

#include "Var.hpp"
#include "../NuVector.hpp"

#include <iostream>

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

template <typename T>
JsnList<T>::JsnList(string& str) {
  if constexpr (!std::is_same_v<Var, T> && !std::is_same_v<Val, T>) {
    throw nu::JsonError("List can be only of Var (JsonObj) or Val (JsonArray).\n");
  }
  m_list.push_back(T(str));

  int i = 0;
  while (str.size()) {
    if (str[i] != ' ' && str[i] != ',') {
      str = str.substr(i);
      break;
    } else if (str[i] == ',') {
      str = str.substr(i + 1);
      m_list.push_back(T(str));
      i = -1;
    }
    ++i;
  }
}

template <typename T>
const nu::Vector<T>& JsnList<T>::list() const {
  return m_list;
}

template <typename T>
void JsnList<T>::print() const {
  for (int i = 0; i < m_list.size(); ++i) {
    m_list[i].print();
    if (i != m_list.size() - 1) std::cout << ", ";
  }
}
