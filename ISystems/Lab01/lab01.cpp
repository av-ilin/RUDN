#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <set>
using namespace std;

void print_matr(const vector<vector<int> > &matr){
    for(int i = 0; i < matr.size(); i++){
        for(int j = 0; j < matr[i].size(); j++)
            cout << matr[i][j] << ' ';
        cout << endl;
    }
    cout << endl;
}

void print_v(const vector<int> &v){
    for(int j = 0; j < v.size(); j++)
        cout << v[j] << ' ';
    cout << endl << endl;;
}

void print_x(const vector<vector<int> > &x){
    for(int i = 0; i < x.size(); i++){
        cout << "state " << i << ": ";
        for(int j = 0; j < x[i].size(); j++)
            cout << x[i][j] << ' ';
        cout << endl;
    }


}


int getRandomNumber(int min, int max){

    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

/*
void random_v(vector<int> &v){
    for(int i = 0; i < v.size(); i++)
        v[i] = getRandomNumber(0,1);
}
*/

void all_v(vector<vector<int> > &v, int n){
    for(int i = 0; i < pow(2, n); i++){
        vector<int> bin;
        int b = i;
        while(b > 0){
            bin.push_back(b % 2);
            b /= 2;
        }
        if(bin.size() < n){
            int temp = n - bin.size();
            for(int j = 0; j < temp; j++)
                bin.push_back(0);
        }
        reverse(bin.begin(), bin.end());
        v.push_back(bin);
    }
}

void random_matr(vector<vector<int> > &matr,const int n, const int k){
    for(int i = 0; i < matr.size(); i++)
        for(int j = 0; j < k; j++){
            int s = getRandomNumber(0, n - 1);
            while (matr[i][s] == 1)
                s = getRandomNumber(0, n - 1);
            matr[i][s] = 1;
        }


}

void s_matr(const vector<vector<int> > &matr, vector<vector<int> > &matr0){
    for(int i = 0; i < matr.size(); i++)
        for(int j = 0; j < matr[i].size(); j++)
            if(matr[i][j] == 1)
                matr0[i].push_back(j);
}


int main(){
    int n, k;
    cin >> n >> k;
    //vector<int> v;
    vector<vector<int> > v;
    vector<vector<int> > matr(n, vector<int> (n, 0));
    vector<vector<int> > matr0(n, vector<int> (0, 0));

    srand(static_cast<unsigned int>(time(0)));
    //random_v(v);
    //print_v(v);
    all_v(v, n);
    print_matr(v);
    random_matr(matr, n, k);
    print_matr(matr);
    s_matr(matr, matr0);
    print_matr(matr0);

    vector<int> l;
    set<vector<int> > m;

    for(int sys = 0; sys < v.size(); sys++){
        vector<int> v0 = v[sys];
        vector<vector<int> > x;
        x.push_back(v0);
        bool check(true);
        while(check){
            vector<int> v1(n,0);
            for(int i = 0; i < n; i++){
                v1[i] = v0[matr0[i][0]];
                switch(i % 4){
                    case 0:
                        for(int j = 1; j < k; j++)
                            v1[i] = v1[i] || v0[matr0[i][j]];
                        break;
                    case 1:
                        for(int j = 1; j < k; j++)
                            v1[i] = v1[i] && v0[matr0[i][j]];
                        break;
                    case 2:
                        for(int j = 1; j < k; j++)
                            v1[i] = !(v1[i] || v0[matr0[i][j]]);
                        break;
                    case 3:
                        for(int j = 1; j < k; j++)
                            v1[i] = !(v1[i] && v0[matr0[i][j]]);
                        break;
                }
            }
            v0 = v1;
            for(int i = 0; i < x.size(); i++)
                if(x[i] == v0){
                    check = false;
                    l.push_back(x.size() - i);
                    //m.insert(v0);
                    break;
                }

            x.push_back(v0);
        }
        bool a_in(false);
        for(int i = 0; i < x.size();i++){
            if(m.find(x[i]) != m.end())
                a_in = true;
        }
        if(!a_in)
            m.insert(x[x.size()-1]);
        print_x(x);
        cout << endl;
    }


    print_v(l);
    set<vector<int> > :: iterator it = m.begin();
    for (int i = 1; it != m.end(); i++, it++)
        print_v(*it);


    int L(0), M;
    for(int i = 0; i < l.size(); i++)
        L += l[i];
    L /= l.size();
    M = m.size();
    cout << "L := " << L << "\t" << "M := " << M;

    return 0;
}
