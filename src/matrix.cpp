#include "pigon/matrix.h"
#include <tuple>
#include <chrono>
#include <thread>
#include <iostream>
#include <cassert>
#include <random>
#include <algorithm>

#define P_ASSERT(exp, message) assert(exp && message);
#define VALIDATE_SIZE(row, col) P_ASSERT(row<_rows, "row index is out of bound"); \
    P_ASSERT(col<_cols, "col index is out of bound");

namespace Pigon {


template<typename T>
Matrix<T>::Matrix(size_t r, size_t c, MatrixType mt, const T initValue)
{
    _rows = r;
    _cols = c;

    _m.resize(r);

    for (size_t i = 0;i<r;i++) {
        _m[i].resize(c);
    }

    fill(mt, initValue);
}

template<typename T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> iList)
{
    _m.insert(_m.end(), iList.begin(), iList.end());

    _rows = _m.size();
    _cols = _m[0].size();
}

template<typename T>
Matrix<T>::~Matrix()
{
    _m.clear();
}

template<typename T>
size_t Matrix<T>::rows()
{
    return _rows;
}

template<typename T>
size_t Matrix<T>::cols()
{
    return _cols;
}

template<typename T>
void Matrix<T>::resize(const size_t rows, const size_t cols)
{
    _m.resize(rows);

    for (size_t i=0;i<rows;i++) {
        _m[i].resize(cols);
    }

    _rows = rows;
    _cols = cols;
}

///
/// @brief deneme comment
///
template<typename T>
void Matrix<T>::fill(MatrixType mt, const T val)
{
    switch (mt) {

    case MatrixType::Unit :

        // fill by zero
        std::fill(_m.begin(), _m.end(), std::vector<T>(_cols,0));

        // check if square matrix
        if(_rows != _cols)
        {
            throw std::runtime_error(std::string("Not a square matrix"));
        }else{
            for(size_t i = 0; i<_rows;i++)
            {
                _m[i][i] = 1;
            }
        }

        break;

    case MatrixType::Random :
        for(size_t i = 0; i<_rows;i++)
        {
            _m[i][i] = std::rand() % 100;
        }

        break;

    default:
        std::fill(_m.begin(), _m.end(), std::vector<T>(_cols,val));

    }

    std::fill(_m.begin(), _m.end(), std::vector<T>(_cols,val));

}

///
/// @brief deneme comment
///
template<typename T>
void Matrix<T>::fill(const T val)
{
    fill(MatrixType::Custom, val);
}

template<typename T>
T &Matrix<T>::at(Matrix::m_index i)
{
    return _m[i.row][i.col];
}

template<typename T>
T &Matrix<T>::at(size_t row, size_t col)
{
    return _m[row][col];
}

template<typename T>
T Matrix<T>::determinant()
{
    if(_rows != _cols)
    {
        throw std::runtime_error(std::string("Not a square matrix"));
    }else{
        return determinant(_m, _m.size());
    }
}

template<typename T>
T Matrix<T>::determinant(const std::vector<std::vector<T>> m, const size_t n)
{
    T result = 0;

    if(n == 1)
    {
        result = m[0][0];
    }
    else if (n == 2)
    {
        result = m[0][0] * m[1][1] - m[0][1] * m[1][0];
    }else{

        size_t r,c;

        std::vector<std::vector<T>> mt(n, std::vector<T>(n));

        for (size_t k = 0; k < n; k++) {
            r=0;c=0;
            for (size_t i = 1; i < n; i++) {
                c=0;
                for (size_t j = 0; j < n; j++) {
                    if( j==k )
                        continue;

                    mt[r][c] = m[i][j];
                    c++;
                }
                r++;
            }

            result += (k % 2 == 0 ? 1 : -1) * m[0][k] * determinant(mt, n-1);
        }
    }
    return result;

}

template<typename T>
void Matrix<T>::transpose()
{
    std::vector< std::vector< T > > mCopy = _m;

    this->resize(_cols, _rows);

    for (size_t i = 0; i<_rows;i++) {
        for (size_t j = 0; j<_cols;j++) {
            _m[i][j] = mCopy[j][i];
        }
    }
}

template<typename T>
std::vector<T> Matrix<T>::unique()
{
    std::vector<T> r;

    for(Matrix<T>::iterator it = begin(); it != end(); it++)
        if(std::find(r.begin(), r.end(), *it) == r.end())
            r.push_back(*it);

    return r;
}



template<typename T>
T Matrix<T>::sum()
{
    T result = 0;

    for (size_t i = 0; i < _rows; i++) {
        for (size_t j = 0; j < _cols; j++) {
            result += _m[i][j];
        }
    }

    return result;
}

template<typename T>
T Matrix<T>::product()
{
    T result = 1;

    for (size_t i = 0; i < _rows; i++) {
        for (size_t j = 0; j < _cols; j++) {
            result *= _m[i][j];
        }
    }

    return result;
}

template<typename T>
void Matrix<T>::normalize()
{
    T d = determinant();

    for (size_t i = 0; i < _rows; i++) {
        for (size_t j = 0; j < _cols; j++) {
            _m[i][j] /= d;
        }
    }
}

template<typename T>
void Matrix<T>::shuffle()
{
    std::vector< std::vector< T > > mCopy = _m;

    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> rndR(0, static_cast<int>(_rows-1));
    std::uniform_int_distribution<int> rndC(0, static_cast<int>(_cols-1));

    for (size_t i = 0; i < _rows; i++)
        for (size_t j = 0; j < _cols; j++)
            std::swap(_m[i][j], _m[static_cast<size_t>(rndR(rng))][static_cast<size_t>(rndC(rng))]);

}

template<typename T>
std::vector<typename Matrix<T>::m_index> Matrix<T>::find(T num)
{
    std::vector<typename Matrix<T>::m_index> r;

    // iterator begin
    Matrix<T>::iterator it = begin();

    // iterator end
    Matrix<T>::iterator it_e = end();

    for(; it != it_e; it++)
    {
        if(std::abs(*it - num) < static_cast<T>(TOLERANCE))
            r.push_back(it.index());
    }

    return r;
}

template<typename T>
std::vector<typename Matrix<T>::m_index> Matrix<T>::find(T num, iterator b, iterator e)
{
    std::vector<typename Matrix<T>::m_index> r;

    for(; b != e; b++)
    {
        if(std::abs(*b - num) < static_cast<T>(TOLERANCE))
            r.push_back(b.index());
    }

    return r;
}

template<typename T>
void Matrix<T>::inverse()
{

}

template<typename T>
typename Matrix<T>::m_index Matrix<T>::min()
{
    m_index min = {0,0};

    for(Matrix<T>::iterator it = begin(); it != end(); it++)
    {
        if(*it < _m[min.row][min.col])
        {
            min = it.index();
        }

    }

    return min;
}

template<typename T>
typename Matrix<T>::m_index Matrix<T>::max()
{
    m_index max = {0,0};

    for(Matrix<T>::iterator it = begin(); it != end(); it++)
    {
        if(*it > _m[max.row][max.col])
        {
            max = it.index();
        }

    }

    return max;
}

template<typename T>
std::vector<T> &Matrix<T>::operator[](size_t indice)
{
    return _m[indice];
}

template<typename T>
T &Matrix<T>::operator()(size_t row, size_t col)
{
    VALIDATE_SIZE(row, col);

    /*switch (s) {
        case Select::All:

        break;
    default:

        break;
    }*/
    return _m[row][col];
}

template<typename T>
std::vector< std::vector<T> > Matrix<T>::operator()(std::vector<size_t> rows, size_t col, Select sr, Select sc)
{
    std::vector<size_t> cols = {col};

    return select(rows, cols, sr, sc);
}

template<typename T>
std::vector< std::vector<T> > Matrix<T>::operator()(size_t row, std::vector<size_t> cols, Select sr, Select sc)
{
    std::vector<size_t> rows = {row};

    return select(rows, cols, sr, sc);
}

template<typename T>
std::vector< std::vector<T> > Matrix<T>::operator()(std::vector<size_t> rows, std::vector<size_t> cols, Select sr, Select sc)
{
    //VALIDATE_SIZE(row, col);
    return select(rows, cols, sr, sc);
}

template<typename T>
std::vector< std::vector<T> > Matrix<T>::operator()(Select s, size_t col)
{
    return select({}, {col}, s);
}


template<typename T>
std::vector< std::vector<T> > Matrix<T>::operator()(size_t row, Select s)
{
    return select({row}, {}, Select::All, s);
}

template<typename T>
std::vector< std::vector<T> > Matrix<T>::operator()(Select sr, Select sc)
{
    return select({}, {}, sr, sc);
}


template<typename T>
std::vector<std::vector<T> > Matrix<T>::select(std::vector<size_t> rows, std::vector<size_t> cols, Select sr, Select sc)
{
    std::vector<size_t> tRows;
    std::vector<size_t> tCols;

    const size_t r_size = rows.size();
    const size_t c_size = cols.size();

    if(r_size>0){
        if(sr != Select::All){
            if(sr == Select::Odd){
                for(size_t i = 0; i < r_size; i++){
                    if(isOdd(rows[i])){
                        tRows.push_back(rows[i]);
                    }
                }
            }
            if(sr == Select::Even){
                for(size_t i = 0; i < r_size; i++){
                    if(isEven(rows[i])){
                        tRows.push_back(rows[i]);
                    }
                }
            }
        }else
            tRows = rows;

    }else{
        if(sr != Select::All){
            for(size_t i = (sr == Select::Odd) ? 1 : 0; i < _rows; i+=2){
                tRows.push_back(i);
            }
        }else{
            for(size_t i = 0; i < _rows; i++){
                tRows.push_back(i);
            }
        }
    }

    if(c_size>0)
    {
        if(sc != Select::All){
            if(sc == Select::Odd){
                for(size_t i = 0; i < c_size; i++){
                    if(isOdd(cols[i])){
                        tCols.push_back(cols[i]);
                    }
                }
            }

            if(sc == Select::Even){
                for(size_t i = 0; i < c_size; i++){
                    if(isEven(cols[i])){
                        tCols.push_back(cols[i]);
                    }
                }
            }
        }else
            tCols = cols;
    }else{
        if(sc != Select::All){
            for(size_t i = (sc == Select::Odd) ? 1 : 0; i < _cols; i+=2){
                tCols.push_back(i);
            }
        }else{
            for(size_t i = 0; i < _cols; i++){
                tCols.push_back(i);
            }
        }
    }

    return _select(tRows, tCols);
}

template<typename T>
std::vector<std::vector<T> > Matrix<T>::_select(std::vector<size_t> rows, std::vector<size_t> cols)
{
    const size_t r_size = rows.size();
    const size_t c_size = cols.size();

    std::vector<std::vector<T> > result(r_size, std::vector<T>(c_size));

    for(size_t i = 0; i < r_size; i++)
    {
        for(size_t j = 0; j < c_size; j++)
        {
            result[i][j] = _m[rows[i]][cols[j]];
        }
    }

    return result;
}


template<typename T>
bool Matrix<T>::isEven(size_t n)
{
    return n % 2 == 0;
}


template<typename T>
bool Matrix<T>::isOdd(size_t n)
{
    return n % 2 == 1 && n != 0;
}

template<typename T>
Matrix<T> Matrix<T>::operator++(int)
{
    for(Matrix<T>::iterator it = begin(); it != end(); it++)
    {
        (*it)++;
    }
    return *this;
}

template<typename T>
Matrix<T> Matrix<T>::operator--(int)
{
    for(Matrix<T>::iterator it = begin(); it != end(); it++)
    {
        (*it)--;
    }
    return *this;
}

// ******************* //
// **** OPERATORS **** //
// ******************* //

// **** ADDITION **** //
template<typename T>
Matrix<T> Matrix<T>::operator+(Matrix<T> m)
{
    Matrix<T> _mResult(_rows, _cols);

    if(_rows != m.rows() || _cols != m.cols())
    {
        throw std::runtime_error(std::string("Size of matrices must be same for addition"));
    }else{

        for(size_t i=0;i<_rows;i++)
        {
            for(size_t j=0;j<_cols;j++)
            {
                _mResult[i][j] += _m[i][j] + m[i][j];
            }
        }

    }

    return _mResult;
}

template<typename T>
Matrix<T> Matrix<T>::operator+(T number)
{
    Matrix<T> _mResult(*this);

    for(size_t i=0;i<_rows;i++)
    {
        for(size_t j=0;j<_cols;j++)
        {
            _mResult[i][j] = _mResult[i][j] + number;
        }
    }

    return _mResult;
}

template<typename T>
Matrix<T> &Matrix<T>::operator+=(Matrix<T> m)
{
    *this = *this + m;
    return *this;
}

template<typename T>
Matrix<T> &Matrix<T>::operator+=(T number)
{
    *this = *this + number;
    return *this;
}


// **** SUBSTRACTION **** //
template<typename T>
Matrix<T> Matrix<T>::operator-(Matrix<T> m)
{
    Matrix<T> _mResult(_rows, _cols);

    if(_rows != m.rows() || _cols != m.cols())
    {
        throw std::runtime_error(std::string("Size of matrices must be same for addition"));
    }else{

        for(size_t i=0;i<_rows;i++)
        {
            for(size_t j=0;j<_cols;j++)
            {
                _mResult[i][j] = _m[i][j] - m[i][j];
            }
        }

    }
    return _mResult;
}

template<typename T>
Matrix<T> Matrix<T>::operator-(T number)
{
    Matrix<T> _mResult(*this);

    for(size_t i=0;i<_rows;i++)
    {
        for(size_t j=0;j<_cols;j++)
        {
            _mResult[i][j] = _mResult[i][j] - number;
        }
    }

    return _mResult;
}

template<typename T>
Matrix<T> &Matrix<T>::operator-=(Matrix<T> m)
{
    *this = *this - m;
    return *this;
}

template<typename T>
Matrix<T> &Matrix<T>::operator-=(T number)
{
    *this = *this - number;
    return *this;
}

// **** MULTIPLICATION **** //
template<typename T>
Matrix<T> Matrix<T>::operator*(Matrix<T> m)
{
    Matrix<T> _mResult;

    if(_cols != m.rows())
    {
        throw std::runtime_error(std::string("[mxn] - [nxp] type matrices are required for multiplication"));
    }else{

        // *************************************************************** //
        /* 1- matrisin satırını vektör olarak alıp sütunlarla çarpmak
         * 2- matrisin geçici bir kopyasını oluşturup, kendisini resize etmek ve çarpımları tmp matris değerlerinden yapmak
         **/
        // *************************************************************** //

        // resize if isn't identity matrix
        if(_rows != m.rows() || _cols != m.cols())
        {
            _mResult.resize(_rows, m.cols());
        }else{
            _mResult.resize(_rows, _cols);
        }

        for(size_t i=0;i<_rows;i++)
        {
            // TODO: "m.cols()" yerine "const size_t cCols = m.cols();" dene
            for(size_t j=0;j<m.cols();j++)
            {
                // TODO: "m.rows()" yerine "const size_t cRows = m.rows();" dene
                for (size_t k=0;k < m.rows();k++) {
                    _mResult[i][j] += _m[i][k] * m[k][j];
                }
            }
        }

    }

    return _mResult;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(T number)
{
    Matrix<T> _mResult(*this);

    for(size_t i=0;i<_rows;i++)
    {
        for(size_t j=0;j<_cols;j++)
        {
            _mResult[i][j] *= number;
        }
    }

    return _mResult;
}

template<typename T>
Matrix<T> &Matrix<T>::operator*=(Matrix<T> m)
{
    *this = *this * m;
    return *this;
}

template<typename T>
Matrix<T> &Matrix<T>::operator*=(T number)
{
    for(size_t i=0;i<_rows;i++)
    {
        for(size_t j=0;j<_cols;j++)
        {
            _m[i][j] *= number;
        }
    }
    return *this;
}



// **** DIVISION **** //

template<typename T>
Matrix<T> Matrix<T>::operator/(T number)
{
    Matrix<T> _mResult(*this);

    for(size_t i=0;i<_rows;i++)
    {
        for(size_t j=0;j<_cols;j++)
        {
            _mResult[i][j] /= number;
        }
    }

    return _mResult;
}


template<typename T>
Matrix<T> &Matrix<T>::operator/=(T number)
{
    *this = *this / number;
    return *this;
}



template class Matrix<float>;
template class Matrix<double>;
template class Matrix<int>;
}
