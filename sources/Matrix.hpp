#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace zich {
class Matrix {
   private:
    size_t rows, cols;
    std::vector<double> data;

   public:
    Matrix(std::vector<double> values, int rows, int columns);
    Matrix(std::vector<double> values, size_t rows, size_t columns);

    // Addition
    Matrix operator+(const Matrix& other) const;  // c = this + other
    Matrix& operator+=(const Matrix& other);      // this = this + other
    Matrix operator+() const;                     // c = +this

    // Subtraction
    Matrix operator-(const Matrix& other) const;  // c = this - other
    Matrix& operator-=(const Matrix& other);      // this = this - other
    Matrix operator-() const;                     // c = -this

    // Comparison operators
    bool operator>(const Matrix& other) const;   // this > other
    bool operator>=(const Matrix& other) const;  // this >= other
    bool operator<(const Matrix& other) const;   // this < other
    bool operator<=(const Matrix& other) const;  // this <= other
    bool operator==(const Matrix& other) const;  // this == other
    bool operator!=(const Matrix& other) const;  // this != other

    // Increment and decrement operators (prefix and postfix)
    Matrix& operator++();    // prefix increment (++this)
    Matrix operator++(int);  // postfix increment (this++)
    Matrix& operator--();    // prefix decrement (--this)
    Matrix operator--(int);  // postfix decrement (this--)

    // Multiplication
    Matrix operator*(const Matrix& other) const;                  // c = this * other
    Matrix& operator*=(const Matrix& other);                      // this = this * other
    Matrix operator*(double scalar) const;                        // c = this * scalar
    Matrix& operator*=(double scalar);                            // this = this * scalar
    friend Matrix operator*(double scalar, const Matrix& other);  // c = scalar * other

    // Input and output
    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
    friend std::istream& operator>>(std::istream& is, Matrix& matrix);
};

}  // namespace zich