//
// Created by paul on 11.07.25.
//

#include "DLHandle.h"

DLHandle::DLHandle(const char *path) {
  handle = dlopen(path, RTLD_NOW);
  if (!handle)
    throw std::runtime_error(dlerror());
}

DLHandle::~DLHandle() {
  if (handle)
    dlclose(handle);
}

void * DLHandle::get(const char *symname) const {
  void* symPtr = dlsym(handle, symname);
  if (!symPtr)
    throw std::runtime_error(dlerror());
  return symPtr;
}

DLHandle & DLHandle::operator=(DLHandle &&other) noexcept {
  if (this != &other) {
    if (handle) dlclose(handle);
    handle = other.handle;
    other.handle = nullptr;
  }
  return *this;
}

