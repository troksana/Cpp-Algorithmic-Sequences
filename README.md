# Algorithmic Sequence Processor & Splicer (C++)

A modern, cross-platform C++ utility designed for generating, manipulating, and analyzing mathematical and data sequences. This project highlights functional template programming, efficient string/data splicing algorithms, and utilizes a professional CMake build system configuration.

## Features

* **Sequence Generation & Manipulation:** Specialized algorithms (`sequence.hpp`) designed to process data sets with minimal memory overhead.
* **String & Data Splicing:** Modular utilities (`split.hpp`) optimizing tokenization, custom boundary isolation, and sequence splitting techniques.
* **Cross-Platform Build System:** Fully managed via modern CMake, utilizing build presets for seamless environment configuration.

## Concepts Demonstrated

* **Language:** Modern C++ (Focusing on generic programming and type safety via templates).
* **Build System:** CMake (utilizing `CMakeLists.txt` and `CMakePresets.json` for reproducible builds across Windows, Linux, and macOS).
* **Algorithmic Complexity:** High-efficiency data tokenization and sequential transformations designed to prevent unnecessary data copying ($O(N)$ operational targets).

## Project Component Breakdown

* `CMakeLists.txt` - Core build instruction script defining project targets, compiler flags, and dependency tracking.
* `CMakePresets.json` - Standardized build and configure presets ensuring environment-agnostic execution.
* `sequence.hpp` - Core algorithms for managing sequential data structures and transformations.
* `split.hpp` - High-performance splicing and parsing mechanics for handling sequence boundaries.
* `main.cpp` - Entry point demonstrating practical sequence operations, processing execution, and testing outputs.
