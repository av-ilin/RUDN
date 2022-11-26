#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

class Vector
{
private:
    int length;
    int capacity;
    double* data;
    void addcapacity();
public:
    Vector();
    Vector(int len);
    Vector(int len, double init_value);
    Vector(const Vector &vector_);

    int get_length();
    int get_capacity();
    bool isEmpty();

    void print();
    void print_stat();
    void pushback(double value);
    void pop(int index);

    Vector& operator=(const Vector &vector_);
    double operator[](int index);
    void operator()(int index, double value);

    ~Vector();
};

#endif // VECTOR_H
