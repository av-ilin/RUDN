#include "vector.h"

using namespace std;

int main()
{
    Vector myvector;
    myvector.print();
    myvector.print_stat();
    cout << endl;

    myvector.pushback(1.35);
    myvector.pushback(1.36);
    myvector.pushback(1.37);
    myvector.print();
    myvector.print_stat();
    cout << endl;

    myvector.pop(2);
    myvector.print();
    myvector.print_stat();
    cout << endl;

    cout << myvector[1] << endl << endl;

    Vector myvector2;
    myvector2 = myvector;
    myvector2.pushback(1.38);
    myvector2.pushback(1.39);
    myvector2.pushback(1.41);
    myvector2(1, 1.11);
    myvector2.print();
    myvector2.print_stat();

    return 0;
}
