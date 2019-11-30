#pragma once

#include <vector>
#include <functional>

#define then

namespace nu {

template <typename T>
class Vector : public std::vector<T> {
public:
  void map(std::function<void(T&)> f);

  Vector<T> filter(std::function<bool(T&)> selector) const;
  Vector<T> filter_ref(std::function<bool(T&)> selector);

  Vector<T>& operator+ (Vector<T>& concat);
  Vector<T>& operator+ (std::vector<T>& concat);
};

template <typename T>
void Vector<T>::map(std::function<void(T&)> f) {
  for(auto& elem : *this) {
    f(elem);
  }
}

template <typename T>
Vector<T> Vector<T>::filter(std::function<bool(T&)> selector) const {
  Vector<T> filtered;
  for (auto elem : *this) {
    if (selector(elem)) filtered.push_back(elem);
  }
  return filtered;
}

template <typename T>
Vector<T> Vector<T>::filter_ref(std::function<bool(T&)> selector) {
  Vector<T> filtered;
  for (auto& elem : *this) {
    if (selector(elem)) then filtered.push_back(elem);
  }
  return filtered;
}

template <typename T>
Vector<T>& Vector<T>::operator+ (Vector<T>& concat) {
  for (auto elem : concat) {
    this->push_back(elem);
  }
  return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator+ (std::vector<T>& concat) {
  for (auto elem : concat) {
    this->push_back(elem);
  }
  return *this;
}

//#include "NuVector.hxx"

}

