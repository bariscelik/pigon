# Pigon - scientific toolbox
Pigon is an open source C++ library for scientific purposes

[TOC]

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

> Note: Row and col numbers starts from 0 in pigon.

```cpp
// initialize a 3x3 matrix
Matrix<float> m = { {1, 3, 5},
                    {2, 5, 6},
                    {4, 8, 7} };
```
$$
M_{3x3}=\begin{bmatrix} 1 & 3 & 5 \\ 2 & 5 & 6 \\ 4 & 8 & 7 \end{bmatrix}
$$

Selection of single element:

```cpp
// row=1, col=2
std::cout << m[1][2] << std::endl; // 6 [row][col]
std::cout << m(1, 2) << std::endl; // 6 (row, col) these are same things
```



Selection an array of rows and single column

```cpp
// row={0, 1}, col=2
Matrix<float> m_sub = m({0, 1}, 2);
```

$$
m\_sub=\begin{bmatrix} 5 \\ 6 \end{bmatrix}
$$



Selection an array of rows and columns

```cpp
// row={0, 1}, col={0, 1}
Matrix<float> m_sub = m({0, 1}, {1, 2});
```

$$
m\_sub=\begin{bmatrix} 3 & 5 \\ 5 & 6 \end{bmatrix}
$$

By Select::type

```cpp
// row=All, col={0, 2}
Matrix<float> m_sub = m(Select::All, {0, 2});
```

$$
m\_sub=\begin{bmatrix} 1 & 5 \\ 2 & 6 \\ 4 & 7\end{bmatrix}
$$

Here is an example MathJax inline rendering \\( 1/x^{2} \\), and here is a block rendering: 
\\[ \frac{1}{n^{2}} \\]