<!-- OPENSPEC:START -->
# OpenSpec Instructions

These instructions are for AI assistants working in this project.

Always open `@/openspec/AGENTS.md` when the request:
- Mentions planning or proposals (words like proposal, spec, change, plan)
- Introduces new capabilities, breaking changes, architecture shifts, or big performance/security work
- Sounds ambiguous and you need the authoritative spec before coding

Use `@/openspec/AGENTS.md` to learn:
- How to create and apply change proposals
- Spec format and conventions
- Project structure and guidelines

Keep this managed block so 'openspec update' can refresh the instructions.

<!-- OPENSPEC:END -->

# AGENTS.md

This file provides guidance to Qoder (qoder.com) when working with code in this repository.

## Project Overview

A C++ demonstration project showcasing CMake build system best practices with GitHub Actions CI/CD. The project consists of two main libraries (`algorithms` and `data_structures`) with corresponding executables and comprehensive test suites using Google Test.

## Build Commands

### Configuration and Build
```bash
# Configure build (Release)
cmake -B build -DCMAKE_BUILD_TYPE=Release

# Configure build (Debug)
cmake -B build -DCMAKE_BUILD_TYPE=Debug

# Build the project
cmake --build build --config Release

# Build with parallel compilation
cmake --build build --config Release -j 4
```

### Testing
```bash
# Run all tests
ctest --test-dir build --config Release --output-on-failure

# Run specific test suite
./build/bin/algorithms_tests
./build/bin/data_structures_tests
```

### CMake Options
- `BUILD_TESTING` (default: ON) - Build test suite
- `ENABLE_WARNINGS` (default: ON) - Enable compiler warnings

```bash
# Disable testing
cmake -B build -DBUILD_TESTING=OFF

# Disable warnings
cmake -B build -DENABLE_WARNINGS=OFF
```

### Running Executables
```bash
# Main application (demonstrates all features)
./build/bin/main_app

# CLI tool
./build/bin/cli_tool help
./build/bin/cli_tool sort 5 2 8 1 9
./build/bin/cli_tool search 5 1 2 5 8 9
```

## Architecture

### Library Structure

The project uses Modern CMake practices with two primary libraries:

1. **algorithms** (`src/algorithms/`)
   - Header-only interfaces in `include/algorithms/`
   - Implementations in `src/`
   - Components: sort, search, string_algorithms, dp_algorithms
   - Exported as `Demo::algorithms` alias

2. **data_structures** (`src/data_structures/`)
   - Header-only interfaces in `include/data_structures/`
   - Implementations in `src/`
   - Components: linked_list, stack_queue, heap, avl_tree, skip_list
   - Exported as `Demo::data_structures` alias

### Dependency Management

- **Google Test**: Automatically fetched via CMake FetchContent (v1.14.0)
- Configuration in `cmake/GoogleTest.cmake`
- Test discovery uses `gtest_discover_tests()`

### Compiler Warnings

Custom function `set_compiler_warnings()` defined in `cmake/CompilerWarnings.cmake`:
- MSVC: `/W4` warning level
- GCC/Clang: `-Wall -Wextra -Wpedantic`

### Testing Organization

Two test executables in `tests/`:
- `algorithms_tests` - Links to `Demo::algorithms` + `gtest_main`
- `data_structures_tests` - Links to `Demo::data_structures` + `gtest_main`

Each test executable automatically discovers tests using GoogleTest's test discovery mechanism.

## CI/CD

GitHub Actions workflow (`.github/workflows/ci.yml`) runs on:
- Platforms: Ubuntu, macOS, Windows
- Build types: Debug, Release
- Total: 6 build matrix combinations
- Features: CMake caching, parallel builds (-j 4), artifact uploads

## Development Workflow

### Adding New Algorithms
1. Create header in `src/algorithms/include/algorithms/`
2. Implement in `src/algorithms/src/`
3. Add source file to `src/algorithms/CMakeLists.txt`
4. Create tests in `tests/algorithms/`
5. Add test file to `tests/CMakeLists.txt`

### Adding New Data Structures
1. Create header in `src/data_structures/include/data_structures/`
2. If not header-only, implement in `src/data_structures/src/` and add to `src/data_structures/CMakeLists.txt`
3. Create tests in `tests/data_structures/`
4. Add test file to `tests/CMakeLists.txt`

## Technical Standards

- C++17 standard (required)
- CMake 3.14+ minimum
- Smart pointers for memory management
- Output directories: `build/bin/` (executables), `build/lib/` (libraries)
