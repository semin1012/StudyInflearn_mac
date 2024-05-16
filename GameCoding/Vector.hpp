#pragma once
#include "assert.h"

template<typename T>
class Iterator
{
public:
    Iterator() : _ptr(nullptr) { }
    Iterator(T* ptr) : _ptr(ptr) { }
    
    // 전위형 ++(++it)
    Iterator& operator++()
    {
        _ptr++;
        return *this;
    }
    
    // 후위형 ++(it++)
    Iterator operator++(int)
    {
        Iterator temp = *this;
        _ptr++;
        return temp;
    }
    
    // it + 3 같은 것
    Iterator operator+(const int count)
    {
        Iterator temp = *this;
        temp._ptr += count;
        return temp;
    }
    
    bool operator==(const Iterator& other)
    {
        return _ptr == other._ptr;
    }
    
    bool operator!=(const Iterator& other)
    {
        return _ptr != other._ptr;
    }
    
    T& operator*()  // 포인터면 반환
    {
        return *_ptr;
    }
    
public:
    T* _ptr = nullptr;
};

template<typename T>
class Vector
{
public:
    using iterator = Iterator<T>;
    
    iterator begin() { return iterator(&_buffer[0]);}
    iterator end() { return begin() + _size; }
    
    explicit Vector()
    {
        
    }
    
//    explicit Vector(int capacity = 100) : _capacity(capacity)
//    {
//        _buffer = new T[capacity];
//    }

    ~Vector()
    {
        delete[] _buffer;
    }

    void clear()
    {
        // TODO
        if (_buffer)
        {
            delete[] _buffer;
            _buffer = new T[_capacity];
        }

        _size = 0;
    }

    void push_back(const T& data)
    {
        if (_size == _capacity)
        {
            int newCapacity = static_cast<int>(_capacity * 1.5);
            if (newCapacity == _capacity)
                newCapacity++;

            reserve(newCapacity);
        }
        
        _buffer[_size] = data;
        
        _size++;
    }
    
    void pop_back()
    {
        _size--;
    }

    T& back()
    {
        return _buffer[_size-1];
    }

    void resize(int size)
    {
        reserve(size);
        _size = size;
    }

    void reserve(int capacity)
    {
        if (_capacity >= capacity)
            return;

        _capacity = capacity;

        T* newData = new T[_capacity];

        for (int i = 0; i < _size; i++)
            newData[i] = _buffer[i];

        if (_buffer)
            delete[] _buffer;

        _buffer = newData;
    }

    T& operator[] (int index)
    {
        // TODO
        assert(index >= 0 && index <= _size);
        return _buffer[index];
    }

    int size() { return _size; }
    int capacity() { return _capacity; }

private:
    T* _buffer = nullptr;
    int        _size = 0;
    int        _capacity = 0;
};
