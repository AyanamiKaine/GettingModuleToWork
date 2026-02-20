# GettingModuleToWork

A C++23 project demonstrating C++ modules with CMake. The `math` module is built as a separate installable CMake package, then consumed by the main application via `find_package`.

## Prerequisites

- CMake 3.28+
- Ninja
- Clang++ (tested with Clang 21)

## Build and Run

### 1. Build and install the math module

```bash
cmake -B math_module/build -S math_module -G Ninja -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_INSTALL_PREFIX="C:/C++/Modules"
cmake --build math_module/build
cmake --install math_module/build
```

### 2. Build the main application

```bash
cmake -B build -G Ninja -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_PREFIX_PATH="C:/C++/Modules"
cmake --build build
```

### 3. Run

```bash
./build/app.exe
```

## Global installation

To avoid passing `-DCMAKE_PREFIX_PATH` every time, set a persistent environment variable so CMake always knows where to find installed modules:

```powershell
# PowerShell (permanent, user-level)
[Environment]::SetEnvironmentVariable("CMAKE_PREFIX_PATH", "C:/C++/Modules", "User")
```

After restarting your terminal, any project using `find_package(math_module REQUIRED)` will find it automatically without needing `-DCMAKE_PREFIX_PATH` on the command line.

## Switching compilers

If you switch between compilers (e.g., MSVC and Clang), you must delete all build directories and reinstall to avoid stale artifacts:

```bash
rm -rf math_module/build build
```

Then follow the build steps above with your desired compiler.
