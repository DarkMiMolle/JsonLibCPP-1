#include "include/parse/JsnList.hpp"

using namespace std;

//template <typename T>
//JsnList<T>::JsnList(string& str) {
//  if constexpr (!is_same_v<Var, T> && !is_same_v<Val, T>) {
//    throw nu::JsonError("List can be only of Var (JsonObj) or Val (JsonArray).\n");
//  }
//  m_list.push_back(T(str));
//
//  int i = 0;
//  while (str.size()) {
//    if (str[i] != ' ' && str[i] != ',') {
//      str = str.substr(i);
//      break;
//    } else if (str[i] == ',') {
//      str = str.substr(i + 1);
//      m_list.push_back(T(str));
//      i = -1;
//    }
//    ++i;
//  }
//}
//
//template <typename T>
//const nu::Vector<T>& JsnList<T>::list() const {
//  return m_list;
//}
