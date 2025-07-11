cmake_minimum_required(VERSION 3.31)
project(workbench LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-Wall -Wextra -Wpedantic)

add_executable(workbench
        src/main.cpp
        src/module/Plugin.cpp
        src/module/DlHandle.cpp
        src/core/PluginSystem.cpp
)

target_include_directories(workbench PRIVATE src)

target_link_libraries(workbench PRIVATE
        ncurses
        menu
        dl
)

add_library(hello SHARED modules/core/hello.cpp)

set_target_properties(hello PROPERTIES PREFIX "")

target_compile_options(hello PRIVATE -fvisibility=hidden -fvisibility-inlines-hidden)

target_compile_definitions(hello PRIVATE WISE_PLUGIN_EXPORTS)

target_include_directories(hello PRIVATE modules/core)

target_link_libraries(hello PRIVATE dl)

install(TARGETS workbench hello
        RUNTIME DESTINATION ./bin
        LIBRARY DESTINATION ./lib/plugins
)
