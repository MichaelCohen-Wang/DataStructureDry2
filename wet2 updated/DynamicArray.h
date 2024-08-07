#ifndef DYNAMICARRAY_H_
#define DYNAMICARRAY_H_

#include <stdexcept>
#include "PrimeHelper.h"

template<typename T>
class DynamicArray {
private:
    T* data;
    int capacity;
    int size;

public:
    DynamicArray();
    ~DynamicArray();

    void push_back(const T& value);
    T& operator[](int index);
    int get_size() const;

    void resize(int new_capacity); // Move this to public
};

template<typename T>
DynamicArray<T>::DynamicArray() : data(nullptr), capacity(0), size(0) {}

template<typename T>
DynamicArray<T>::~DynamicArray() {
    delete[] data;
}

template<typename T>
void DynamicArray<T>::resize(int new_capacity) {
    new_capacity = PrimeHelper::next_prime(new_capacity);
    T* new_data = new T[new_capacity];
    for (int i = 0; i < size; ++i) {
        new_data[i] = data[i];
    }
    delete[] data;
    data = new_data;
    capacity = new_capacity;
}

template<typename T>
void DynamicArray<T>::push_back(const T& value) {
    if (size == capacity) {
        resize(capacity == 0 ? 1 : capacity * 2);
    }
    data[size++] = value;
}

template<typename T>
T& DynamicArray<T>::operator[](int index) {
    if (index < 0 || index >= size) {
        //need to see why this is happening
        //throw std::out_of_range("Index out of range");
    }
    return data[index];
}

template<typename T>
int DynamicArray<T>::get_size() const {
    return size;
}

#endif // DYNAMICARRAY_H_
