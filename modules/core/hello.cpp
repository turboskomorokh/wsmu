#include <cstdio>
#include <print>
#include <stdexcept>

extern "C" const char *WSMU_PLUGIN_NAME = "hello";
extern "C" long WSMU_PLUGIN_VERSION = 100L;

extern "C" const char *WSMU_PLUGIN_COMMAND_LIST[] = {
  "echo",
  nullptr
};

extern "C" int echo(int argc, const char *argv[]) {
  const std::span args(argv, argc);
    for (const char* arg : args) {
      if (arg)
        std::print("{} ", arg);
    }
    std::println();
  return EXIT_SUCCESS;
}


