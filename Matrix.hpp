#include <algorithm>
#include <cstddef>

#include <iostream>
#include <string>
//
// Created by 14864 on 2020/12/6.
//

#ifndef ASS4_BY_CLION_MATRIX_HPP
#define ASS4_BY_CLION_MATRIX_HPP

#endif //ASS4_BY_CLION_MATRIX_HPP


using namespace std;

class Scalar{
private:
    int len;
    float * s;
public:
    Scalar();
    Scalar(int len);
    int getLen(){return len;}
    float* getS(){return s;}
};

Scalar::Scalar() {
    len = 10;
    s = new float[10];
}

Scalar::Scalar(int len) {
    this->len = len;
    s = new float[len];
}

class Matrix {
private:
    int m; //rows
    int n; //columns
    float **mat;
    int refcount; // 数据被多少对象引用
public:
    Matrix();

    Matrix(int m, int n);

    Matrix(int m, int n, float **mat);

    Matrix(Matrix &mat);

    ~Matrix();

    Matrix& operator=(Matrix &matrix);

    friend ostream &operator<<(ostream &os, const Matrix &mat);

    static Matrix mat_product(Matrix m1, Matrix m2);

    Matrix operator*( Matrix &mat);

    Matrix operator*(Scalar &scalar);

    friend Matrix operator*(Scalar &scalar,Matrix &mat);

    int getM(){return m;}
    int getN(){return n;}
    float** getMat(){return mat;}

};

//无参构造器
Matrix::Matrix() {
    m = 10;
    n = 10;
    mat = new float *[m];
    for (int i = 0; i < m; i++) {
        mat[i] = new float[n]();
    }
    refcount = 1;
}

//有参构造器1
Matrix::Matrix(int m, int n) {
    this->m = m;
    this->n = n;
    mat = new float *[m];
    for (int i = 0; i < m; i++) {
        mat[i] = new float[n]();
    }
    refcount = 1;
}

//有参构造器2
Matrix::Matrix(int m, int n, float **mat) {
    this->m = m;
    this->n = n;
    this->mat = mat;
    refcount = 1;
}


//拷贝构造器
Matrix::Matrix(Matrix &mat) {
    this->m = mat.m;
    this->n = mat.n;
    this->mat = mat.mat;
    this->refcount = mat.refcount;
    refcount++;
}

//析构器
Matrix::~Matrix() {
    if (refcount == 1) {
        delete[] mat;
    } else {
        refcount--;
    }
}

// =运算符重载
Matrix& Matrix::operator=(Matrix &matrix) {
    this->m = matrix.m;
    this->n = matrix.n;
    this->mat = matrix.mat;
    this->refcount = matrix.refcount;
    matrix.refcount++;
    return *this;
}

// <<运算符重载
ostream &operator<<(ostream &os, const Matrix &mat) {
    for (int i = 0; i < mat.m; i++) {
        for (int j = 0; j < mat.n; j++) {
            os << mat.mat[i][j] << " ";
        }
        os << endl;
    }
    return os;
}

float dot_product1(const float* v1, const float* v2, size_t n) {
    float sum = 0.0f;
    for (size_t i = 0; i < n; i++)
        sum += (v1[i] * v2[i]);
    return sum;
}

// *运算符重载 矩阵乘矩阵
Matrix Matrix::operator*( Matrix &mat)
{
    Matrix ans(this->getM(), mat.getN());
    if (this->getN() != mat.getM()) {
        cerr << "The number of the first matrix's columns must equal to the second matrix's rows." << endl;
        return ans;
    }
    for (int i = 0; i < ans.getM(); i++) {
        float* v2 = new float[mat.getM()];
        for (int j = 0; j < ans.getN(); j++) {
            for (int k = 0; k < mat.getM(); k++) {
                v2[k] = mat.getMat()[j][k];
            }
            ans.getMat()[i][j] = dot_product1(this->getMat()[i], v2, mat.getM());
        }
    }
    return ans;
}

// *运算符重载 矩阵乘向量
Matrix Matrix::operator*(Scalar &scalar) {
    Matrix ans(this->getM(),scalar.getLen());
    if(this->getN() != 1){
        cerr << "The number of the first matrix's columns must equal to the second matrix's rows." << endl;
        return ans;
    }
    float* v2 = new float[1];
    for (int i = 0; i < ans.getM(); i++) {
        for (int j = 0; j < ans.getN(); j++) {
            v2[0] = scalar.getS()[j];
            ans.getMat()[i][j] = dot_product1(this->getMat()[i], v2, 1);
        }
    }
    return ans;
}

// *运算符重载 向量乘矩阵
Matrix operator*(Scalar &scalar,Matrix &mat){
    Matrix ans(1,mat.getN());
    if(scalar.getLen() != mat.getM()){
        cerr << "The number of the first matrix's columns must equal to the second matrix's rows." << endl;
        return ans;
    }
    float* v2 = new float[mat.getM()];
    for(int i=0;i<mat.getN();i++){
        for(int j=0;j<mat.getM();j++){
            v2[j] = mat.getMat()[j][i];
        }
        ans.getMat()[0][i] = dot_product1(scalar.getS(),v2,scalar.getLen());
    }
    return ans;
}
