#include "matrix.h"

Matrix::Matrix()
{
    std::cout << "The creation of the default matrix has started!" << std::endl;
    m = n = 0;
    val = nullptr;
    std::cout << "The default matrix creation is finished!" << std::endl << std::endl;
}

Matrix::Matrix(int width, int height)
{
    std::cout << "The creation of the matrix by the condition has started!" << std::endl ;
    if(width < 0 || height < 0){
        std::cout << "Error! The size must be greater than 0!" << std::endl;
        std::cout << "The values will be replaced with positive values!" << std::endl;
        width = abs(width);
        height = abs(height);
    }
    m = width;
    n = height;
    create_M();
    std::cout << "The creation of the matrix by the condition is finished!" << std::endl << std::endl;
}

Matrix::Matrix(const Matrix& other_matrix)
{
    std::cout << "Matrix copying started!" << std::endl << std::endl;
    m = other_matrix.m;
    n = other_matrix.n;
    create_M();
    for(unsigned int i = 0; i < m; i++)
        for(unsigned int j = 0; j < n; j++)
            val[i][j] = other_matrix.val[i][j];
    std::cout << "Matrix copying finished!" << std::endl << std::endl;
}

Matrix::~Matrix()
{
    delete_M();
}

void Matrix::create_M()
{
    std::cout << "The creation of the null matrix has begun!" << std::endl;
    val = new double*[m];
    for(unsigned int i = 0; i < m; i++){
        val[i] = new double[n];

        for(unsigned int j = 0; j < m; j++)
            val[i][j] = 0;
    }
    std::cout << "The creation of the null matrix is finished!" << std::endl << std::endl;
 }

void Matrix::delete_M()
{
    std::cout << "The matrix deletion has started!" << std::endl;
    for(unsigned int i = 0; i < m; i++)
        delete[] val[i];
    delete[] val;
    std::cout << "The matrix deletion is over!" << std::endl << std::endl;
}

void Matrix::print_M()
{
    std::cout << "Matrix output has started!" << std::endl;
    if (m == 0 || n == 0){
        std::cout << "Output is not possible!" << std::endl << std::endl;
        return;
    }
    for(unsigned int i = 0; i < m; i++){
        for(unsigned int j = 0; j < n; j++)
            std::cout << val[i][j] << "\t";
        std::cout << std::endl;
    }
    std::cout << "Matrix output is over!" << std::endl << std::endl;
}

void Matrix::set_m(int _m)
{
    if(_m < 0){
        std::cout << "Error! The size must be greater than 0!" << std::endl;
        std::cout << "The values will be replaced with positive values!" << std::endl;
        _m = abs(_m);
    }
    delete_M();
    m = _m;
    create_M();
}

void Matrix::set_n(int _n)
{
    if(_n < 0){
        std::cout << "Error! The size must be greater than 0!" << std::endl;
        std::cout << "The values will be replaced with positive values!" << std::endl;
        _n = abs(_n);
    }
    delete_M();
    n = _n;
    create_M();
}

void Matrix::set_m_n(int _m, int _n)
{
    if(_m < 0 || _n < 0){
        std::cout << "Error! The size must be greater than 0!" << std::endl;
        std::cout << "The values will be replaced with positive values!" << std::endl;
        _m = abs(_m);
        _n = abs(_n);
    }
    delete_M();
    m = _m;
    n = _n;
    create_M();
}

unsigned int Matrix::get_m() const
{
    return m;
}

unsigned int Matrix::get_n() const
{
    return n;
}

void Matrix::set_val(int i, int j, double new_val)
{
    if(i < 0 || j < 0){
        std::cout << "Error! The place must be greater than 0!" << std::endl;
        std::cout << "The values will be replaced with positive values!" << std::endl;
        i = abs(i);
        j = abs(j);
    }
    if (i >= m || j >= n){
        std::cout << "Error! You are out of the allowed values!" << std::endl << std::endl;
        return;
    }
    val[i][j] = new_val;
}

double Matrix::get_val(int i, int j) const
{
    if(i < 0 || j < 0){
        std::cout << "Error! The place must be greater than 0!" << std::endl;
        std::cout << "The values will be replaced with positive values!" << std::endl;
        i = abs(i);
        j = abs(j);
    }
    if (i >= m || j >= n){
        std::cout << "Error! You are out of the allowed values!" << std::endl;
        return 0.0;
    }
    return val[i][j];
}

void Matrix::file_mat(std::string name_f)
{
    std::cout << "Getting the matrix from the file has started!" << std::endl;
    std::ifstream file(name_f);
    if(file.is_open()) std::cout << "File is open!" << std::endl;
    else{
        std::cout << "Error! File is not open!" << std::endl << std::endl;
        return;
    }
    delete_M();
    file >> m;
    file >> n;
    create_M();
    for(unsigned int i = 0; i < m; i++){
        for(unsigned int j = 0; j < n; j++){
            if(file.eof()){
                std::cout << "Error! The file is empty, the values are not enough!" << std::endl;
                std::cout << "Getting the matrix from the file is over!!" << std::endl << std::endl;
                file.close();
                return;
            }
            file >> val[i][j];

        }
    }

    if(!file.eof()) std::cout << "Error! The file is not empty, but the values were enough!" << std::endl;

    file.close();
    file.clear();
    std::cout << "Getting the matrix from the file is over!!" << std::endl << std::endl;

}

Matrix Matrix::operator +(const Matrix& other_mat)
{
    if (m != other_mat.m || n != other_mat.n){
        std::cout << "Error! Matrix addition is impossible!" << std::endl;
        Matrix er;
        return er;
    }
    Matrix res(m, n);
    for(unsigned int i = 0; i < m; i++)
        for(unsigned int j = 0; j < n; j++)
            res.val[i][j] = val[i][j] + other_mat.val[i][j];

    return res;
}

Matrix Matrix::operator -(const Matrix& other_mat)
{
    if (m != other_mat.m || n != other_mat.n){
        std::cout << "Error! Matrix addition is impossible!" << std::endl;
        Matrix er;
        return er;
    }
    Matrix res(m, n);
    for(unsigned int i = 0; i < m; i++)
        for(unsigned int j = 0; j < n; j++)
            res.val[i][j] = val[i][j] - other_mat.val[i][j];

    return res;
}

Matrix& Matrix::operator =(const Matrix& other_mat)
{
    delete_M();
    m = other_mat.m;
    n = other_mat.n;
    create_M();
    for(unsigned int i = 0; i < m; i++)
        for(unsigned int j = 0; j < n; j++)
            val[i][j] = other_mat.val[i][j];
    return *this;
}

Matrix Matrix::operator *(double num)
{
    Matrix res(m, n);
    for(unsigned int i = 0; i < m; i++)
        for(unsigned int j = 0; j < n; j++)
            res.val[i][j] = val[i][j] * num;

    return res;
}

Matrix Matrix::operator *(const Matrix& other_mat)
{
    if (m != other_mat.n || n != other_mat.m){
        std::cout << "Error! Matrix addition is impossible!" << std::endl;
        Matrix er;
        return er;
    }
    Matrix res(m, other_mat.n);
    for(unsigned int i = 0; i < m; i++)
        for(unsigned int j = 0; j < other_mat.n; j++)
            for(unsigned int k = 0; k < n; k++)
                res.val[i][j] += val[i][k] * other_mat.val[k][j];

    return res;
}

