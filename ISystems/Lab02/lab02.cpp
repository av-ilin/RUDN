#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>

using namespace std;

bool sortbysec(const pair<char,int> &a, const pair<char,int> &b){
    return (a.second < b.second);
}
int getRN(int min, int max){
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}


void print(const vector<vector<int> > &mat){
    for(int i = 0; i < mat.size(); i++){
        for(int j = 0; j < mat[i].size(); j++)
            cout << mat[i][j] << "\t";
        cout << endl;
    }
    cout << endl;
}
void print(const vector<int> &dp){
    for(int i = 0; i < dp.size(); i++)
        cout << dp[i];
    cout << endl;
}
void print_solve(const vector<vector<int> > &solution){
    cout << "Solution" << endl;
    int st = 0;
    for(int i = 0; i < solution.size(); i++){
        cout << "Step " << st << ": ";
        for(int j = 0; j < solution[i].size(); j++)
             cout << solution[i][j] << ' ';
        st++;
        cout << endl;
    }
}

void fil(vector<vector<int> > &mat){
    int num = 0;
    for(int i = 0; i < mat.size(); i++)
        for(int j = 0; j < mat[i].size(); j++)
        {
            mat[i][j] = num;
            num++;
        }

    int n = mat.size();
    int l = mat[0].size();
    int s = getRN(1,5);
    for(int i = 0; i < s; i++){
        int k1, k2, l1, l2;
        k1 = getRN(0,n - 1);
        l1 = getRN(0,l - 1);
        k2 = getRN(0,n - 1);
        l2 = getRN(0,l - 1);
        swap(mat[k1][l1], mat[k2][l2]);
    }
}

int check0(const vector<vector<int> > &mat,int i0, int j0){
    int n(0);
    for(int i = i0; i < mat.size(); i++){
        int j(j0);
        if(i != i0) j = 0;
        for(j; j < mat[i].size(); j++){
            if(mat[i][j] < mat[i0][j0] && mat[i][j] != 0)
                n++;
        }
    }
    return n;
}
bool check(const vector<vector<int> > &mat){
    int N(0);
    for(int i = 0; i < mat.size(); i++){
        for(int j = 0; j < mat[i].size(); j++)
            if(mat[i][j] != 0)
                N = N + check0(mat, i, j);
    }
    for(int i = 0; i < mat.size(); i++)
        for(int j = 0; j < mat[i].size(); j++)
            if(mat[i][j] == 0){
                N = N + i + 1;
                break;
            }
    if(N%2 == 1)
        return false;
    return true;
}


void left(vector<vector<int> > &mat, int x, int y){
    swap(mat[y][x], mat[y][x-1]);
}
void right(vector<vector<int> > &mat, int x, int y){
    swap(mat[y][x], mat[y][x+1]);
}
void up(vector<vector<int> > &mat, int x, int y){
    swap(mat[y][x], mat[y-1][x]);
}
void down(vector<vector<int> > &mat, int x, int y){
    swap(mat[y][x], mat[y+1][x]);
}

vector<int> mat_to(const vector<vector<int> > &mat){
    vector<int> dp;
    for(int i = 0; i < mat.size(); i++)
        for(int j = 0; j < mat[i].size(); j++)
            dp.push_back(mat[i][j]);
    return dp;
}

int md(const vector<vector<int> > &mat, const vector<vector<int> > &tar){
    int MD(0);
    //print(tar);
    for(int i = 0; i < mat.size(); i++){
        for(int j = 0; j < mat[i].size(); j++){

            if(mat[i][j] == 0) continue;

            int i0, j0;
            for(int i1 = 0; i1 < tar.size(); i1++)
                for(int j1 = 0; j1 < tar[i1].size(); j1++)
                if(tar[i1][j1] == mat[i][j]){
                    i0 = i1;
                    j0 = j1;
                    break;
                }

            //cout << i0 << ' ' << j0 << " | " << i << ' ' << j << " | " << mat[i][j] << endl;
            MD = MD + abs(i0 - i) + abs(j0 - j);
        }
    }
    return MD;
}

void s_zero(const vector<vector<int> > &mat, int &x, int &y){
    for(int i = 0; i < mat.size(); i++)
        for(int j = 0; j < mat[i].size(); j++)
            if(mat[i][j] == 0){
                x = j;
                y = i;
            }
}

bool check_use(const vector<int> &mat0, const vector<vector<int> > &used){
    bool chack(true);
    for(int i = 0; i < used.size(); i++){
        if(used[i] == mat0){
            chack = false;
            break;
        }
    }
    return chack;
}

bool flag = false;
vector<vector<int> > solution;
void dfs(vector<vector<int> > &mat, const vector<vector<int> > &tar, vector<vector<int> > &used, int deep, int step){

    if(mat == tar){
        flag = true;
        int md1 = md(mat, tar);
        cout << "Step: " << step << " Deep: " << deep << " Distance: " << md1 << " Matrix: ";
        print(mat_to(mat));
        print(mat);
        solution.push_back(mat_to(mat));

    }
    if(flag) return;

    solution.push_back(mat_to(mat));
    int md1 = md(mat, tar);
    cout << "Step: " << step << " Deep: " << deep << " Distance: " << md1 << " Matrix: "; print(mat_to(mat));
    //print(used);
    //for(int i = 0; i < rule.size();i++) cout << rule[i].first << ' ' << rule[i].second << " | "; cout << endl;

    vector<pair<char,int> > rule;
    int x, y;
    s_zero(mat, x, y);
    if(x - 1 > -1){
        vector<vector<int> > mat0 = mat;
        left(mat0, x, y);
        vector<int> mat1 = mat_to(mat0);

        if(check_use(mat1, used)){
            int MD = md(mat0, tar);
            rule.push_back(make_pair('l',MD));
        }

        //print(mat0);print(mat1);cout << check_use(mat1, used) << endl;
    }
    if(x + 1 < mat[0].size()){
        vector<vector<int> > mat0 = mat;
        right(mat0, x, y);
        vector<int> mat1 = mat_to(mat0);

        if(check_use(mat1, used)){
            int MD = md(mat0, tar);
            rule.push_back(make_pair('r',MD));
        }

        //print(mat0);print(mat1);cout << check_use(mat1, used) << endl;
    }
    if(y - 1 > -1){
        vector<vector<int> > mat0 = mat;
        up(mat0, x, y);
        vector<int> mat1 = mat_to(mat0);

        if(check_use(mat1, used)){
            int MD = md(mat0, tar);
            rule.push_back(make_pair('u',MD));
        }

        //print(mat0);print(mat1);cout << check_use(mat1, used) << endl;
    }
    if(y + 1 < mat.size()){
        vector<vector<int> > mat0 = mat;
        down(mat0, x, y);
        vector<int> mat1 = mat_to(mat0);

        if(check_use(mat1, used)){
            int MD = md(mat0, tar);
            rule.push_back(make_pair('d',MD));
        }

        //print(mat0);print(mat1);cout << check_use(mat1, used) << endl;
    }
    sort(rule.begin(), rule.end(), sortbysec);

    deep++;
    for(int i = 0; i < rule.size(); i++){
        switch(rule[i].first){
            case 'l': left(mat, x, y); used.push_back(mat_to(mat));step++; dfs(mat, tar, used, deep, step); break;
            case 'r': right(mat, x, y); used.push_back(mat_to(mat));step++; dfs(mat, tar, used, deep, step); break;
            case 'u': up(mat, x, y); used.push_back(mat_to(mat));step++; dfs(mat, tar, used, deep, step); break;
            case 'd': down(mat, x, y); used.push_back(mat_to(mat));step++; dfs(mat, tar, used, deep, step); break;
            default: solution.pop_back(); deep--; return;
        }
    }

}

int main(){
    srand(static_cast<unsigned int>(time(0)));
    int n, k;
    cin >> n >> k;

    vector<vector<int> > mat(n, vector<int> (k, 0));
    fil(mat);
    while(!check(mat))
        fil(mat);
    print(mat);

    int c(1);
    vector<vector<int> > target(n, vector<int> (k, 0));
    for(int i = 0; i < n; i++)
        for(int j = 0; j < k; j++){
            target[i][j] = c;
            c++;
        }
    target[n-1][k-1] = 0;

    //print(target);

    vector<vector<int> > used;
    int deep(0), step(0);
    dfs(mat, target, used, deep, step);
    //cout << md(mat, target) << endl;

    //print_solve(solution);
    return 0;
}
