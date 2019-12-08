#pragma once

#include <vector>
#include <functional>
#include <type_traits>



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

#include "implem/NuVector.hxx"

}

