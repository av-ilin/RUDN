#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <string>
#include <fstream>

class Matrix
{
private:
    unsigned int m; //height
    unsigned int n; //width
    double** val; //data
public:
    Matrix();
    Matrix(int width, int height);
    void create_M();
    void delete_M();
    Matrix(const Matrix& other_matrix);
    ~Matrix();
    void print_M();
    void set_m(int _m);
    void set_n(int _n);
    void set_m_n(int _m, int _n);
    unsigned int get_m() const;
    unsigned int get_n() const;
    void set_val(int i, int j, double new_val);
    double get_val(int i, int j) const;
    void file_mat(std::string name_f);
    Matrix operator+(const Matrix &other_mat);
    Matrix& operator=(const Matrix &other_mat);
    Matrix operator*(double num);
    Matrix operator-(const Matrix &other_mat);
    Matrix operator*(const Matrix &other) ;
};

#endif // MATRIX_H
