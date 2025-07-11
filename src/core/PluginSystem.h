//
// Created by paul on 11.07.25.
//

#ifndef PLUGINSYSTEM_H
#define PLUGINSYSTEM_H

#include "module/Plugin.h"


class PluginSystem {
public:
  static void LoadPlugins(const std::filesystem::path& pluginPath);
  static Plugin& GetPlugin(const std::string& name);
private:
  static inline std::vector<Plugin> loaded_plugins;
};


#endif //PLUGINSYSTEM_H
