# Infinity-cpp
This GitHub repository houses C++ implementations. Each concept is organized into 
its own self-contained project within the src folder.

## Overview

This repository serves as a resource for C++ implementations of different 
programming concepts. Each implementation is accompanied by a set of files that 
make it easy to build, run, debug, and clean the project.

## Getting Started
* If you'd like to use one of the projects in this repository, follow these simple steps:

```shell
$ git clone https://github.com/YamtalDev/D.E.L.T-BashTools.git
$ cd D.E.L.T-BashTools
$ cd src
$ cd desired_implementation

```

Inside the implementation folder, you'll find the following files:

- header_file.hpp: The header file containing the necessary declarations.
- cpp_file.cpp: The C++ source file with the implementation.
- file_test.cpp: A test file for testing the implementation.
- Makefile: A Makefile to automate compilation, running, debugging, and cleaning.

## Usage
To compile, run, debug, or clean the project, you can use the provided Makefile 
with the following commands:

```shell
# Simple compilation
$ make
# Running the project
$ make run
# Debugging the project
$ make debug
# Deleting all the obj, exe, shared/static libs files
$ make clean 
# Checking valgrind on the project
$ make vlg 
# Release compilation with optimization -O3
$ make release

```
These simple commands streamline the development process and make it easy to work 
with each project in this repository.

## Contact

For any questions about the project:

### Name: Tal Aharon
### Email: tal.aharon.work@gmail.com