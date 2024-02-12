# Foreground Pattern Scanner - Memory-mapped executable pattern scanner

This repository contains a C++ program called `ForegroundPatternScanner.cpp` designed to scan the executable files of foreground windows for specific patterns. The program utilizes memory mapping to load the executable file of the foreground window into memory and then scans its content for predefined byte patterns.

## Overview

The `ForegroundPatternScanner.cpp` program utilizes Windows APIs to retrieve information about the foreground window and the associated process. Instead of directly scanning the process's memory, it maps the executable file of the process into memory using file mapping techniques. It then scans the mapped file for predefined byte patterns that represent signatures of known applications. If a match is found, it outputs the file path of the executable associated with the process.

## Installation

To use this project, you can clone the repository and compile it using a C++ compiler:

```bash
git clone https://github.com/NIR3X/ForegroundPatternScanner.cpp --recurse-submodules
cd ForegroundPatternScanner.cpp
make
```

## Dependencies

* This program relies on the following dependencies:
	* `FastPatternsScanner.cpp/FastPatternsScanner.h`: A header file providing functionality for fast pattern scanning.
	* `FileMapping.cpp/FileMapping.h`: A header file containing utilities for file mapping.

## Usage

To use the `ForegroundPatternScanner.cpp` program, simply compile it using a compatible C++ compiler and run the resulting executable. The program will continuously monitor the foreground window and map the executable file of the corresponding process into memory. It will then scan the mapped file for predefined patterns.
Example Patterns

The program comes preconfigured with patterns representing signatures of various applications such as Cheat Engine, x64dbg, Process Hacker, OllyDbg, Scylla, IDA, Extreme Injector v3, CrySearch, Squalr, and Binary Ninja. These patterns can be customized or extended as needed.

## License
[![GNU AGPLv3 Image](https://www.gnu.org/graphics/agplv3-155x51.png)](https://www.gnu.org/licenses/agpl-3.0.html)  

This program is Free Software: You can use, study share and improve it at your
will. Specifically you can redistribute and/or modify it under the terms of the
[GNU Affero General Public License](https://www.gnu.org/licenses/agpl-3.0.html) as
published by the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
