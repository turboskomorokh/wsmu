//
// Created by paul on 11.07.25.
//

#include <vector>

#include "Plugin.h"

#include <ranges>

Plugin::Plugin(const std::filesystem::path& path) : dlData(path.c_str()), filename(path.filename().string()) {

  const auto rawNamePtr = dlData.getSymbol<const char**>("WISE_PLUGIN_NAME");
  const auto rawVersionPtr = dlData.getSymbol<long*>("WISE_PLUGIN_VERSION");

  if (!rawNamePtr)
    throw std::runtime_error("Plugin {} does not have a name symbol.");
  if (!rawVersionPtr)
    throw std::runtime_error("Plugin {} does not have a version symbol");

  name = std::string(*rawNamePtr);
  version = static_cast<long>(*rawVersionPtr);

  for (auto cmdPtr = dlData.getSymbol<const char**>("WISE_PLUGIN_COMMAND_LIST"); *cmdPtr != nullptr; ++cmdPtr) {
    using FuncType = int(*)(int, const char**);
    const auto func = dlData.getSymbol<FuncType>(*cmdPtr);
    commands[*cmdPtr] = func;
  }
}

std::vector<std::string> Plugin::getCommands() const {
  std::vector<std::string> commandList;
  commandList.reserve(commands.size());
  for (const auto &cmd: commands | std::views::keys)
    commandList.emplace_back(cmd);
  return commandList;
}

int Plugin::execute(const char* command, const std::vector<std::string>& args) {
  std::vector<const char*> argv;
  argv.reserve(args.size());
  for (const auto& s : args)
    argv.push_back(s.c_str());

  if (args.empty()) {
    return execute(command, 0, nullptr);
  }

  return execute(command, static_cast<int>(argv.size()), argv.data());
}

int Plugin::execute(const char* command, int argc, const char* argv[]) {
  const auto it = commands.find(command);
  if (it == commands.end()) {
    throw std::runtime_error(std::format("command not found: {}", command));
  }
  return it->second(argc, argv);
}

std::string Plugin::getName() const {
  return name;
}

long Plugin::getVersion() const {
  return version;
}



