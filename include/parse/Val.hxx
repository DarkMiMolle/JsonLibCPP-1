
#include "../JsonExeption.hpp"

template <typename T>
const T& Val::get() const {
  try {
    if constexpr (std::is_same_v<T, JsonArray> || std::is_same_v<T, JsonObj>) {
      if (std::holds_alternative<void*>(m_val)) {
        return T(std::get<void*>(m_val));
      }
      return std::get<Ref<T>>(m_val).get();
    } else if constexpr (!(std::is_same_v<T, JsonArray> || std::is_same_v<T, JsonObj>)) {
      if (std::holds_alternative<void*>(m_val)) {
        return T();
      }
      return std::get<T>(m_val);
    }
    throw "should never be here\n";
  } catch (nu::JsonError& e) {
    throw;
  }
}

/*template <>
const JsonArray& Val::get<JsonArray>() const {
  try {
    return std::get<Ref<JsonArray>>(m_val).get();
  } catch (nu::JsonError& e) {
    throw;
  }
}

template <>
const JsonObj& Val::get<JsonObj>() const {
  try {
    return std::get<Ref<JsonObj>>(m_val).get();
  } catch (nu::JsonError& e) {
    throw;
  }
}*/

