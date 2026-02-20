# Creating and Installing C++23 Modules with CMake

A guide for creating reusable C++23 modules that can be installed globally and consumed by any project with `find_package`.

## Prerequisites

- CMake 3.28+
- Ninja
- Clang++ or MSVC (tested with Clang 21)

## One-time setup

Set `CMAKE_PREFIX_PATH` so CMake always knows where your installed modules live:

```powershell
[Environment]::SetEnvironmentVariable("CMAKE_PREFIX_PATH", "C:/C++/Modules", "User")
```

Restart your terminal after running this.

## Creating a module

### Project structure

```
my_module/
├── CMakeLists.txt
└── src/
    ├── my_module.cppm       # Module interface (exported API)
    └── my_module_impl.cpp   # Module implementation
```

### CMakeLists.txt

```cmake
cmake_minimum_required(VERSION 3.28)
project(my_module LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(my_module STATIC)
target_compile_features(my_module PUBLIC cxx_std_23)

target_sources(my_module
    PUBLIC FILE_SET CXX_MODULES FILES
        src/my_module.cppm
    PRIVATE
        src/my_module_impl.cpp
)

include(GNUInstallDirs)

install(TARGETS my_module
    EXPORT my_module-targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    FILE_SET CXX_MODULES
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/my_module/cxx_modules
)

install(EXPORT my_module-targets
    NAMESPACE my_module::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/my_module
)

include(CMakePackageConfigHelpers)

file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/my_module-config.cmake"
    "include(CMakeFindDependencyMacro)\ninclude(\"\${CMAKE_CURRENT_LIST_DIR}/my_module-targets.cmake\")\n"
)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/my_module-config.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/my_module
)
```

Replace every occurrence of `my_module` with your module's name.

### Module interface (src/my_module.cppm)

```cpp
export module my_module;

export class MyClass {
public:
    MyClass() = default;
    int do_something(int a, int b);
};
```

### Module implementation (src/my_module_impl.cpp)

```cpp
module;

#include <iostream>

module my_module;

int MyClass::do_something(int a, int b) {
    return a + b;
}
```

## Building and installing

```bash
cmake -B build -S . -G Ninja -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_INSTALL_PREFIX="C:/C++/Modules"
cmake --build build
cmake --install build
```

Your module is now installed globally. Any project on your PC can use it.

## Using an installed module in a project

### CMakeLists.txt

```cmake
cmake_minimum_required(VERSION 3.28)
project(my_app LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(my_module REQUIRED)

add_executable(app main.cpp)
target_link_libraries(app PRIVATE my_module::my_module)
```

### main.cpp

```cpp
#include <print>

import my_module;

int main() {
    MyClass obj;
    std::println("Result: {}", obj.do_something(2, 3));
}
```

### Build and run

```bash
cmake -B build -G Ninja -DCMAKE_CXX_COMPILER=clang++
cmake --build build
./build/app.exe
```

No `-DCMAKE_PREFIX_PATH` needed if you set the environment variable in the one-time setup.

## Quick reference

| Step | Command |
|------|---------|
| Install a module | `cmake --install build` |
| Use in a project | `find_package(my_module REQUIRED)` + `target_link_libraries(app PRIVATE my_module::my_module)` |
| Use in source code | `import my_module;` |
| Reinstall after changes | Rebuild and run `cmake --install build` again |
| Switch compilers | Delete `build/` directory and rebuild from scratch |
