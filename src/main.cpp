#include <ncurses.h>
#include <menu.h>

#include <string>
#include <print>
#include <unordered_map>

#include "core/PluginSystem.h"
#include "module/Pluggable.h"

const std::string utility_message = R"(
 _ _ _  _____  _____  _____
| | | ||     ||   __||   __|
| | | ||-   -||__   ||   __|
|_____||_____||_____||_____|
Workbench internal setup environment.
)";

int main() {
  std::println("{}", utility_message);
  PluginSystem::LoadPlugins("./plugins");

  Pluggable& plugin = PluginSystem::GetPlugin("Hello");
  plugin.execute("hello", {});
}