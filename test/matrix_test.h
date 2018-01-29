#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <pigon/matrix.h>
#include <chrono>

using namespace testing;
using namespace Pigon;

size_t ROW = 2;
size_t COL = 3;

TEST(OPERATOR, ADDITION)
{
    Matrixf mat1(2, 2, MatrixType::Custom, 5);
    Matrixf mat2(2, 2, MatrixType::Custom, 3);

    // + NUMBER
    mat1 = mat1 + 3;

    for (size_t i=0;i<mat1.rows();i++) {
        for (size_t j=0;j<mat1.cols();j++) {
            EXPECT_EQ(mat1[i][j], 8);
        }
    }

    // += NUMBER
    mat1 += 2;

    for (size_t i=0;i<mat1.rows();i++) {
        for (size_t j=0;j<mat1.cols();j++) {
            EXPECT_EQ(mat1[i][j], 10);
        }
    }

    // + MATRIX
    mat1 = mat1 + mat2;

    std::cout << mat1 << std::endl;

    for (size_t i=0;i<mat1.rows();i++) {
        for (size_t j=0;j<mat1.cols();j++) {
            EXPECT_EQ(mat1[i][j], 13);
        }
    }

    // += MATRIX
    mat1 += mat2;

    for (size_t i=0;i<mat1.rows();i++) {
        for (size_t j=0;j<mat1.cols();j++) {
            EXPECT_EQ(mat1[i][j], 16);
        }
    }
}

TEST(OPERATOR, SUBSTRACTION)
{
    Matrixf mat1(2, 2, MatrixType::Custom, 16);
    Matrixf mat2(2, 2, MatrixType::Custom, 3);

    // - NUMBER
    mat1 = mat1 - 3;

    for (size_t i=0;i<mat1.rows();i++) {
        for (size_t j=0;j<mat1.cols();j++) {
            EXPECT_EQ(mat1[i][j], 13);
        }
    }

    // -= NUMBER
    mat1 -= 2;

    for (size_t i=0;i<mat1.rows();i++) {
        for (size_t j=0;j<mat1.cols();j++) {
            EXPECT_EQ(mat1[i][j], 11);
        }
    }

    // - MATRIX
    mat1 = mat1 - mat2;

    for (size_t i=0;i<mat1.rows();i++) {
        for (size_t j=0;j<mat1.cols();j++) {
            EXPECT_EQ(mat1[i][j], 8);
        }
    }

    // -= MATRIX
    mat1 -= mat2;

    for (size_t i=0;i<mat1.rows();i++) {
        for (size_t j=0;j<mat1.cols();j++) {
            EXPECT_EQ(mat1[i][j], 5);
        }
    }
}

TEST(OPERATOR, MULTIPLICATION)
{
    Matrixf mat1(3, 2, MatrixType::Custom, 1);
    Matrixf mat2(2, 2, MatrixType::Custom, 5);
    Matrixf mat3(3, 2, MatrixType::Custom, 2);

    Matrixd ms = {{2, 4, 1, 7},
                  {3, 6, 2, 4},
                  {3, 9, 5, 2},
                  {2, 1, 4, 0}};


    Matrixd ms2 = {{1, 5, 4, 3},
                   {4, 7, 2, 1},
                   {3, 2, 1, 2},
                   {2, 9, 8, 1}};

    Matrixd ms_data = {{35, 103, 73, 19},
                       {41,  97, 58, 23},
                       {58, 106, 51, 30},
                       {18,  25, 14, 15}};

    Matrixd ms_data2 = {{704, 1213, 571, 373},
                        {649, 1207, 600, 359},
                        {695, 1404, 735, 412},
                        {190, 428, 256, 122}};



    Matrixf mat1_data(3, 2);
    Matrixf mat3_data(3, 2);

    mat1[0][0] = 1;
    mat1[0][1] = 4;

    mat1[1][0] = 3;
    mat1[1][1] = 5;

    mat1[2][0] = 6;
    mat1[2][1] = 7;

    mat2[0][0] = 2;
    mat2[0][1] = 4;

    mat2[1][0] = 3;
    mat2[1][1] = 6;

    // * NUMBER
    mat1 = mat1 * 5;


    mat1_data[0][0] = 5;mat1_data[0][1] = 20;
    mat1_data[1][0] = 15;mat1_data[1][1] = 25;
    mat1_data[2][0] = 30;mat1_data[2][1] = 35;

    for (size_t i=0;i<mat1.rows();i++) {
        for (size_t j=0;j<mat1.cols();j++) {
            EXPECT_EQ(mat1[i][j], mat1_data[i][j]);
        }
    }

    mat1_data[0][0] = -10;mat1_data[0][1] = -40;
    mat1_data[1][0] = -30;mat1_data[1][1] = -50;
    mat1_data[2][0] = -60;mat1_data[2][1] = -70;

    // *= NUMBER
    mat1 *= -2;

    for (size_t i=0;i<mat1.rows();i++) {
        for (size_t j=0;j<mat1.cols();j++) {
            EXPECT_EQ(mat1[i][j], mat1_data[i][j]);
        }
    }

    // * MATRIX
    mat3 = mat1 * mat2;


    mat3_data[0][0] = -140;mat3_data[0][1] = -280;
    mat3_data[1][0] = -210;mat3_data[1][1] = -420;
    mat3_data[2][0] = -330;mat3_data[2][1] = -660;

    for (size_t i=0;i<mat3.rows();i++) {
        for (size_t j=0;j<mat3.cols();j++) {
            EXPECT_EQ(mat3[i][j], mat3_data[i][j]);
        }
    }

    // *= MATRIX
    mat1 *= mat2;

    for (size_t i=0;i<mat1.rows();i++) {
        for (size_t j=0;j<mat1.cols();j++) {
            EXPECT_EQ(mat1[i][j], mat3_data[i][j]);
        }
    }

    ms *= ms2;
    for (size_t i=0;i<ms.rows();i++) {
        for (size_t j=0;j<ms.cols();j++) {
            EXPECT_EQ(ms[i][j], ms_data[i][j]);
        }
    }

    ms *= ms2;
    for (size_t i=0;i<ms.rows();i++) {
        for (size_t j=0;j<ms.cols();j++) {
            EXPECT_EQ(ms[i][j], ms_data2[i][j]);
        }
    }
}

TEST(OPERATOR, DIVISION)
{
    Matrixf mat1(2, 2, MatrixType::Custom, 12);
    Matrixf mat2(2, 2);

    // / NUMBER
    mat2 = mat1 / 3;

    for (size_t i=0;i<mat2.rows();i++) {
        for (size_t j=0;j<mat2.cols();j++) {
            EXPECT_EQ(mat2[i][j], 4);
        }
    }

    // /= NUMBER
    mat2 /= 4;

    for (size_t i=0;i<mat2.rows();i++) {
        for (size_t j=0;j<mat2.cols();j++) {
            EXPECT_EQ(mat2[i][j], 1);
        }
    }
}

TEST(OPERATOR, INCREMENT)
{
    Matrixf m(3,2, MatrixType::Custom, 1.0f);

    std::cout << "Original: \n" << m << std::endl;

    m++;

    for(Matrix<float>::iterator i = m.begin(); i != m.end(); i++)    {
       EXPECT_TRUE(*i == 2.0f);
    }

    std::cout << "\nIncreased: \n" << m << std::endl;
}

TEST(OPERATOR, DECREMENT)
{
    Matrixf m(3,3, MatrixType::Custom, 2.0f);

    std::cout << "Original: \n" << m << std::endl;

    m--;

    for(Matrix<float>::iterator i = m.begin(); i != m.end(); i++)    {
       EXPECT_TRUE(*i == 1.0f);
    }

    std::cout << "\nDecreased: \n" << m << std::endl;
}

TEST(COMMON, ALL)
{

    Matrixf m2 = { {3, 5},
                   {7, 8} };

    for(Matrix<float>::iterator i = m2.begin(); i != m2.end(); i++)
    {
        std::cout << *i << std::endl;  // prints d.
    }

    Matrixf m(5, 5, MatrixType::Custom, 12);
    EXPECT_EQ(12, m[2][4]);

    m[2][4] = 23;

    EXPECT_EQ(23, m[2][4]);

    Matrixf m3(2,3);
    //std::cout << m3(0,2) << std::endl;

    m3.at(0,0) = 15;
    std::cout << m3 << std::endl;


    for(Matrix<float>::iterator i = m.begin(); i != m.begin() + 5; i++)
    {
        std::cout << *i << std::endl;  // prints d.
    }

}

TEST(COMMON, SELECT)
{
    Matrixf m = {{2,4,5},
                 {3,2,1},
                 {7,8,6}};

    std::cout << m << std::endl;

    std::vector< std::vector<float> > m1;
    /**/
    m1 = m({0,2}, 1);

    EXPECT_EQ(m1[0][0], 4);
    EXPECT_EQ(m1[1][0], 8);

    m1 = m(1, {0,1});

    EXPECT_EQ(m1[0][0], 3);
    EXPECT_EQ(m1[0][1], 2);

    m1 = m({1,2}, {0,1});

    EXPECT_EQ(m1[0][0], 3);
    EXPECT_EQ(m1[0][1], 2);
    EXPECT_EQ(m1[1][0], 7);
    EXPECT_EQ(m1[1][1], 8);

    m1 = m(Select::All,1);

    EXPECT_EQ(m1[0][0], 4);
    EXPECT_EQ(m1[1][0], 2);
    EXPECT_EQ(m1[2][0], 8);

    m1 = m(1, Select::All);

    EXPECT_EQ(m1[0][0], 3);
    EXPECT_EQ(m1[0][1], 2);
    EXPECT_EQ(m1[0][2], 1);

    m1 = m(Select::Even, Select::Odd);

    EXPECT_EQ(m1[0][0], 4);
    EXPECT_EQ(m1[1][0], 8);

    m1 = m({0,1}, {1,2}, Select::Even, Select::Odd);

    EXPECT_EQ(m1[0][0], 4);
}

TEST(INIT, INIT_TYPE)
{

    Matrixf b(3,3);

    EXPECT_EQ(1, 1);

}

TEST(FUNCTIONS, RESIZE)
{
    Matrixf mat(ROW,COL);

    std::cout << "Original: \n" << mat << std::endl;

    const size_t rows = 5;
    const size_t cols = 10;

    EXPECT_EQ(mat.rows(), ROW);
    EXPECT_EQ(mat.cols(), COL);

    mat.resize(rows, cols);

    EXPECT_EQ(mat.rows(), rows);
    EXPECT_EQ(mat.cols(), cols);

    std::cout << "\nResized: \n" << mat << std::endl;
}

TEST(FUNCTIONS, TRANSPOSE)
{
    Matrixf pm(2,2);

    pm[0][0] = 3;
    pm[0][1] = 5;
    pm[1][0] = 7;
    pm[1][1] = 8;

    std::cout << "Original: \n" << pm << std::endl;

    pm.transpose();

    std::cout << "\nTransposed: \n" << pm << std::endl;
}

TEST(FUNCTIONS, FILL)
{
    Matrixf m(10,10);

    m.fill(32);

    for (size_t i=0;i<m.rows();i++) {
        for (size_t j=0;j<m.cols();j++) {
            EXPECT_EQ(m[i][j], 32);
        }
    }

}

TEST(FUNCTIONS, SUM)
{
    Matrixf m1 = { {3, 5},
                   {6, 7} };

    EXPECT_EQ(m1.sum(), 21);
}

TEST(FUNCTIONS, PRODUCT)
{
    Matrixf m1 = { {3, 5},
                   {6, 7} };

    EXPECT_EQ(m1.product(), 630);
}

TEST(FUNCTIONS, SHUFFLE)
{
    Matrixf mat1(3, 2);

    mat1[0][0] = 1;
    mat1[0][1] = 4;

    mat1[1][0] = 3;
    mat1[1][1] = 5;

    mat1[2][0] = 6;
    mat1[2][1] = 7;

    std::cout << "Original: \n" << mat1 << std::endl;

    mat1.shuffle();

    std::cout << "\nShuffled: \n" << mat1 << std::endl;
}

TEST(FUNCTIONS, NORMALIZE)
{
    Matrixf m1 = { {3, 5},
                   {6, 7} };

    m1.normalize();

    //EXPECT_EQ(m1.normalize(), 630);
}

TEST(FUNCTIONS, UNIQUE)
{
    Matrixf m1 = { {2, 5},
                   {6, 7},
                   {2, 1},
                   {7, 7} };
    std::vector<float> res = {2,5,6,7,1};

    EXPECT_EQ(m1.unique(), res);
}

TEST(FUNCTIONS, FIND)
{
    Matrixf m = { {2, 6, 8},
                   {6, 7, 3},
                   {2, 1, 4} };


    std::vector<Matrixf::m_index> r = m.find(2);

    std::vector<Matrixf::m_index> r_data = {Matrixf::m_index{0,0}, Matrixf::m_index{2, 0}};

    std::vector<Matrixf::m_index>::iterator i = r.begin();

    std::vector<Matrixf::m_index>::iterator r_data_i = r_data.begin();

    for(; r_data_i != r_data.end(); r_data_i++)    {
        EXPECT_EQ((*i++).row, (*r_data_i).row);
    }


    std::vector<Matrixf::m_index> r_data_1 = {Matrixf::m_index{0,0}};

    r = m.find(2, m.begin(), m.begin() + 6);
    i = r.begin();
    r_data_i = r_data_1.begin();

    for(; i != r.end(); i++)    {
        EXPECT_EQ((*i).row, (*r_data_i++).row);
    }
}

TEST(FUNCTIONS, MIN)
{
    Matrixf m1 = { {3, 5},
                   {6, 7} };

    EXPECT_EQ(3, m1.at(m1.min()));
}

TEST(FUNCTIONS, MAX)
{
    Matrixf m1 = { {3, 5},
                   {6, 7} };

    EXPECT_EQ(7, m1.at(m1.max()));
}

TEST(FUNCTIONS, INVERSE)
{
    Matrixf m = {{2, 5, 1, 2},
                 {2, 3, 4, 9},
                 {6, 9, 1, 7},
                 {3, 5, 7, 8}};

    Matrixf m_data = {{-0.822951, -0.413115,  0.432787, 0.291803 },
                      { 0.527869,  0.101639, -0.154098, -0.111475 },
                      {-0.065574, -0.180328, -0.049180, 0.262295 },
                      { 0.036066,  0.249180, -0.022951, -0.144262 }};

    Matrixf::iterator i_data = m_data.begin();

    m.inverse();

    std::cout << m << std::endl;

    /*for(Matrix<float>::iterator i = m.begin(); i != m.end(); i++)    {
       EXPECT_EQ(*i, *i_data);
       i_data++;
    }*/
}

TEST(GETTER, COMMON)
{

    // matrix size
    Matrixf ms(ROW,COL);

    EXPECT_EQ(ms.rows(), ROW);
    EXPECT_EQ(ms.cols(), COL);
}

TEST(PERFORMANCE, TRANSPOSE)
{
    Matrixf pm(1000,1000);

    auto start = std::chrono::steady_clock::now();

    pm.transpose();

    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast <std::chrono::milliseconds> (end - start);

    EXPECT_GT(50, time.count());
}

TEST(PERFORMANCE, RESIZE)
{
    Matrix<int> m1 = { {3, 4},
                       {1, 5} };
    Matrix<int> m2 = { {1, 3},
                       {5, 6} };

    std::cout << "m1:\n" << m1 << std::endl;

    m1 = m1 + 3;

    std::cout << "m1+3:\n" << m1 << std::endl;


    std::cout << "\nm2:\n" << m2 << std::endl;

    m1 = m1 + m2;

    std::cout << "\nm1 + m2:\n" << m1 << std::endl;

    m1 += m2;

    std::cout << "\nm1 + m2:\n" << m1 << std::endl;
}

TEST(PERFORMANCE, INITIALIZE)
{

    auto start = std::chrono::steady_clock::now();

    Matrixf m1(3000,3000);

    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast <std::chrono::milliseconds> (end - start);

    EXPECT_GT(100, time.count());


    start = std::chrono::steady_clock::now();

    Matrixf m2(3000,3000,MatrixType::Unit);

    end = std::chrono::steady_clock::now();
    time = std::chrono::duration_cast <std::chrono::milliseconds> (end - start);

    EXPECT_GT(100, time.count());

    start = std::chrono::steady_clock::now();

    Matrixf m3(3000,3000,MatrixType::Custom, 1);

    end = std::chrono::steady_clock::now();
    time = std::chrono::duration_cast <std::chrono::milliseconds> (end - start);

    EXPECT_GT(100, time.count());

}

TEST(PERFORMANCE, DETERMINANT)
{
    Matrixf m1 = { {3, 5},
                   {6, 7} };

    Matrixf m2 = { {3, 2, 1},
                   {1, 4, 9},
                   {4, 2, 5} };

    Matrixf m3 = { {1, 3, 2, 4},
                   {2, 8, 1, 5},
                   {3, 7, 7, 4},
                   {5, 9, 6, 12},};

    float m1_data = -9;
    float m2_data = 54;
    float m3_data = -218;

    EXPECT_EQ(m1.determinant(), m1_data);
    EXPECT_EQ(m2.determinant(), m2_data);
    EXPECT_EQ(m3.determinant(), m3_data);
}

TEST(PERFORMANCE, MULTIPLY)
{

}

TEST(PERFORMANCE, SUM)
{

}
