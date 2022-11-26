#include "vector.h"

Vector::Vector(){
    length = 0;
    data = new double[1];
    capacity = 1;
}
Vector::Vector(int len){
    length = len;
    capacity = 1;
    while(capacity < length)
        capacity *= 2;
    data = new double[capacity];
}
Vector::Vector(int len, double init_value){
    length = len;
    capacity = 1;
    while(capacity < length)
        capacity *= 2;
    data = new double[capacity];
    for(int i = 0; i < len; i++)
        data[i] = init_value;
}
Vector::Vector(const Vector &vector_){
    if(this != &vector_){
        delete[] data;
        data = new double[vector_.capacity];
        for (int i = 0; i < vector_.length; i++)
            data[i] = vector_.data[i];
        length = vector_.length;
        capacity = vector_.capacity;
    }
}
Vector::~Vector(){
    delete[] data;
}

int Vector::get_length(){
    return length;
}
int Vector::get_capacity(){
    return capacity;
}
bool Vector::isEmpty(){
    if(length == 0)
        return true;
    return false;
}
void Vector::addcapacity(){
    capacity *= 2;
    double* tmp = data;
    data = new double[capacity];
    for(int i = 0; i < length; i++)
        data[i] = tmp[i];
    delete[] tmp;
}

void Vector::print(){
    for(int i = 0; i < length; i++)
        std::cout << data[i] << ' ';
    if (length == 0)
        std::cout << "Vector is empty!";
    std::cout << std::endl;
}
void Vector::print_stat(){
    std::cout << "Length: " << length << std::endl;
    std::cout << "Capacity: " << capacity << std::endl;
}
void Vector::pushback(double value){
    if(capacity <= length)
        addcapacity();
    data[length] = value;
    length++;
}
void Vector::pop(int index){
    if (index >= length || index < 0)
        std::cout << "Out of vector limits!" << std::endl;
    else{
        for (int i = index + 1; i < length; i++)
            data[i - 1] = data[i];
        length--;
    }
}

Vector& Vector::operator=(const Vector &vector_){
    if(this != &vector_){
        delete[] data;
        data = new double[vector_.capacity];
        for (int i = 0; i < vector_.length; i++)
            data[i] = vector_.data[i];
        length = vector_.length;
        capacity = vector_.capacity;
    }
    return *this;
}
double Vector::operator[](int index){
    return data[index];
}
void Vector::operator()(int index, double value){
    data[index] = value;
}

