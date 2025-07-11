//
// Created by paul on 11.07.25.
//

#include <print>

#include "PluginSystem.h"

#include <ranges>

void PluginSystem::LoadPlugins(const std::filesystem::path &pluginPath) {
  for (const auto &entry: std::filesystem::directory_iterator(pluginPath)) {
    if (entry.is_regular_file()) {
      const auto &path = entry.path();
      try {
        loaded_plugins.emplace_back(path);
      } catch (const std::exception &e) {
        std::println("Exception while loading {}: {}", path.string(), e.what());
      }
    }
  }

  std::println("Found {} available plugins:", loaded_plugins.size());

  for (const auto &plugin: loaded_plugins) {
    std::println("{}:{}", plugin.getName(), plugin.getVersion());
  }
}

Plugin& PluginSystem::GetPlugin(const std::string& name) {
  for (auto& plugin : loaded_plugins) {
    if (plugin.getName().find(name) != std::string::npos)
      return plugin;
  }
  throw std::runtime_error("Plugin not found: " + name);
}


