//
// Created by paul on 11.07.25.
//

#include "DlHandle.h"

DlHandle::DlHandle(const char *path) {
  handle = dlopen(path, RTLD_NOW);
  if (!handle)
    throw std::runtime_error(dlerror());
}

DlHandle::~DlHandle() {
  if (handle)
    dlclose(handle);
}

void * DlHandle::get(const char *symname) const {
  void* symPtr = dlsym(handle, symname);
  if (!symPtr)
    throw std::runtime_error(dlerror());
  return symPtr;
}

DlHandle & DlHandle::operator=(DlHandle &&other) noexcept {
  if (this != &other) {
    if (handle) dlclose(handle);
    handle = other.handle;
    other.handle = nullptr;
  }
  return *this;
}

