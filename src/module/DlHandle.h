//
// Created by paul on 11.07.25.
//

#ifndef DLHANDLE_H
#define DLHANDLE_H

#include <stdexcept>
#include <dlfcn.h>


#include <dlfcn.h>
#include <stdexcept>

class DlHandle {
  void* handle = nullptr;

public:
  explicit DlHandle(const char* path);

  ~DlHandle();

  void* get(const char* symname) const;

  template<typename T>
  T getSymbol(const char* symname) const;


  DlHandle(const DlHandle&) = delete;
  DlHandle& operator=(const DlHandle&) = delete;

  DlHandle(DlHandle&& other) noexcept : handle(other.handle) {
    other.handle = nullptr;
  }

  DlHandle& operator=(DlHandle&& other) noexcept;
};

template<typename T>
T DlHandle::getSymbol(const char *symname) const {
  return reinterpret_cast<T>(get(symname));
}


#endif //DLHANDLE_H
