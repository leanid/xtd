#define __XTD_CORE_NATIVE_LIBRARY__
#include <xtd/native/debug.h>
#undef __XTD_CORE_NATIVE_LIBRARY__
#include <iostream>
#include <syslog.h>

using namespace xtd::native;

void debug::write_to_output(const std::string& message) {
  syslog(LOG_EMERG | LOG_USER, "%s", message.c_str());
#if !defined(__APPLE__)
  std::cerr << message << std::flush;
#endif
}