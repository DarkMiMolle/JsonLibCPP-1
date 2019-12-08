
template <typename T>
string Jsonable::to_string(T& val) {
  if constexpr (std::is_base_of_v<Jsonable, T>) {
    return val.stringify();
  }
  if constexpr (std::is_same_v<T, std::string>) {
    return "\"" + val + "\"";
  }
  if constexpr (std::is_same_v<T, char>) {
    return string() + "\"" + val + "\"";
  }
  if constexpr (std::is_arithmetic_v<T>) {
    return std::to_string(val);
  }
  if constexpr (is_JsonArray<T>) {
    string str = "[";
    for (auto& e : val) {
      str += " " + to_string(e) + ",";
    }
    str.back() = ' ';
    str += "]";
    return str;
  }
  throw val;
}

template <typename U, typename T>
bool Jsonable::assign_if(T* val, JsonTypes& e) {
  if constexpr (std::is_base_of_v<std::vector<U>, T>) {
    if constexpr (std::is_base_of_v<Jsonable, U>) {
      val->emplace_back();
      val->back().load(std::get<Json>(e)); // not working
    }
    val->push_back(std::get<U>(e));
    return true;
  }
  return false;
}

template <typename T>
std::function<void(JsonTypes)> Jsonable::assign_gen(T* val) {
  if constexpr (std::is_base_of_v<Jsonable, T>) { // val is an Object.
    return [=](JsonTypes elem) {
      if (assign_if_JsonNull(val, elem)) {
        return;
      }

      try {
        val->load(std::get<Json>(elem));
      } catch (std::exception& e) {
        std::cout << e.what() << "\n\n";
      }
    };
  }
  if constexpr (is_JsonArray<T>) {
    return [=](JsonTypes elem) {
      auto array = std::get<JsonArray>(elem);
      for (auto& e : array.list) {
        if (assign_if<int>(val, e)) continue;
        if (assign_if<float>(val, e)) continue;
        if (assign_if<char>(val, e)) continue;
        if (assign_if<string>(val, e)) continue;
        if (assign_if<bool>(val, e)) continue;
        void* ptr = std::get_if<Json>(&e);
        if (ptr) {
          std::cout << "figure it out\n";
        }
        ptr = std::get_if<JsonArray>(&e);
        if (ptr) {
          std::cout << "figure it out\n";
        }
      }
    };
  }
  if constexpr(std::is_same_v<T, char>) {
    return [=](JsonTypes elem) {
      if (assign_if_JsonNull(val, elem)) {
        return;
      }

      *val = std::get<char>(elem);
    };
  }
  if constexpr (is_JsonTypes<T>) {
    return [=](JsonTypes elem) {
      if (assign_if_JsonNull(val, elem)) {
        return;
      }

      try {
        *val = std::get<T>(elem);
      } catch (std::exception& e) {
        std::cout << std::boolalpha << std::is_base_of_v<Jsonable, T> << '\n' <<
        e.what() << '\n';
      }
    };
  }
  return [](JsonTypes elem) {
    throw "error";
  };
}
