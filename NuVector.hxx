// #include "NuVector.hpp"

template <typename T>
void Vector<T>::map(std::function<void(T&)> f);

template <typename T>
Vector<T> Vector<T>::filter(std::function<bool(T&)> selector) const;

template <typename T>
T* Vector<T>::find_one(std::function<bool(T&)> finder);

template <typename T>
Vector<T> Vector<T>::find_many(std::function<bool(T&)> finder);

template <typename T>
Vector<T>& Vector<T>::operator+ (Vector<T>& concat);

template <typename T>
Vector<T>& Vecrtor<T>::operator+ (std::vector<T>& concat);
