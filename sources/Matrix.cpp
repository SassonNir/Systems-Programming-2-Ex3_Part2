#include "Matrix.hpp"

namespace zich {
// Constructors
Matrix::Matrix(std::vector<double> values, int rows, int columns) : data(std::move(values)), rows(size_t(rows)), cols(size_t(columns)) {
    if (rows < 1 || columns < 1) {
        throw std::invalid_argument("Matrix dimensions must be greater than 0");
    }
    if (rows * columns != data.size()) {
        throw std::invalid_argument("Matrix::Matrix(std::vector<double> values, int rows, int columns): rows * columns != values.size()");
    }
}
Matrix::Matrix(std::vector<double> values, size_t rows, size_t columns) : data(std::move(values)), rows(rows), cols(columns) {
    if (rows < 1 || columns < 1) {
        throw std::invalid_argument("Matrix dimensions must be greater than 0");
    }
    if (rows * columns != data.size()) {
        throw std::invalid_argument("Matrix::Matrix(std::vector<double> values, size_t rows, size_t columns): rows * columns != values.size()");
    }
}

// Addition - c = this + other
Matrix Matrix::operator+(const Matrix& other) const {
    if (this->rows != other.rows || this->cols != other.cols) {
        throw std::invalid_argument("Matrix::operator+(const Matrix& other): this->rows != other.rows || this->cols != other.cols");
    }
    std::vector<double> values(this->rows * this->cols, 0);
    for (size_t i = 0; i < this->rows * this->cols; i++) {
        values.at(i) = this->data.at(i) + other.data.at(i);
    }
    return Matrix(values, this->rows, this->cols);
}

// Addition - this = this + other
Matrix& Matrix::operator+=(const Matrix& other) {
    if (this->rows != other.rows || this->cols != other.cols) {
        throw std::invalid_argument("Matrix::operator+=(const Matrix& other): this->rows != other.rows || this->cols != other.cols");
    }
    for (size_t i = 0; i < this->rows * this->cols; i++) {
        this->data.at(i) += other.data.at(i);
    }
    return *this;
}

// Addition - c = +this
Matrix Matrix::operator+() const {
    std::vector<double> values(this->rows * this->cols, 0);
    for (size_t i = 0; i < this->rows * this->cols; i++) {
        values.at(i) = +this->data.at(i);
    }
    return Matrix(values, this->rows, this->cols);
}

// Subtraction - c = this - other
Matrix Matrix::operator-(const Matrix& other) const {
    if (this->rows != other.rows || this->cols != other.cols) {
        throw std::invalid_argument("Matrix::operator-(const Matrix& other): this->rows != other.rows || this->cols != other.cols");
    }
    std::vector<double> values(this->rows * this->cols, 0);
    for (size_t i = 0; i < this->rows * this->cols; i++) {
        values.at(i) = this->data.at(i) - other.data.at(i);
    }
    return Matrix(values, this->rows, this->cols);
}

// Subtraction - this = this - other
Matrix& Matrix::operator-=(const Matrix& other) {
    if (this->rows != other.rows || this->cols != other.cols) {
        throw std::invalid_argument("Matrix::operator-=(const Matrix& other): this->rows != other.rows || this->cols != other.cols");
    }
    for (size_t i = 0; i < this->rows * this->cols; i++) {
        this->data.at(i) -= other.data.at(i);
    }
    return *this;
}

// Subtraction - c = -this
Matrix Matrix::operator-() const {
    std::vector<double> values(this->rows * this->cols, 0);
    for (size_t i = 0; i < this->rows * this->cols; i++) {
        values.at(i) = -this->data.at(i);
    }
    return Matrix(values, this->rows, this->cols);
}

// Multiplication - c = this * other
Matrix Matrix::operator*(const Matrix& other) const {
    if (this->cols != other.rows) {
        throw std::invalid_argument("Matrix::operator*(const Matrix& other): this->cols != other.rows");
    }
    std::vector<double> values(this->rows * other.cols, 0);
    for (size_t i = 0; i < this->rows; i++) {
        for (size_t j = 0; j < other.cols; j++) {
            for (size_t k = 0; k < this->cols; k++) {
                values.at(i * other.cols + j) += this->data.at(i * this->cols + k) * other.data.at(k * other.cols + j);
            }
        }
    }
    return Matrix(values, this->rows, other.cols);
}

// Multiplication - this = this * other
Matrix& Matrix::operator*=(const Matrix& other) {
    *this = (*this) * other;
    return (*this);
}

// Multiplication - c = this * scalar
Matrix Matrix::operator*(double scalar) const {
    std::vector<double> values(this->rows * this->cols, 0);
    for (size_t i = 0; i < this->rows * this->cols; i++) {
        values.at(i) = this->data.at(i) * scalar;
    }
    return Matrix(values, this->rows, this->cols);
}

// Multiplication - this = this * scalar
Matrix& Matrix::operator*=(double scalar) {
    for (size_t i = 0; i < this->rows * this->cols; i++) {
        this->data.at(i) *= scalar;
    }
    return *this;
}

// Multiplication - c = scalar * this
Matrix operator*(double scalar, const Matrix& other) {
    return other * scalar;
}

// Increment - this = this + 1 (prefix ++this)
Matrix& Matrix::operator++() {
    for (size_t i = 0; i < this->rows * this->cols; i++) {
        this->data.at(i) += 1;
    }

    return *this;
}

// Increment - this = this + 1 (postfix this++)
Matrix Matrix::operator++(int) {
    Matrix copy{this->data, this->rows, this->cols};
    ++(*this);
    return copy;
}

// Decrement - this = this - 1 (prefix --this)
Matrix& Matrix::operator--() {
    for (size_t i = 0; i < this->rows * this->cols; i++) {
        this->data.at(i) -= 1;
    }
    return *this;
}

// Decrement - this = this - 1 (postfix this--)
Matrix Matrix::operator--(int) {
    Matrix copy{this->data, this->rows, this->cols};
    --(*this);
    return copy;
}

// Comparison - this == other
bool Matrix::operator==(const Matrix& other) const {
    if (this->rows != other.rows || this->cols != other.cols) {
        throw std::invalid_argument("Matrix::operator==(const Matrix& other): this->rows != other.rows || this->cols != other.cols");
    }
    for (size_t i = 0; i < this->rows * this->cols; i++) {
        if (this->data.at(i) != other.data.at(i)) {
            return false;
        }
    }
    return true;
}

// Comparison - this != other
bool Matrix::operator!=(const Matrix& other) const {
    return !(*this == other);
}

// Comparison - this < other
bool Matrix::operator<(const Matrix& other) const {
    if (this->rows != other.rows || this->cols != other.cols) {
        throw std::invalid_argument("Matrix::operator<(const Matrix& other): this->rows != other.rows || this->cols != other.cols");
    }
    double sum1 = 0;
    double sum2 = 0;
    for (size_t i = 0; i < this->rows * this->cols; i++) {
        sum1 += this->data.at(i);
        sum2 += other.data.at(i);
    }
    return sum1 < sum2;
}

// Comparison - this > other
bool Matrix::operator>(const Matrix& other) const {
    return other < *this;
}

// Comparison - this <= other
bool Matrix::operator<=(const Matrix& other) const {
    return !(*this > other);
}

// Comparison - this >= other
bool Matrix::operator>=(const Matrix& other) const {
    return !(*this < other);
}

// Output - cout << this
std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
    for (size_t i = 0; i < matrix.rows; i++) {
        os << "[";
        for (size_t j = 0; j < matrix.cols; j++) {
            os << matrix.data.at(i * matrix.cols + j);
            if (j != matrix.cols - 1) {
                os << " ";
            }
        }
        os << "]";
        if (i != matrix.rows - 1) {
            os << "\n";
        }
    }
    return os;
}

// Helper function for >> operator
void rows_cols_amt(std::string str_mat, int& row, int& col){
    int row_num = 0;
    int col_num = 0;
    int open_bracket = 0;
    int close_bracket = 0;

    unsigned long int i = 0;
    while(i < str_mat.length()){
        if(str_mat[i] == ','){
            row_num++;
        }
        //check if after evry comma ther is a space
        if(i + 1 < str_mat.length() && str_mat[i] == ','){
            if(str_mat[i+1] != ' '){
                throw std::invalid_argument("Invalid matrix");
            }
        }
        i++;
    }
    row_num++;
    i = 0;
    while(i < str_mat.length()){
        if(str_mat[i] == '['){
            open_bracket++;
        }
        else if(str_mat[i] == ']'){
            break;
        }
        if (open_bracket == 1){
            if(str_mat[i] == ' '){
                col_num++;
            }
        }
        
        i++;
    }
    col_num++;
    row = row_num;
    col = col_num;
}

// Input - cin >> this
std::istream& operator>>(std::istream& is, Matrix& matrix) {
    std::string inpt;
    std::getline(is, inpt);
    int row = 0;
    int col = 0;
    rows_cols_amt(inpt, row, col);
    std::istringstream str_input{inpt};
    // temp vecttor
    std::vector<double> temp_vector;
    // strip_whitespace(line);
    char dummy = ' ';
    for (size_t i = 0; i < row; i++) {
        str_input >> dummy;

        // check if dummy is [
        if (dummy != '[') {
            throw std::invalid_argument("Matrix not opend error");
        }

        for (size_t j = 0; j < col; j++) {
            double temp = 0;
            str_input >> temp;
            temp_vector.push_back(temp);
        }

        str_input >> dummy;
        // check if dummy is ]
        if (dummy != ']') {
            throw std::invalid_argument("Matrix not closed properly");
        }
        if (i < row - 1) {
            str_input >> dummy;
            // check if dummy is , (seperator)
            if (dummy != ',') {
                throw std::invalid_argument("Matrix not spaced properly");
            }
        }
    }
    matrix.data = temp_vector;
    matrix.cols = size_t(col);
    matrix.rows = size_t(row);

    return is;
}

}  // namespace zich
