#pragma once

#include <cstddef>
#include <stdexcept>
#include <iostream>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABS : public StackInterface<T> {
public:
    // Big 5 + Parameterized Constructor
    ABS(): capacity_(1), curr_size_(0), array_(new T[1]){};

    explicit ABS(const size_t capacity): capacity_(capacity), curr_size_(0), array_(new T[capacity]){};

    ABS(const ABS& other): capacity_(other.capacity_), curr_size_(other.curr_size_), array_(new T[capacity_]){
            for(size_t i = 0; i < curr_size_; i++){
                array_[i] = other.array_[i];
            }
    };

    ABS& operator=(const ABS& rhs){
        if(this == &rhs){ return *this; } //check for self assignment
        T* temp = new T[rhs.capacity_];
        for(size_t i = 0; i < rhs.curr_size_; i++){
            temp[i] = rhs.array_[i];
        }
        delete[] this->array_;
        this->array_ = temp;
        this->capacity_ = rhs.capacity_;
        this->curr_size_ = rhs.curr_size_;
        return *this;
    };

    ABS(ABS&& other) noexcept : capacity_(other.capacity_), curr_size_(other.curr_size_), array_(other.array_){
        other.capacity_ = 0;
        other.curr_size_ = 0;
        other.array_ = nullptr;
    };

    ABS& operator=(ABS&& rhs) noexcept{
        if(this == &rhs){ return *this; } //check for self
        //first we deal with our array
        delete[] this->array_;
        this->array_ = rhs.array_;
        rhs.array_ = nullptr;
        //then other stuff
        this->capacity_ = rhs.capacity_;
        this->curr_size_ = rhs.curr_size_;
        rhs.capacity_ = 0;
        rhs.curr_size_ = 0;
        return *this;
    };
    ~ABS() noexcept override{
        capacity_ = 0;
        curr_size_ = 0;
        delete[] array_;
        array_ = nullptr;
    };

    // Get the number of items in the ABS
    [[nodiscard]] size_t getSize() const noexcept override{ return curr_size_; }

    // Get the max size of the ABS
    [[nodiscard]] size_t getMaxCapacity() const noexcept{ return capacity_; }

    // Return underlying data for the stack
    [[nodiscard]] T* getData() const noexcept{ return array_; }

    // Push item onto the stack
    void push(const T& data) override{
        if(capacity_ == curr_size_){
            T* temp = new T[capacity_ * scale_factor_];
            for(size_t i = 0; i < capacity_; i++){
                temp[i] = array_[i];
            }
            delete[] array_;
            array_ = temp;
            capacity_ *= scale_factor_;
        };
        array_[curr_size_] = data;
        curr_size_++;
    }

    T peek() const override{
        if(curr_size_ == 0){ throw std::runtime_error("ABS peek() on empty array"); }
        return array_[curr_size_ - 1];
    }

    T pop() override{
        if(curr_size_ == 0){ throw std::runtime_error("ABS pop() on empty array"); }
        T temp = array_[curr_size_ - 1];
        curr_size_ -= 1;
        shrinkIfNeeded();
        return temp;
    }
    void shrinkIfNeeded(){
        std::size_t half_capacity_= (capacity_ + 1)/2;
        if(half_capacity_ <= curr_size_){ return; }
        T* temp = new T[half_capacity_];
        for(size_t i = 0; i < curr_size_; i++){
            temp[i] = array_[i];
        }
        delete[] array_;
        array_ = temp;
        capacity_ = half_capacity_;
    }; //Reduces to half when sparse

    void PrintForward(){
        for(size_t i = 0; i < curr_size_; i++){
            std::cout << array_[i] << std::endl;
        }
    }
    void PrintReverse(){
        for(size_t i = curr_size_; i > 0; i--){
            std::cout << array_[i - 1] << std::endl;
        }
    }

private:
    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;
};
