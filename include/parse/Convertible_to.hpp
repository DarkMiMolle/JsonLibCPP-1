#pragma once

namespace jsn_parse {

template <typename T>
class Convertible_to {
public:
  virtual T convert() const = 0;
  using TypeDest = T;
};


}
