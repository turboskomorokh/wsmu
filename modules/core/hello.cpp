#include <cstdio>
#include <stdexcept>

extern "C" const char *WISE_PLUGIN_NAME = "Hello";
extern "C" long WISE_PLUGIN_VERSION = 100L;

extern "C" const char *WISE_PLUGIN_COMMAND_LIST[] = {
  "hello",
  nullptr
};

extern "C" int hello(int argc, const char *argv[]) {
  return std::printf("Hello, world!\n");
}
