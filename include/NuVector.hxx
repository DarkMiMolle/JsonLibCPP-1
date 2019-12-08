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
    if (selector(elem)) filtered.push_back(elem);
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
