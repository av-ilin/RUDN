#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
using namespace std;

void mat_file(string name_f, vector<vector<int> > &mat){
    ifstream file(name_f);
    for(int i = 0; i < mat.size(); i++)
        for(int j = 0; j < mat[i].size(); j++)
            file >> mat[i][j];

    file.seekg(0, ios::beg);
    file.clear();
    file.close();
}
void print(const vector<vector<int> > &mat){
    for(int i = 0; i < mat.size(); i++){
        for(int j = 0; j < mat[i].size(); j++)
            cout << mat[i][j] << ' ';
        cout << endl;
    }
    cout << endl;
}
void print(const vector<int> &v){
    for(int i = 0; i < v.size(); i++)
        cout << v[i] << ' ';
    cout << endl;
}
void print(const vector<vector<double> > &mat){
    for(int i = 0; i < mat.size(); i++){
        for(int j = 0; j < mat[i].size(); j++){
            if(mat[i][j] == int(mat[i][j])) cout << int(mat[i][j]) << ' ';
            else
                printf ("%.2f ", mat[i][j]);
        }

        cout << endl;
    }
    cout << endl;
}
void print(const vector<double> &v){
    for(int i = 0; i < v.size(); i++){
        if(v[i] == int(v[i])) cout << int(v[i]) << ' ';
        else
            printf ("%.2f ", v[i]);
    }
    cout << endl << endl;
}
void v_to_mat(const vector<double> &v, vector<vector<double> > &mat){
    int c(0);
    for(int i = 0; i < mat.size(); i++)
        for(int j = 0; j < mat[i].size(); j++){
            mat[i][j] = v[c];
            c++;
        }
}
void mat_to_v(vector<int> &v, const vector<vector<int> > &mat){
    for(int i = 0; i < mat.size(); i++)
        for(int j = 0; j < mat[i].size(); j++)
            v.push_back(mat[i][j]);
}
void print_obj(const vector<vector<int> > &o){
    for(int i = 0; i < o.size(); i++){
        for(int j = 0; j < o[i].size(); j++){
            if(o[i][j] == 0)
                cout << "  ";
            else
                cout << o[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;
}

//3 1 2 4 1 5 3 1 6 3
//3 1 2 3 4 5 6 7 8 10
void inversion(vector<vector<double> > &A){
    int N = A.size();
    double temp;
    vector<vector<double> > E(N, vector<double> (N, 0));

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++){
            E[i][j] = 0.0;
            if (i == j)
                E[i][j] = 1.0;
        }

    for (int k = 0; k < N; k++){
        temp = A[k][k];

        for (int j = 0; j < N; j++){
            A[k][j] /= temp;
            E[k][j] /= temp;
        }
        //cout << "+" << k << endl;
        for (int i = k + 1; i < N; i++){
            //cout << "-" << i << endl;
            temp = A[i][k];
            for (int j = 0; j < N; j++){
                A[i][j] -= A[k][j] * temp;
                E[i][j] -= E[k][j] * temp;
            }
        }
    }

    for (int k = N - 1; k > 0; k--)
        for (int i = k - 1; i >= 0; i--){
            temp = A[i][k];
            for (int j = 0; j < N; j++){
                A[i][j] -= A[k][j] * temp;
                E[i][j] -= E[k][j] * temp;
            }
        }

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            A[i][j] = E[i][j];

}
vector<vector<double> > multi(const vector<vector<double> > &a, const vector<vector<double> > &b){
    int row1(a.size()), col1(a[0].size());
    int row2(b.size()), col2(b[0].size());
    vector<vector<double> > c(row1, vector<double> (col2, 0));
    for (int i = 0; i < row1; i++){
        for (int j = 0; j < col2; j++){
          c[i][j] = 0;
          for (int k = 0; k < col1; k++)
            c[i][j] += a[i][k] * b[k][j];
        }
    }
    return c;
}

vector<vector<double> > s_covs(const vector<vector<int> > &z, const vector<double> &_z){
    vector<vector<double> > covs(_z.size(), vector<double> (_z.size(), 0));
    int N = z.size();
    for(int i = 0; i < covs.size(); i++)
        for(int j = 0; j < covs[i].size(); j++){
            for(int k = 0; k < N; k++)
                covs[i][j] += (z[k][i] - _z[i]) * (z[k][j] - _z[j]);

            covs[i][j] *= 1.0 / (N - 1);
        }

    return covs;
}
double EM (const vector<double> &x, const vector<int> &y, const vector<vector<double> > &S){
    int n = x.size();

    vector<double> temp0;
    for(int i = 0; i < n; i++)
        temp0.push_back(x[i] - y[i]);

    vector<vector<double> > third;
    for(int i = 0; i < n; i++)
    {
        vector<double> temp;
        temp.push_back(temp0[i]);
        third.push_back(temp);
    }

    vector<vector<double> > first;
    first.push_back(temp0);

    vector<vector<double> > second(n, vector<double> (n, 0));
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++){
            second[i][j] = S[i][j];
            if(i == j)
                second[i][j]++;
        }

    vector<vector<double> > result = multi(first, second);
    result = multi(result, third);
    double temp = result[0][0];
    temp = sqrt(temp);
    return temp;
}


class object{
private:
    string name;
    vector<double> core;
    vector<vector<double> > covs;
public:
    vector<double> get_core(){return core;}
    void set_core(const vector<vector<int> > &v1, const vector<vector<int> > &v2, const vector<vector<int> > &v3){
        vector<double> core0;
        for(int i = 0; i < v1.size(); i++)
            for(int j = 0; j < v1[i].size(); j++)
                core0.push_back((v1[i][j] + v2[i][j] + v3[i][j])/3.0);
        core = core0;
    }

    vector<vector<double> > get_covs(){return covs;}
    void set_covs(const vector<vector<double> > &covs0){covs = covs0;}

    string get_name(){return name;}
    void set_name(string name0){name = name0;}

    void print_covs(){print(covs);}
    void print_core(){print(core);}
    void print_core_mat(int n, int k){
        int c(0);
        for(int i = 0; i < n; i++){
            for(int j = 0; j < k; j++){
                if(core[c] == int(core[c]))
                    cout << int(core[c]) << '\t';
                else
                    printf ("%.1f\t", core[c]);
                c++;
            }
            cout << endl;
        }
        cout << endl;
    }

};
class RGB{
private:
    string name;
    vector<double> core;
    vector<vector<double> > covs;
public:
    vector<double> get_core(){return core;}
    void set_core(const vector<int> &v1, const vector<int> &v2, const vector<int> &v3){
        vector<double> core0;
        for(int i = 0; i < v1.size(); i++)
                core0.push_back((v1[i] + v2[i] + v3[i])/3.0);
        core = core0;
    }

    vector<vector<double> > get_covs(){return covs;}
    void set_covs(const vector<vector<double> > &covs0){covs = covs0;}

    string get_name(){return name;}
    void set_name(string name0){name = name0;}

    void print_covs(){print(covs);}
    void print_core(){print(core);}
};
class weapon{
private:
    string name;
    vector<double> core;
    vector<vector<double> > covs;
public:
    vector<double> get_core(){return core;}
    void set_core(const vector<int> &v1, const vector<int> &v2, const vector<int> &v3){
        vector<double> core0;
        for(int i = 0; i < v1.size(); i++)
                core0.push_back((v1[i] + v2[i] + v3[i])/3.0);
        core = core0;
    }

    vector<vector<double> > get_covs(){return covs;}
    void set_covs(const vector<vector<double> > &covs0){covs = covs0;}

    string get_name(){return name;}
    void set_name(string name0){name = name0;}

    void print_covs(){print(covs);}
    void print_core(){print(core);}
};

int main(){

    int n(9), k(7);
    vector<vector<int> > x1(n, vector<int> (k,0));
    vector<vector<int> > x2(n, vector<int> (k,0));
    vector<vector<int> > x3(n, vector<int> (k,0));
    string name_f;
    name_f = "data\\X1.txt"; mat_file(name_f, x1);
    name_f = "data\\X2.txt"; mat_file(name_f, x2);
    name_f = "data\\X3.txt"; mat_file(name_f, x3);
    vector<vector<int> > tmp;
    vector<int> v;
    mat_to_v(v, x1);tmp.push_back(v);v.clear();
    mat_to_v(v, x2);tmp.push_back(v);v.clear();
    mat_to_v(v, x3);tmp.push_back(v);v.clear();

    object x;
    x.set_name("Object X");
    x.set_core(x1, x2, x3);
    x.set_covs(s_covs(tmp, x.get_core()));

    print(x1); print(x2); print(x3);
    cout << x.get_name() << endl; x.print_core_mat(n, k); x.print_core(); print(tmp); x.print_covs();

    cout << "__________________________________________________" << endl;

    vector<vector<int> > y1(n, vector<int> (k,0));
    vector<vector<int> > y2(n, vector<int> (k,0));
    vector<vector<int> > y3(n, vector<int> (k,0));
    name_f = "data\\Y1.txt"; mat_file(name_f, y1);
    name_f = "data\\Y2.txt"; mat_file(name_f, y2);
    name_f = "data\\Y3.txt"; mat_file(name_f, y3);
    tmp.clear();
    mat_to_v(v, y1);tmp.push_back(v);v.clear();
    mat_to_v(v, y2);tmp.push_back(v);v.clear();
    mat_to_v(v, y3);tmp.push_back(v);v.clear();

    object y;
    y.set_name("Object Y");
    y.set_core(y1, y2, y3);
    y.set_covs(s_covs(tmp, y.get_core()));

    print(y1); print(y2); print(y3);
    cout << y.get_name() << endl; y.print_core_mat(n, k); y.print_core(); print(tmp); y.print_covs();

    cout << "__________________________________________________" << endl;

    vector<vector<int> > z1(n, vector<int> (k,0));
    vector<vector<int> > z2(n, vector<int> (k,0));
    vector<vector<int> > z3(n, vector<int> (k,0));
    name_f = "data\\z1.txt"; mat_file(name_f, z1);
    name_f = "data\\z2.txt"; mat_file(name_f, z2);
    name_f = "data\\z3.txt"; mat_file(name_f, z3);
    tmp.clear();
    mat_to_v(v, z1);tmp.push_back(v);v.clear();
    mat_to_v(v, z2);tmp.push_back(v);v.clear();
    mat_to_v(v, z3);tmp.push_back(v);v.clear();

    object z;
    z.set_name("Object Z");
    z.set_core(z1, z2, z3);
    z.set_covs(s_covs(tmp, z.get_core()));

    print(z1); print(z2); print(z3);
    cout << z.get_name() << endl; z.print_core_mat(n, k); z.print_core(); print(tmp); z.print_covs();

    cout << "__________________________________________________" << endl;

    while(true){
        string name;
        cin >> name;
        if (name == "-1") break;
        vector<vector<int> > obj(n, vector<int> (k,0));
        name_f = "data\\" + name + ".txt";
        mat_file(name_f, obj);
        print_obj(obj);
        vector<int> _obj;
        mat_to_v(_obj, obj);

        //print(x0); print(_x);
        double ex = EM(x.get_core(), _obj, x.get_covs());
        double ey = EM(y.get_core(), _obj, y.get_covs());
        double ez = EM(z.get_core(), _obj, z.get_covs());
        cout << "Result: " << "X_ " << ex << " Y_ " << ey << " Z_ " << ez << endl;

        if(ex < ey && ex < ez)
            cout << "This is " << x.get_name() << endl << endl;
        else if(ey < ex && ey < ez)
            cout << "This is " << y.get_name() << endl << endl;
        else if(ez < ex && ez < ey)
            cout << "This is " << z.get_name() << endl << endl;
        else
            cout << "Unknown" << endl << endl;
    }

    cout << "\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\" << endl;


    vector<vector<int> > red0 = {{255, 0, 0}, {128, 0, 0}, {1, 0, 0}};

    RGB red;
    red.set_name("Red");
    red.set_core(red0[0], red0[1], red0[2]);
    red.set_covs(s_covs(red0, red.get_core()));

    print(red0);
    cout << red.get_name() << endl; red.print_core(); red.print_covs();

    cout << "__________________________________________________" << endl;

    vector<vector<int> > green0 = {{0, 255, 0}, {0, 128, 0}, {0, 1, 0}};

    RGB green;
    green.set_name("Green");
    green.set_core(green0[0], green0[1], green0[2]);
    green.set_covs(s_covs(green0, green.get_core()));

    print(green0);
    cout << green.get_name() << endl; green.print_core(); green.print_covs();

    cout << "__________________________________________________" << endl;

    vector<vector<int> > blue0 = {{0, 0, 255}, {0, 0, 128}, {0, 0, 1}};

    RGB blue;
    blue.set_name("Blue");
    blue.set_core(blue0[0], blue0[1], blue0[2]);
    blue.set_covs(s_covs(blue0, blue.get_core()));

    print(blue0);
    cout << blue.get_name() << endl; blue.print_core(); blue.print_covs();

    cout << "__________________________________________________" << endl;

    while(true){
        int temp; cin >> temp;
        if (temp == -1) break;

        vector<int> _rgb(3, 0);
        _rgb[0] = temp;
        for(int i = 1; i < 3; i++)
            cin >> _rgb[i];


        double er = EM(red.get_core(), _rgb, red.get_covs());
        double eg = EM(green.get_core(), _rgb, green.get_covs());
        double eb = EM(blue.get_core(), _rgb, blue.get_covs());

        cout << "Result: " << "Red_" << er << " Green_" << eg << " Blue_" << eb << endl;

        if(er < eg && er < eb)
            cout << "It's a shade of " << red.get_name() << endl << endl;
        else if(eg < er && eg < eb)
            cout << "It's a shade of " << green.get_name() << endl << endl;
        else if(eb < er && eb < eg)
            cout << "It's a shade of " << blue.get_name() << endl << endl;
        else
            cout << "Unknown" << endl << endl;
    }

    cout << "\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\" << endl;
    vector<vector<int> > w1 = {{5, 100, 1300, 1250}, {7, 250, 1250, 1300}, {7, 200, 1800, 970}};

    weapon mgun;
    mgun.set_name("Machine gun");
    mgun.set_core(w1[0], w1[1], w1[2]);
    mgun.set_covs(s_covs(w1, mgun.get_core()));

    print(w1);
    cout << mgun.get_name() << endl; mgun.print_core(); mgun.print_covs();

    cout << "__________________________________________________" << endl;

    vector<vector<int> > w2 = {{5, 30, 500, 750}, {5, 30, 1000, 500}, {5, 40, 600, 850}};

    weapon asle;
    asle.set_name("Assault rifle");
    asle.set_core(w2[0], w2[1], w2[2]);
    asle.set_covs(s_covs(w2, asle.get_core()));

    print(w2);
    cout << asle.get_name() << endl; asle.print_core(); asle.print_covs();

    cout << "__________________________________________________" << endl;

    vector<vector<int> > w3 = {{12, 10, 2500, 0}, {8, 10, 1300, 0}, {12, 5, 2430, 0}};

    weapon snile;
    snile.set_name("Sniper Rifle");
    snile.set_core(w3[0], w3[1], w3[2]);
    snile.set_covs(s_covs(w3, snile.get_core()));

    print(w3);
    cout << snile.get_name() << endl; snile.print_core(); snile.print_covs();

    cout << "__________________________________________________" << endl;

    while(true){
        int temp; cin >> temp;
        if (temp == -1) break;

        vector<int> _w(4, 0);
        _w[0] = temp;
        for(int i = 1; i < 4; i++)
            cin >> _w[i];

        double eg = EM(mgun.get_core(), _w, mgun.get_covs());
        double ea = EM(asle.get_core(), _w, asle.get_covs());
        double es = EM(snile.get_core(), _w, snile.get_covs());
        cout << "Result: " << "Mgun_" << eg << " Asle_" << ea << " Snile_" << es << endl;

        if(eg < ea && eg < es)
            cout << "It's a " << mgun.get_name() << endl << endl;
        else if(ea < eg && ea < es)
            cout << "It's a " << asle.get_name() << endl << endl;
        else if(es < eg && es < ea)
            cout << "It's a " << snile.get_name() << endl << endl;
        else
            cout << "Unknown" << endl << endl;
    }

    return 0;
}
