#include <string>
#include <print>

#include <span>

#include "core/PluginSystem.h"
#include "module/Plugin.h"

#define WSMU_version "1.0-devel"
#define WSMU_DIR /srv/wsmu

const std::string utility_message = R"(
 _ _ _  _____  _____  _____
| | | ||   __||     ||  |  |
| | | ||__   || | | ||  |  |
|_____||_____||_|_|_||_____|
____________________________________
Workbench server management utility.
Version: )" WSMU_version R"(
____________________________________
)";

int main(int argc, char* argv[]) {
  if (argc <= 1) {
    std::println("{}", utility_message);
    return 0;
  }
  std::span<const char* const> args(argv + 1, argc - 1);

  PluginSystem::LoadPlugins("./plugins");

  Plugin& plugin = PluginSystem::GetPlugin(args[0]);

  if (args.size() < 2) {
    std::println("Usage: <plugin_name> <command> [args...]");
    return 1;
  }

  auto execArgs = std::span(args.data() + 2, args.size() > 2 ? args.size() - 2 : 0);

  if (std::string_view(args[1]) == "version") {
    std::print("{} version {}\n", plugin.getName(), plugin.getVersion());
    return 0;
  }
  if (std::string_view(args[1]) == "commands") {
    auto commands = plugin.getCommands();
    std::println("{} commands:", plugin.getName());
    for (const auto& command : commands) {
      std::println("{}", command);
    }
    return 0;
  }
  plugin.execute(args[1], execArgs);
}

