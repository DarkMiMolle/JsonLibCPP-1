#pragma once

#include <memory>
#include <variant>
#include <string>

#include "Convertible_to.hpp"
#include "../json_files/Json.hpp"

namespace jsn_parse {

class JsonObj;
class JsonArray;

template <typename T>
class Ref {
private:
  std::shared_ptr<T> m_elem;
public:
  Ref(T* ptr) {
    m_elem.reset(ptr);
  }

  const T& get() const {
    return *m_elem;
  }
};



using ParseJsonTypes = std::variant<bool, char, int, float, std::string, Ref<JsonObj>, Ref<JsonArray>, void*>;

class Val : public Convertible_to<nu::JsonTypes> {
  using string = std::string;
public:
  Val() = delete;
  Val(string& str);

  template <typename T>
  const T& get() const;

  TypeDest convert() const override;

  void print() const;
private:
  void build_string(string& str);
  void build_number(string& str);
  void build_obj(string& str);
  void build_array(string& str);
  ParseJsonTypes m_val;
};

#include "Val.hxx"

}
