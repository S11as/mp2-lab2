//
// Created by Kirill on 10/15/2020.
//

#ifndef MATRIXLIB_SMATRIX_H
#define MATRIXLIB_SMATRIX_H

#include "MyVector.h"

template<class T>
class SMatrix : public Vector<Vector<T>> {
protected:
    int lower_bandwidth = 0;
    int upper_bandwidth = 0;
public:
    SMatrix(int size = 0, int lower_bandwidth = 0, int upper_bandwidth = 0);
    SMatrix(const SMatrix<T> &matrix);
    SMatrix(const Vector<Vector<T>> &vector);

    ~SMatrix();

    // перегрузка для корректной индексации
    // ленточная матрица хранится/индексируется
    // 1 1 0 0   ->   1 1 0 0
    // 1 1 1 0   ->   1 1 1 0
    // 1 1 1 0   ->   0 1 1 1
    // 1 1 0 0   ->   0 0 1 1
    T &operator()(int row, int col) const;
    SMatrix<T> &operator=(const SMatrix<T> &matrix);
    SMatrix<T> operator+(const SMatrix<T> &matrix);

    template<class T1>
    friend istream &operator>>(istream &istr, const SMatrix &matrix);

    template<class T1>
    friend ostream &operator<<(ostream &ostr, const SMatrix &matrix);
};

template<class T>
SMatrix<T>::SMatrix(int size, int lower_bandwidth, int upper_bandwidth) : Vector<Vector<T>>(size, Vector<T>()) {
    int max_bandwidth = size - 1;
    if(lower_bandwidth > max_bandwidth || upper_bandwidth > max_bandwidth)
        throw out_of_range("bandwith out of range");
    this->lower_bandwidth = lower_bandwidth;
    this->upper_bandwidth = upper_bandwidth;

    int upper_span = upper_bandwidth;
    int lower_span = 0;
    int span = lower_span + upper_span + 1;
    this->x[0] = Vector<T>(span, 0);

    for (int i = 1; i < size; ++i) {
        if(lower_span < lower_bandwidth)
            lower_span++;
        if(upper_span > (size-1)-i)
            upper_span--;
        span = lower_span + upper_span + 1;
        this->x[i] = Vector<T>(span, 0);
    }
}

template<class T>
SMatrix<T>::SMatrix(const Vector<Vector<T>> &vector):Vector<Vector<T>>(vector) {
    // матрица, когда возможны верхние и нижние диагонали, иначе - дефолтные нули
    // 1 1 0
    // 1 1 0
    // 1 0 0
    if(vector.length>=3){
        this->upper_bandwidth = vector.x[0].length-1;
        this->upper_bandwidth = vector.x[vector.length-1].length-1;
    }
}

template<class T>
SMatrix<T>::~SMatrix() = default;

template<class T>
SMatrix<T>::SMatrix(const SMatrix<T> &matrix): Vector<Vector<T>>(matrix) {
    if(matrix.length>=3){
        this->upper_bandwidth = matrix.x[0].length-1;
        this->upper_bandwidth = matrix.x[matrix.length-1].length-1;
    }
}

template<class T>
SMatrix<T> &SMatrix<T>::operator=(const SMatrix<T> &matrix) {
    if (this != &matrix) {
        if (this->length != matrix.length) {
            delete[] this->x;
            SMatrix<T>(matrix.length, matrix.lower_bandwidth, matrix.upper_bandwidth);
        }
        for (int i = 0; i < this->length; ++i) {
            this->x[i] = matrix.x[i];
        }
    }
    return *this;
}

template<class T>
T &SMatrix<T>::operator()(int row, int col) const {
    if(row<0 || row >= this->length)
        throw out_of_range("row out of range");

    // проверяем, лежит ли запрашиваемый элемент выше заданных диагоналей
    int upper_shift = (this->length-1)-row-this->upper_bandwidth;
    if(col+upper_shift >= this->length)
        throw out_of_range("col out of range");

    // вычисляем, если это необходимо, сдвиг хранения
    int lower_shift = row - this->lower_bandwidth;
    if(lower_shift > 0)
        col -= lower_shift;

    //запрашиваемый элемент ниже заданных диагоналей
    if(col < 0)
        throw out_of_range("col out of range");

    return this->x[row][col];
}

template<class T>
SMatrix<T> SMatrix<T>::operator+(const SMatrix<T> &matrix) {
    return Vector<Vector<T>>::operator+(matrix);
}


template<class T1>
istream &operator>>(istream &istr, const SMatrix<T1> &matrix) {
    for (int i = 0; i < matrix.length; ++i) {
        istr >> matrix.x[i];
    }
    return istr;
}

template<class T1>
ostream &operator<<(ostream &ostr, const SMatrix<T1> &matrix) {
    for (int i = 0; i < matrix.length; ++i) {
        ostr << matrix.x[i];
        ostr << "\n";
    }
    return ostr;
}

#endif //MATRIXLIB_SMATRIX_H
