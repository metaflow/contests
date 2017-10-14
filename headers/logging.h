#ifndef H_LOGGING
#define H_LOGGING
#include "prettyprint.h"

bool _first_debug_output = true;

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
T debug(T&& arg, O&&... args) {
  std::stringstream ss;
  _out_to_stream(ss, std::forward<T>(arg), std::forward<O>(args)...);
  std::cerr << ss.str() << std::endl;
  return arg;
}

#endif  // H_LOGGING
