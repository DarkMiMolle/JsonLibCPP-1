#pragma once

#include "Convertible_to.hpp"
#include "../Json.hpp"
#include "JsnList.hpp"

namespace jsn_parse {

class JsonObj : public Convertible_to<nu::Json>{
  using string = std::string;
public:
  JsonObj() = delete;
  JsonObj(string& str);
  JsonObj(void* null);

  const JsnList<Var>& attributs() const;

  const Val operator[](string name) const;
  //  Val& operator[](string name);

  nu::Json convert() const override;

  void print() const;
private:
  JsnList<Var> m_list;
  const bool is_null;
};



}
