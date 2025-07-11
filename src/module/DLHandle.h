//
// Created by paul on 11.07.25.
//

#ifndef DLHANDLE_H
#define DLHANDLE_H

#include <stdexcept>
#include <dlfcn.h>


#include <dlfcn.h>
#include <stdexcept>

class DLHandle {
public:
  explicit DLHandle(const char* path);

  ~DLHandle();

  void* get(const char* symname) const;

  template<typename T>
  T getSymbol(const char* symname) const;


  DLHandle(const DLHandle&) = delete;
  DLHandle& operator=(const DLHandle&) = delete;

  DLHandle(DLHandle&& other) noexcept : handle(other.handle) {
    other.handle = nullptr;
  }

  DLHandle& operator=(DLHandle&& other) noexcept;
private:
  void* handle = nullptr;
};

template<typename T>
T DLHandle::getSymbol(const char *symname) const {
  return reinterpret_cast<T>(get(symname));
}


#endif //DLHANDLE_H
