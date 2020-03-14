# unamed00

## Getting Started

This project was generated from [this template](https://github.com/Mathieu-Lala/template_cpp_project)

### Prerequisite

This project is build with the package manager Conan.
Make sure you have [installed conan](https://docs.conan.io/en/latest/installation.html) and configured your profile and your remotes.

### Installing

Building on unix platform :

```bash
$> ./make.sh [Debug|Release]
```

You can also generate a Visual Studio Solution from this repo.

## Running the tests

To build the tests :

```bash
$> ./make.sh Test
```

After that, to generate the coverage as html (in build/coverage/index.html):

```bash
$> make -C build coverage
```

## Documentation

The documentation is generated with the Release build. It contains :

* a graph of the external dependencies
* a list of all the sources files and the all the macro / function / class / namespace ...
* a todo / bug / issues list

## Built With

* [Conan](https://conan.io/) - The package and dependencies manager
* [CMake](https://cmake.org/) - Cross-platform Building Tool
* [Travis](https://travis-ci.org/) - Continuous integration service for github project
* [Ctest](https://cmake.org/cmake/help/latest/manual/ctest.1.html) - CMake test driver program
* [Catch2](https://github.com/catchorg/Catch2) - Testing Framework
* [Gcov](https://gcc.gnu.org/onlinedocs/gcc/Gcov.html) - Code coverage generator
* [Doxygen](http://www.doxygen.nl/) - Documentation Generator

## Authors

* **Mathieu Lala** - *Initial work* - [Github](https://github.com/Mathieu-Lala)

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE.md) file for details
