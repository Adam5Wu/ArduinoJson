// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#pragma once

namespace ArduinoJson {

class JsonError {
 public:
  enum Code {
    Ok,
    MissingBrace,
    MissingBracket,
    MissingColon,
    MissingComma,
    TooDeep,
    NoMemory
  };

  JsonError(Code code) : _code(code) {}

  operator Code() const {
    return _code;
  }

  const char* c_str() const {
    switch (_code) {
      case Ok:
        return "Ok";
      case MissingBrace:
        return "MissingBrace";
      case MissingBracket:
        return "MissingBracket";
      case MissingColon:
        return "MissingColon";
      case MissingComma:
        return "MissingComma";
      case TooDeep:
        return "TooDeep";
      case NoMemory:
        return "NoMemory";
      default:
        return "???";
    }
  }

 private:
  Code _code;
};

#if ARDUINOJSON_ENABLE_STD_STREAM
inline std::ostream& operator<<(std::ostream& s, const JsonError& e) {
  s << e.c_str();
  return s;
}
#endif

}  // namespace ArduinoJson
