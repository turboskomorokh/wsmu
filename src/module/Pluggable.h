//
// Created by paul on 11.07.25.
//

#ifndef PLUGGABLE_H
#define PLUGGABLE_H

#include <filesystem>
#include <memory>

#include <string>
#include <vector>

#include <dlfcn.h>
#include <unordered_map>

#include "DlHandle.h"

using FuncType = int(*)(int, const char**);

class Pluggable {
public:
  explicit Pluggable(const std::filesystem::path& path);
  virtual ~Pluggable() = default;

  Pluggable(Pluggable&&) = default;
  Pluggable& operator=(Pluggable&&) = default;

  [[nodiscard]] std::vector<std::string> getCommands() const;
  int execute(const char* command, const std::vector<std::string>& args);
  int execute(const char *command, int argc, const char *argv[]);
  std::string getName() const;
  long getVersion() const;

private:
  DlHandle dlData;
  std::unordered_map<std::string, FuncType> commands;
  std::string name, filename;
  long version;
};


#endif //PLUGGABLE_H
