#include "matrix.h"
#include <vector>
using namespace std;

vector<double> find_big(const Matrix& mat)
{
    if(mat.get_m() < 1 || mat.get_n() < 1){
        cout << "Error! Matrix is empty!" << endl;
        vector<double> er(1, 0);
        return er;
    }
    vector<double> v(mat.get_m(), 0);
    double maxi = mat.get_val(0, 0);
    //cout << maxi << '!' << endl;
    for(int i = 0; i < mat.get_m(); i++){
        v[i] = mat.get_val(i, 0);
        //cout << v[i] << ' ';
    }
    //cout << endl;

    for (int i = 0; i < mat.get_m(); i++){
        for(int j = 0; j < mat.get_n(); j++){
            if(mat.get_val(i, j) > maxi) {
                maxi = mat.get_val(i, j);
                for(int k = 0; k < mat.get_m(); k++){
                    v[k] = mat.get_val(k, j);
                    //cout << v[k] << ' ';
                }
                //cout << endl;
            }
        }
    }
    /*
    for(int i = 0; i < mat.get_m(); i++)
        cout << v[i] << ' ';
    cout << endl;
    */
    return v;

}

int main()
{
    /*
    Matrix matrixA(4,4);
    matrixA.create_M();
    Matrix matrixB(matrixA);
    matrixA.print_M();
    matrixB.print_M();

    matrixA.set_m(3);
    matrixA.set_n(3);
    matrixA.print_M();

    matrixA.set_m_n(5, 5);
    matrixA.print_M();

    cout << matrixA.get_m() << ' ' << matrixA.get_n() << endl << endl;

    matrixA.set_val(2, 3, 6);
    matrixA.print_M();

    cout << matrixA.get_val(2, 3) << endl << endl;

    matrixB.file_mat("matrix.txt");
    matrixB.print_M();

    matrixA = matrixB;
    matrixA.print_M();

    Matrix matrixC;
    matrixC = (matrixA + matrixB);
    matrixC.print_M();

    matrixC = matrixC * 1.5;
    matrixC.print_M();

    matrixC = (matrixC - matrixA);
    matrixC.print_M();
    */
    Matrix matrixD, matrixE, matrixF;

    //matrixF = matrixA*matrixC;
    //matrixF.print_M();


    matrixD.file_mat("data/matrix_D.txt");
    matrixD.print_M();
    matrixE.file_mat("data/matrix_E.txt");
    matrixE.print_M();
    matrixF = matrixE*matrixD;
    matrixF.print_M();
    
    Matrix matrixA;
    matrixA.file_mat("data/matrix.txt");
    matrixA.print_M();
    vector<double> k;
    k = find_big(matrixA);
    for (int i = 0; i < k.size(); i++)
        cout << k[i] << endl;
    cout << endl;
    



    return 0;
}
