#include "include/json_files/Json.hpp"
#include "include/NuVector.hpp"

#include "include/JsonExeption.hpp"

#include <iostream>

using namespace std;

/*--------------- PRIVATE FUNC ------------------*/


string analyse_cut_var(string str) {
  string dst;
  int braket = 0, accolade = 0;
  bool dquot_op = false;
  for (size_t i = 0; i < str.size(); ++i) {
    if (str[i] == '"') dquot_op = !dquot_op;
    if (str[i] != ' ' || dquot_op) {
      dst += str[i];
    }
    if (!dquot_op) {
      if (str[i] == '[') ++braket;
      else if (str[i] == ']') --braket;
      else if (str[i] == '{') ++accolade;
      else if (str[i] == '}') -- accolade;
    }
  }

  if (dquot_op || braket != 0 || accolade != 0) throw nu::ParseError('}');
  return dst;
}


bool is_var_name(string actual, char to_add) {
  if ((to_add < 'a' || to_add > 'z') && (to_add < 'A' || to_add > 'z')) {
    if (actual.size() == 1) return false;
    return ((to_add >= '0' && to_add <= '9') || to_add == '_' || to_add == '-');
  }
  return true;
}

string var_name(string& str) {
  size_t start = 0, end = 0;
  for (; start < str.size() && str[start] != '"'; ++start);
  if (str[start] != '"') throw "error var name";
  str = str.substr(start + 1);
  string var_name = "\"";
  for (end = 0; end < str.size(); ++end) {
    auto c = str[end];
    if (c == '"') {
      var_name += c;
      break;
    }
    if (!is_var_name(var_name, c)) throw "error var name";
    var_name += c;
  }
  if (var_name.back() != '"') throw "error var name";
  str = str.substr(end + 1);
  return var_name;

}

string val_to_char(string& str, char elem) {
  string ret;
  bool is_string = false;
  for (size_t i = 0; i < str.size(); ++i) {
    ret += str[i];
    if (str[i] == '"' && str[i - 1] != '\\') is_string = !is_string;
    else if (!is_string && str[i] == elem) {
      str = str.substr(i + 1);
      return ret;
    }
  }
  throw "error parsing: unterminated val, missing elem";
}

string val_array(string& str) {
  return val_to_char(str, ']');
}

string val_obj(string& str) {
  return val_to_char(str, '}');
}

string val_string(string& str) {
  string val = "\"";
  for (size_t i = 1; i < str.size(); ++i) {
    if (str[i] == '"' && str[i - 1] == '\\') val.pop_back();
    if (str[i] == '"' && str[i - 1] != '\\') {
      val += str[i];
      str = str.substr(i + 1);
      return val;
    }
    val += str[i];
  }
  throw "error parsing: unterminated string, missing \"";
}

string val_number(string& str) {
  string number;
  number += str.front();
  bool is_float = false;
  for (size_t i = 1; i < str.size(); ++i) {
    if (str[i] >= '0' && str[i] <= '9') number += str[i];
    else if (str[i] == '.') {
      if (is_float) throw "error parsing: number can have only one '.' to mark them as float";
      else {
        is_float = true;
        number += str[i];
      }
    } else if (str[i] == ',' || str[i] == ' ' || str[i] == ']' || str[i] == '}') {
      str = str.substr(i);
      return number;
    } else throw "error parsing, value must be separated.";
  }
  throw "error parsing, unterminate json";
}

string val(string& str) {
  size_t start = 0;
  while (str[start] == ' ') ++start;
  str = str.substr(start);
  if (str.front() == '"') {
    return val_string(str);
  } else if (str.front() >= '0' && str.front() <= '9') {
     return val_number(str);
  } else if (str.substr(0, 4) == "null" || str.substr(0, 4) == "true") {
    auto val = str.substr(0, 4);
    str = str.substr(4); // should be juste after the null/true
    return val;
  } else if (str.substr(0, 5) == "false") {
    str = str.substr(5);
    return str.substr(0, 5);
  } else if (str.front() == '{') {
    return val_obj(str);
  } else if (str.front() == '[') {
     return val_array(str);
  }
  throw nu::JsonError("invalide value parsing");
}

string var(string& str) {
  auto id = var_name(str);
  size_t next = 0;
  while (str[next] != ':') ++next;
  str = str.substr(next + 1);
  auto value = val(str);
  return id + ":" + value;
}

nu::Vector<string> cut_var(string str) {
  nu::Vector<string> array;
  bool isObj = str.front() == '{';
  if (isObj && str.back() != '}') throw nu::ParseError(str.back());

  if (isObj) str = str.substr(1, str.size());
  else {
    // FIXME: add some check
    array.push_back(val(str));
    return array;
  }

  while (str.size() > 0) {
    array.push_back(var(str));
    if (str.front() == '}') {
      return array;
    }
    if (str.front() != ',') throw "error parsing: unterminated json";
    str = str.substr(1);
  }

  array.back() = array.back().substr(0, array.back().size() - 1);
  return array;
}

constexpr bool isVar(char c) {
  return c == '"' || (c > '0' && c <= '9') || c == '{'; // || c == '["
}

nu::JsonTypes to_type(string str) {
  if (str.front() == '"' && str.back() == '"') {
    auto val = str.substr(1, str.size() - 2);
    if (val.size() == 1) {
      return val[0];
    }
    return val;
  } else if (str.front() >= '0' && str.back() <= '9') {
    if (str.find('.') != string::npos) {
      return std::stof(str);
    }
    return std::stoi(str);
  } else if (str == "true" || str == "false") {
    return str == "true";
  } else if (str == "null") {
    return nullptr;
  } else if (str.front() == '{' && str.back() == '}') {
    return nu::Json().parse(str);
  } else if (str.front() == '[' && str.back() == ']') {
    
    nu::JsonArray array;
    str = str.substr(1);
    while (str.size()) {
      for (size_t i = 0; i < str.size(); ++i) {
        if (str[i] != ' ') {
          str = str.substr(i);
          break;
        }
      }
      try {
        array.list.push_back(to_type(val(str)));
      } catch (std::exception& e) {
        // TODO
        throw e;
      }
      for (size_t i = 0; i < str.size(); ++i) {
        if (str[i] == ',') {
          str = str.substr(i + 1);
          break;
        } else if (str[i] == ']') {
          return array;
        }
      }
    }
  }
  throw "invalid value, type error";
}

std::pair<string, nu::JsonTypes> parse_var(string str) {
  str = str.substr(1);
  string varName = "";
  size_t i = 0;
  for (; str[i] != '"'; ++i) varName += str[i];
  for (; str[i] != ':' && str[i]; ++i);
  //for (; !isVar(str[i]) && str[i] && str.substr(i, 4) != "null"; ++i);
  while (str[i] == ' ') ++i;
  return std::pair(varName, to_type(str.substr(i + 1)));
}

/*-----------------------------------------------*/

namespace nu {

Json::Json(string str) : m_jsn(str) {}
Json::Json(char* str) : m_jsn(str) {}

Json& Json::parse(string str) {
  auto var_line = cut_var(str);
  var_line.map([&](string& elem) {
    auto e = parse_var(elem);
    m_map.insert(e);
  });
  return *this;
}

string Json::getString() const {
  return m_jsn;
}


}
