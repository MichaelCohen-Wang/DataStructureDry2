#ifndef DYNAMICARRAY_H_
#define DYNAMICARRAY_H_

#include <stdexcept>
#include <memory>
#include "PrimeHelper.h"

template<typename T>
class DynamicArray {
private:
    std::unique_ptr<T[]> data;
    int capacity;
    int size;

    void copy_from(const DynamicArray& other); // Helper function for copy constructor and assignment

public:
    DynamicArray();
    explicit DynamicArray(int initial_capacity);
    DynamicArray(const DynamicArray& other); // Copy constructor
    DynamicArray& operator=(const DynamicArray& other); // Copy assignment operator
    ~DynamicArray();

    void push_back(T value);
    T& operator[](int index);
    const T& operator[](int index) const;
    int get_size() const;

    void resize(int new_capacity);
};

template<typename T>
void DynamicArray<T>::copy_from(const DynamicArray& other) {
    capacity = other.capacity;
    size = other.size;
    data = std::unique_ptr<T[]>(new T[capacity]);
    for (int i = 0; i < size; ++i) {
        data[i] = std::move(other.data[i]);
    }
}

template<typename T>
DynamicArray<T>::DynamicArray() : data(nullptr), capacity(0), size(0) {}

template<typename T>
DynamicArray<T>::DynamicArray(int initial_capacity) : capacity(initial_capacity), size(0) {
    data = std::unique_ptr<T[]>(new T[capacity]);
}

template<typename T>
DynamicArray<T>::DynamicArray(const DynamicArray& other) {
    copy_from(other);
}

template<typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray& other) {
    if (this != &other) {
        copy_from(other);
    }
    return *this;
}

template<typename T>
DynamicArray<T>::~DynamicArray() {
    // Unique_ptr automatically cleans up the memory
}

template<typename T>
void DynamicArray<T>::resize(int new_capacity) {
    new_capacity = PrimeHelper::next_prime(new_capacity);
    std::unique_ptr<T[]> new_data(new T[new_capacity]);
    for (int i = 0; i < size; ++i) {
        new_data[i] = std::move(data[i]);
    }
    data = std::move(new_data);
    capacity = new_capacity;
}

template<typename T>
void DynamicArray<T>::push_back(T value) {
    if (size == capacity) {
        resize(capacity == 0 ? 1 : capacity * 2);
    }
    data[size++] = std::move(value);
}

template<typename T>
T& DynamicArray<T>::operator[](int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

template<typename T>
const T& DynamicArray<T>::operator[](int index) const {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

template<typename T>
int DynamicArray<T>::get_size() const {
    return size;
}

#endif // DYNAMICARRAY_H_
