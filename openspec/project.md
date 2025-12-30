# Project Context

## Purpose
A C++ demonstration project showcasing CMake build system best practices with GitHub Actions CI/CD. This project serves as a learning platform for algorithms, data structures implementation, and modern C++ development workflow.

## Tech Stack
- **Language**: C++17
- **Build System**: CMake 3.14+
- **Testing Framework**: Google Test 1.14.0
- **CI/CD**: GitHub Actions (multi-platform: Ubuntu, macOS, Windows)
- **Version Control**: Git

## Project Conventions

### Code Style
- C++17 standard required
- Header files in `include/module_name/`, implementations in `src/`
- Template classes implemented directly in header files
- Smart pointers for memory management
- Snake_case for functions and variables
- PascalCase for classes and structs
- Compiler warnings enabled by default:
  - MSVC: `/W4`
  - GCC/Clang: `-Wall -Wextra -Wpedantic`

### Architecture Patterns
- **Modern CMake**: Target-based design with namespace aliases (`Demo::algorithms`, `Demo::data_structures`)
- **Library Separation**: Two primary libraries (algorithms, data_structures)
- **Header-Only Interfaces**: Public API in `include/`, private implementations in `src/`
- **Modular Testing**: Separate test executables per library
- **Output Directories**: `build/bin/` for executables, `build/lib/` for libraries

### Testing Strategy
- Google Test framework with `gtest_main` for automatic test runner
- Test files mirror source structure: `tests/algorithms/` and `tests/data_structures/`
- Test discovery via `gtest_discover_tests()`
- Required: all new features must have corresponding unit tests
- Validation: `ctest --test-dir build --output-on-failure` must pass before commit
- Run executables to verify integration:
  - `./build/bin/main_app` - demonstrates all features
  - `./build/bin/cli_tool` - command-line interface testing

### Git Workflow
- CI runs on: push to main/master, pull requests, manual workflow dispatch
- Build matrix: 2 build types (Debug, Release) × 3 platforms (Ubuntu, macOS, Windows)
- Required: all CI checks must pass
- Features: CMake caching, parallel builds (`-j 4`), artifact uploads
- Standard commits - no special conventions enforced

## Domain Context
This project implements classical computer science algorithms and data structures:
- **Algorithms**: sorting (quick, merge, heap), searching (binary), string manipulation, dynamic programming
- **Data Structures**: linked lists, stacks, queues, heaps, AVL trees, skip lists, B-trees
- Focus on educational clarity over production optimization

## Important Constraints
- Minimum CMake version: 3.14
- C++17 compliance required
- No external dependencies beyond Google Test (auto-fetched via FetchContent)
- Cross-platform compatibility: Linux, macOS, Windows
- CMake options:
  - `BUILD_TESTING` (default: ON) - can disable for faster builds
  - `ENABLE_WARNINGS` (default: ON) - can disable if needed

## External Dependencies
- **Google Test**: Version 1.14.0, fetched automatically via CMake FetchContent
- Configuration: `cmake/GoogleTest.cmake`
- No runtime external services or APIs required