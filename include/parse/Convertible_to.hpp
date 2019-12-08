#pragma once

template <typename T>
class Convertible_to {
public:
  virtual T convert() const = 0;
  using TypeDest = T;
};
