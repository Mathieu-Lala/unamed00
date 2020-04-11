unamed00
======

Ambition
------

The main purpose of this project is to practice my C++, and learn new techniques or syntax.

The goal is to create a 3D game engine in network with a modular conception.

Screenshots
------

### Scene Example

An example of what you can do for now :

An Asteroid like game : survive as much as wave as u can !

![Screenshot Scene Example Wave 2](./resources/screenshots/2020-04-11_19-14-53.png?raw=true "Wave 2")
![Screenshot Scene Example Wave 4](./resources/screenshots/2020-04-11_19-15-08.png?raw=true "Wave 4")
![Screenshot Scene Example Wave 8](./resources/screenshots/2020-04-11_19-17-19.png?raw=true "Wave 8")

Getting Started
------

This project was generated from [this template](https://github.com/Mathieu-Lala/template_cpp_project)

### Prerequisite

This project is build with the package manager Conan.
Make sure you have [installed conan](https://docs.conan.io/en/latest/installation.html) and configured your profile and your remotes.

### Building

[![Build Status](https://travis-ci.com/Mathieu-Lala/unamed00.svg?branch=master)](https://travis-ci.com/Mathieu-Lala/unamed00)

Building on unix platform :

```bash
$> ./make.sh [Debug|Release]
```

You can also generate a Visual Studio Solution from this repo : [tutorial](https://docs.microsoft.com/en-us/visualstudio/get-started/tutorial-open-project-from-repo?view=vs-2019)

Running the tests
------

[![codecov](https://codecov.io/gh/Mathieu-Lala/unamed00/branch/master/graph/badge.svg)](https://codecov.io/gh/Mathieu-Lala/unamed00)

To build the tests :

```bash
$> ./make.sh Test
```

After that, to generate the coverage as html (in build/coverage/index.html):

```bash
$> make -C build coverage
```

Documentation
------

The documentation is generated with the Release build. It contains :

* a graph of the external dependencies
* a list of all the sources files and the all the macro / function / class / namespace ...
* a todo / bug / issues list

Made With
------

* [Conan](https://conan.io/) - The package and dependencies manager
* [CMake](https://cmake.org/) - Cross-platform Building Tool
* [Travis](https://travis-ci.org/) - Continuous integration service for github project
* [Ctest](https://cmake.org/cmake/help/latest/manual/ctest.1.html) - CMake test driver program
* [Catch2](https://github.com/catchorg/Catch2) - Testing Framework
* [Gcov](https://gcc.gnu.org/onlinedocs/gcc/Gcov.html) - Code coverage generator
* [Doxygen](http://www.doxygen.nl/) - Documentation Generator


Authors
------

* **Mathieu Lala** - *Initial work* - [Github](https://github.com/Mathieu-Lala)

License
------

This project is licensed under the MIT License - see the [LICENSE](LICENSE.md) file for details
