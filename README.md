# Pigon - Engineering Toolbox [![Build Status](https://travis-ci.org/bariscelik/pigon.svg?branch=master)](https://travis-ci.org/bariscelik/pigon)
A cross-platform template classes based library in C++ which includes linear algebra and various engineering solutions

# Introduction
Pigon is consists of several tools for 3d graphics, mathematics, engineering solutions.

## A Quick Example
```cpp
Matrix<float> m = { {2,5},
                    {3,7} };
```
## Features
- Easy to learn
- Minimal (size & usage)
- No third-party dependencies
- Cross platform (Windows, Linux, Mac OS X) (gcc, clang, msvc)
- Written with pure mathematics
- High intelligibility and readability
- Performance-focused design

# Installation
There are 2 steps for installation:

## Step 1. Include
Include header files that you need like that:
```cpp 
#include "pigon/pigon.h"
#include "pigon/matrix.h"
```
## Step 2. Initialization
```cpp
// create a 4x4 unit matrix in float type
Matrixf m4x4(4, 4, MatrixType::Unit);
```

## License

Pigon is an open source software licensed under MIT. See the LICENSE.txt file for more

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
