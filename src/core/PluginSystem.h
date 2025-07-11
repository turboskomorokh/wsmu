//
// Created by paul on 11.07.25.
//

#ifndef PLUGINSYSTEM_H
#define PLUGINSYSTEM_H

#include "module/Pluggable.h"


class PluginSystem {
  static inline std::vector<Pluggable> loaded_plugins;
public:
  static void LoadPlugins(const std::filesystem::path& pluginPath);
  static Pluggable& GetPlugin(const std::string& name);
};


#endif //PLUGINSYSTEM_H
