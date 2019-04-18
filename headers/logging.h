#ifndef H_LOGGING
#define H_LOGGING
#include "prettyprint.h"
#include <string>

bool _first_debug_output = true;
std::string _debug_indent = "";

template<typename T>
void _out_to_stream(std::ostream& ss, T&& arg) {
  ss << std::forward<T>(arg);
}

template<typename T, typename... O>
void _out_to_stream(std::ostream& ss, T&& arg, O&&... args) {
  ss << std::forward<T>(arg) << ' ';
  _out_to_stream(ss, std::forward<O>(args)...);
}

template<typename T, typename... O>
decltype(auto) debug(T&& arg, O&&... args) {
  std::stringstream ss;
  _out_to_stream(ss, std::forward<T>(arg), std::forward<O>(args)...);
  std::cerr << _debug_indent << ss.str() << std::endl;
  return std::forward<T>(arg);
}

void debug_indent() {
  _debug_indent += "  ";
}

void debug_unindent() {
  if (_debug_indent.size() > 2) _debug_indent = _debug_indent.substr(2);
}

#endif  // H_LOGGING
