#pragma once

#include "../Json.hpp"
#include "Val.hpp"
#include "JsnList.hpp"
#include "../NuVector.hpp"

namespace jsn_parse {


class JsonArray : public Convertible_to<nu::JsonArray> {
  using string = std::string;
public:
  JsonArray() = delete;
  JsonArray(string& str);
  JsonArray(void*);

  const Val& operator[](int i) const;
  void print() const;

  TypeDest convert() const override;
private:
  JsnList<Val> m_list;
  const bool is_null;
};

}

