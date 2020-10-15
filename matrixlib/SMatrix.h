//
// Created by Kirill on 10/15/2020.
//

#ifndef MATRIXLIB_SMATRIX_H
#define MATRIXLIB_SMATRIX_H

#include "MyVector.h"

template<class T>
class SMatrix : public Vector<Vector<T>> {
public:
    SMatrix(int size = 0);

    SMatrix(const SMatrix<T> &matrix);

    SMatrix(const Vector<Vector<T>> &vector);

    ~SMatrix();

    SMatrix<T> &operator=(const SMatrix<T> &matrix);

    SMatrix<T> operator+(const SMatrix<T> &matrix);

    template<class T1>
    friend istream &operator>>(istream &istr, const SMatrix &matrix);

    template<class T1>
    friend ostream &operator<<(ostream &ostr, const SMatrix &matrix);
};

template<class T>
SMatrix<T>::SMatrix(int size) : Vector<Vector<T>>(size, Vector<T>()) {
    for (int i = 0; i < size; ++i) {
        this->x[i] = Vector<T>(size - i, 0);
    }
}

template<class T>
SMatrix<T>::SMatrix(const Vector<Vector<T>> &vector):Vector<Vector<T>>(vector) {}

template<class T>
SMatrix<T>::~SMatrix() = default;

template<class T>
SMatrix<T>::SMatrix(const SMatrix<T> &matrix): Vector<Vector<T>>(matrix) {}

template<class T>
SMatrix<T> &SMatrix<T>::operator=(const SMatrix<T> &matrix) {
    // TODO compare sizes
    if (this != matrix) {
        Vector<Vector<T>>::operator=(matrix);
    }
    return *this;
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
    }
    return ostr;
}




#endif //MATRIXLIB_SMATRIX_H
