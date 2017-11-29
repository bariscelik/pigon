#ifndef MATRIX_H
#define MATRIX_H

#include "pigon_global.h"
#include <stdexcept>

#include <iostream>
#include <type_traits>
#include <bitset>
#include <vector>


/**
 * @brief Type of matrix
 */
enum class MatrixType{
        Custom,
        Unit,
        Random
    };

/**
 * @brief Selection type of a dimension (row or col)
 */
enum class Select{
        Odd,
        Even,
        All
    };


namespace Pigon{

template<typename T = float> class PIGONSHARED_EXPORT Matrix
{

public:

    Matrix(size_t r=3, size_t c=2,MatrixType mt = MatrixType::Custom, const T initValue = 0);
    Matrix(std::initializer_list<std::initializer_list<T>> iList);
    ~Matrix();


    /**
     * @brief tolerance value for floating-point comparison
     */
    T TOLERANCE = 1e-10;

    /**
     * @brief Matrix index
     */
    struct m_index{
        size_t row;
        size_t col;
    };

    /**
     * @brief matrix iterator
     */
    class iterator
    {
        public:
            typedef iterator self_type;
            typedef std::vector<std::vector<T>> value_type;
            typedef std::vector<std::vector<T>>* matrix_ptr;
            typedef T& reference;
            typedef T* pointer;
            typedef int difference_type;

            iterator(matrix_ptr ptr, bool end=false) : ptr_(ptr), end(end) {
                rows = (*ptr_).size();
                cols = (*ptr_)[0].size();

                if(end)
                {
                    _row = rows-1;
                    _col = cols-1;
                }

            }

            self_type operator++() {
                if(_row < rows)
                {
                    if(_col < cols-1)
                    {
                        _col++;
                    }else{
                        _col = 0;
                        ++_row;
                    }
                }

                if(_row == rows && _col == 0)
                {
                    end = true;
                    _row = rows-1;
                    _col = cols-1;
                }

                return *this;
            }

            self_type operator++(int) {return operator++();}
            reference operator*() { return (*ptr_)[_row][_col]; }
            bool operator==(const self_type& rhs) { return _row == rhs._row && _col == rhs._col; }
            bool operator!=(const self_type& rhs) { return _row != rhs._row || _col != rhs._col || end != rhs.end; }

            const Matrix::m_index index() {
                return Matrix::m_index{_row, _col};
            }

        private:
            matrix_ptr ptr_;
            bool end;

            // matrix size
            size_t rows;
            size_t cols;

            // current row & col
            size_t _row = 0,_col = 0;

    };

    /**
     * @brief first element
     * @return iterator
     */
    iterator begin(){
        return iterator(&_m);
    }

    /**
     * @brief last element (virtual)
     * @return iterator
     */
    iterator end(){
        return iterator(&_m, true);
    }

    /**
     * @brief rows
     * @return rows count
     */
    size_t rows();

    /**
     * @brief rows
     * @return cols count
     */
    size_t cols();

    /**
     * @brief changes matrix size
     * @param rows new matrix rows
     * @param cols new matrix columns
     */
    void resize(const size_t rows, const size_t cols);

    /**
     * @brief Replace all matrix elements to specified values
     * @param mt type of matrix
     * @param val value to fill
     */
    void fill(MatrixType mt = MatrixType::Custom, const T val = 0);

    /**
     * @brief Replace all matrix elements to specified values
     * @param val value to fill
     */
    void fill(const T val);

    /**
     * @brief Get element by position(row,col)
     * @param i
     * @return Reference of element
     */
    T& at(m_index i);

    /**
     * @brief Get element by position(row,col)
     * @param row
     * @param col
     * @return Reference of element
     */
    T& at(size_t row, size_t col);

    /**
     * @brief Calculates determinant
     * @return Result of determinant calculation
     */
    T determinant();

    /**
     * @brief transpose
     */
    void transpose();


    /**
     * @brief Find unique elements by grouping.
     * @return Unique elements in a vector
     */
    std::vector<T> unique();

    /**
     * @brief Accumulate all elements
     * @return Result of accumulation
     */
    T sum();

    /**
     * @brief product
     * @return
     */
    T product();

    /**
     * @brief normalize
     */
    void normalize();

    /**
     * @brief shuffle
     */
    void shuffle();

    /**
     * @brief Find matched elements by given parameter.
     * @param num
     * @return Element indices as vector
     */
    std::vector<m_index> find(T num);

    /**
     * @brief Calculate inverse of matrix
     */
    void inverse();

    /**
     * @brief Finds smallest element on matrix
     * @return Index of minimum element
     */
    m_index min();

    /**
     * @brief Find greatest element on matrix
     * @return Index of maximum element
     */
    m_index max();

    // ******************* //
    // **** OPERATORS **** //
    // ******************* //

    /**
     * @brief operator []
     * @param indice
     * @return
     */
    std::vector<T> &operator[] (size_t indice);

    T &operator() (size_t row, size_t col);
    std::vector< std::vector<T> > operator() (std::vector<size_t> rows, size_t col, Select sr = Select::All, Select sc = Select::All);
    std::vector< std::vector<T> > operator() (size_t row, std::vector<size_t> cols, Select sr = Select::All, Select sc = Select::All);
    std::vector< std::vector<T> > operator() (std::vector<size_t> rows, std::vector<size_t> cols, Select sr = Select::All, Select sc = Select::All);
    std::vector< std::vector<T> > operator() (Select s, size_t col);
    std::vector< std::vector<T> > operator() (size_t row, Select s);
    std::vector< std::vector<T> > operator() (Select sr, Select sc);


    Matrix<T> operator++(int);
    Matrix<T> operator--(int n);

    //Matrix<T> &operator=(Matrix<T> &m);

    Matrix<T> operator+(Matrix<T> m);
    Matrix<T> operator+(T number);

    Matrix<T> &operator+=(Matrix<T> m);
    Matrix<T> &operator+=(T number);

    Matrix<T> operator-(Matrix<T> m);
    Matrix<T> operator-(T number);

    Matrix<T> &operator-=(Matrix<T> m);
    Matrix<T> &operator-=(T number);

    Matrix<T> operator*(Matrix<T> m);
    Matrix<T> operator*(T number);

    Matrix<T> &operator*=(Matrix<T> m);
    Matrix<T> &operator*=(T number);

    Matrix<T> operator/(T number);

    Matrix<T> &operator/=(T number);

private:

    /**
     * @brief matrix that stores elements
     */
    std::vector< std::vector<T> > _m;

    std::vector< std::vector<T> > select(std::vector<size_t> rows, std::vector<size_t> cols, Select sr = Select::All, Select Select = Select::All);
    std::vector< std::vector<T> > _select(std::vector<size_t> rows, std::vector<size_t> cols);

    inline bool isEven(size_t n);
    inline bool isOdd(size_t n);
    size_t _rows;
    size_t _cols;
    T determinant(const std::vector<std::vector<T>> m, const size_t n=0);
};

typedef Matrix<> Matrixf;
typedef Matrix<int> Matrixi;
typedef Matrix<double> Matrixd;
}

#endif // MATRIX_H

// TODO: Kütüphane dosyasına dahil edilecek
std::ostream& operator<<(std::ostream &os, Pigon::Matrix<float> &m)
{
    std::string s;

    s.append("------------------------------------------------------------------------------------------\n");

    for (size_t i=0;i<m.rows();i++) {
        for (size_t j=0;j<m.cols();j++) {
            s.append(std::to_string(m[i][j]) + " | ");
        }
        s.append("\n");
    }

    s.append("\nMatrix Size: " + std::to_string(m.rows()) + "x" + std::to_string(m.cols()));

    s.append("\n------------------------------------------------------------------------------------------");

    return os << s;
};

std::ostream& operator<<(std::ostream &os, Pigon::Matrix<int> &m)
{
    std::string s;

    s.append("------------------------------------------------------------------------------------------\n");

    for (size_t i=0;i<m.rows();i++) {
        for (size_t j=0;j<m.cols();j++) {
            s.append(std::to_string(m[i][j]) + " | ");
        }
        s.append("\n");
    }

    s.append("\nMatrix Size: " + std::to_string(m.rows()) + "x" + std::to_string(m.cols()));

    s.append("\n------------------------------------------------------------------------------------------");

    return os << s;
};

//template std::ostream& operator<<(std::ostream&, const Pigon::Matrix<float>&);
