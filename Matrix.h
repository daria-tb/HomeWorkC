#pragma once
#include <iostream>

template <typename T>
class Matrix 
{
public:
    Matrix(size_t rows, size_t cols);
    Matrix(size_t rows, size_t cols, T value);
    Matrix(const Matrix& other);
    Matrix(Matrix&& other) noexcept;
    ~Matrix();

    Matrix& operator=(const Matrix& other);
    Matrix& operator=(Matrix&& other) noexcept;

    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const T multiplier) const;
    Matrix operator*(const Matrix& other) const;

    bool operator==(const Matrix& other) const;
    bool operator!=(const Matrix& other) const;

    T GetElement(size_t row, size_t col) const;
    size_t GetRowsCount() const;
    size_t GetColsCount() const;

    void FillByRandom();
    void FillByValue(T value);
    void Print() const;

private:
    size_t rows_, cols_;
    T** data_;
};

// Конструктор
template <typename T>
Matrix<T>::Matrix(size_t rows, size_t cols)
    : rows_(rows), cols_(cols)
{
    data_ = new T*[rows_];
    for (size_t i = 0; i < rows_; ++i) 
	{
        data_[i] = new T[cols_];
    }
}

template <typename T>
Matrix<T>::Matrix(size_t rows, size_t cols, T value)
    : rows_(rows), cols_(cols)
{
    data_ = new T*[rows_];
    for (size_t i = 0; i < rows_; ++i) 
	{
        data_[i] = new T[cols_];
        for (size_t j = 0; j < cols_; ++j) 
		{
            data_[i][j] = value;
        }
    }
}

template <typename T>
Matrix<T>::Matrix(const Matrix& other)
    : rows_(other.rows_), cols_(other.cols_)
{
    data_ = new T*[rows_];
    for (size_t i = 0; i < rows_; ++i) 
	{
        data_[i] = new T[cols_];
        for (size_t j = 0; j < cols_; ++j) 
		{
            data_[i][j] = other.data_[i][j];
        }
    }
}

template <typename T>
Matrix<T>::Matrix(Matrix&& other) noexcept
    : rows_(other.rows_), cols_(other.cols_), data_(other.data_)
{
    other.data_ = nullptr;  // Очищаємо вказівник, щоб не було подвійного звільнення пам'яті
}

template <typename T>
Matrix<T>::~Matrix() 
{
    for (size_t i = 0; i < rows_; ++i) 
	{
        delete[] data_[i];
    }
    delete[] data_;
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix& other) 
{
    if (this == &other) return *this;

    for (size_t i = 0; i < rows_; ++i) 
	{
        delete[] data_[i];
    }
    delete[] data_;

    rows_ = other.rows_;
    cols_ = other.cols_;
    data_ = new T*[rows_];
    for (size_t i = 0; i < rows_; ++i) 
	{
        data_[i] = new T[cols_];
        for (size_t j = 0; j < cols_; ++j) {
            data_[i][j] = other.data_[i][j];
        }
    }

    return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(Matrix&& other) noexcept 
{
    if (this == &other) return *this;

    for (size_t i = 0; i < rows_; ++i) 
	{
        delete[] data_[i];
    }
    delete[] data_;

    rows_ = other.rows_;
    cols_ = other.cols_;
    data_ = other.data_;
    other.data_ = nullptr;

    return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix& other) const 
{
    if (rows_ != other.rows_ || cols_ != other.cols_) 
	{
        throw std::invalid_argument("Matrix dimensions must match");
    }

    Matrix result(rows_, cols_);
    for (size_t i = 0; i < rows_; ++i) 
	{
        for (size_t j = 0; j < cols_; ++j) 
		{
            result.data_[i][j] = data_[i][j] + other.data_[i][j];
        }
    }
    return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix& other) const 
{
    if (rows_ != other.rows_ || cols_ != other.cols_) 
	{
        throw std::invalid_argument("Matrix dimensions must match");
    }

    Matrix result(rows_, cols_);
    for (size_t i = 0; i < rows_; ++i) 
	{
        for (size_t j = 0; j < cols_; ++j) 
		{
            result.data_[i][j] = data_[i][j] - other.data_[i][j];
        }
    }
    return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const T multiplier) const 
{
    Matrix result(rows_, cols_);
    for (size_t i = 0; i < rows_; ++i) 
	{
        for (size_t j = 0; j < cols_; ++j) 
		{
            result.data_[i][j] = data_[i][j] * multiplier;
        }
    }
    return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix& other) const 
{
    if (cols_ != other.rows_) 
	{
        throw std::invalid_argument("Matrix dimensions must match for multiplication");
    }

    Matrix result(rows_, other.cols_);
    for (size_t i = 0; i < rows_; ++i) 
	{
        for (size_t j = 0; j < other.cols_; ++j) 
		{
            result.data_[i][j] = 0;
            for (size_t k = 0; k < cols_; ++k) 
			{
                result.data_[i][j] += data_[i][k] * other.data_[k][j];
            }
        }
    }
    return result;
}

template <typename T>
bool Matrix<T>::operator==(const Matrix& other) const 
{
    if (rows_ != other.rows_ || cols_ != other.cols_) 
	{
        return false;
    }

    for (size_t i = 0; i < rows_; ++i) 
	{
        for (size_t j = 0; j < cols_; ++j) 
		{
            if (data_[i][j] != other.data_[i][j]) 
			{
                return false;
            }
        }
    }
    return true;
}

template <typename T>
bool Matrix<T>::operator!=(const Matrix& other) const 
{
    return !(*this == other);
}

template <typename T>
T Matrix<T>::GetElement(size_t row, size_t col) const 
{
    if (row >= rows_ || col >= cols_) 
	{
        std::cerr << "Index out of range" << std::endl;
        return T();
    }
    return data_[row][col];
}

template <typename T>
size_t Matrix<T>::GetRowsCount() const 
{
    return rows_;
}

template <typename T>
size_t Matrix<T>::GetColsCount() const 
{
    return cols_;
}

template <typename T>
void Matrix<T>::FillByRandom() 
{
    for (size_t i = 0; i < rows_; ++i) 
	{
        for (size_t j = 0; j < cols_; ++j) 
		{
            data_[i][j] = rand() % 100 + 1; // Генерація випадкового числа від 1 до 100
        }
    }
}

template <typename T>
void Matrix<T>::FillByValue(T value) 
{
    for (size_t i = 0; i < rows_; ++i) 
	{
        for (size_t j = 0; j < cols_; ++j) 
		{
            data_[i][j] = value;
        }
    }
}

template <typename T>
void Matrix<T>::Print() const 
{
    for (size_t i = 0; i < rows_; ++i) 
	{
        for (size_t j = 0; j < cols_; ++j) 
		{
            std::cout << data_[i][j] << " ";
        }
        std::cout << "\n";
    }
}
