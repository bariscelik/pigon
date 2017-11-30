# Pigon - scientific toolbox
Pigon is an open source library for scientific purposes

# Introduction
Pigon is contains some tools for mathematics and physics. Programming principle that behind of Pigon is quite simple. This is more like an API rather than a library. Readability

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

# Usage
Some basic concepts are explained in this document about mathematics and physics in Pigon.

## Matrix
Matrix tool has a lot of mathematical functions like that

* determinant
* transpose
* unique
* sum, product
* normalize
* shuffle
* inverse
* min, max

### Initialization
It is possible to carry out an initialization in two ways:

#### 1. Initializer List
```cpp
// initialize a 3x3 matrix with initializer list
Matrix<float> m = { {1, 3, 5},
                    {2, 5, 6},
                    {4, 8, 7} };
```
#### 2. With Constructor
```cpp
// initialize a 3x3 random matrix with constructor function
Matrix<float> m(3, 3, MatrixType::Random);
```

### Selection
In pigon, there are too many selection types for matrices. 

