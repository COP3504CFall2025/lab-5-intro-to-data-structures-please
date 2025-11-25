#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <utility>
#include <iostream>

template <typename T>
class ABDQ : public DequeInterface<T> {
private:
    T* data_;                 // underlying dynamic array
    std::size_t capacity_;    // total allocated capacity
    std::size_t size_;        // number of stored elements
    std::size_t front_;       // index of front element
    std::size_t back_;        // index after the last element (circular)

    static constexpr std::size_t SCALE_FACTOR = 2;

public:
    // Big 5
	//basic constructor
    ABDQ(): capacity_(4), size_(0), front_(0), back_(0), data_(new T[4]){};

	//parametrized constructor
    explicit ABDQ(std::size_t capacity): capacity_(capacity), size_(0), front_(0), back_(0), data_(new T[capacity]){};

	//copy constructor
    ABDQ(const ABDQ& other): capacity_(other.capacity_), size_(other.size_), front_(0), back_(other.size_), data_(new T[other.capacity_]){
		std::size_t currIndex = other.front_;
		for(std::size_t i = 0; i < other.size_; i++){
			this->data_[i] = other.data_[currIndex];
			currIndex = (currIndex + 1) % other.capacity_;
		};
	};

	//move contructor
    ABDQ(ABDQ&& other) noexcept: capacity_(other.capacity_), size_(other.size_), front_(other.front_), back_(other.back_), data_(other.data_){
		other.capacity_ = 0;
		other.size_ = 0;
		other.front_ = 0;
		other.back_ = 0;
		other.data_ = nullptr;
	};

	//copy assignment
    ABDQ& operator=(const ABDQ& other){
		if(this == &other){ return *this; }
		delete[] this->data_;
		this->data_ = new T[other.capacity_];
		this->capacity_ = other.capacity_;
		this->size_ = other.size_;
		this->front_ = 0;
		this->back_ = other.size_;
		std::size_t currIndex = other.front_;
		for(std::size_t i = 0; i < other.size_; i++){
			this->data_[i] = other.data_[currIndex];
			currIndex = (currIndex + 1) % other.capacity_;
		};
		return *this;
	};

	//move assignment
    ABDQ& operator=(ABDQ&& other) noexcept{
		if(this == &other){ return *this; }
		//copy over everything first
		delete[] this->data_;
		this->data_ = other.data_;
		this->capacity_ = other.capacity_;
		this->size_ = other.size_;
		this->front_ = other.front_;
		this->back_ = other.back_;
		//then handle the array thingy
		other.capacity_ = 0;
		other.size_ = 0;
		other.front_ = 0;
		other.back_ = 0;
		other.data_ = nullptr;
		return *this;
	};

    ~ABDQ() override{
		capacity_ = 0;
		size_ = 0;
		front_ = 0;
		back_ = 0;
		delete[] data_;
		data_ = nullptr;
	};

    // Insertion
    void pushFront(const T& item) override{
		//add this to front array and move all other pieces forward
		if(size_ == capacity_){ ensureCapacity(); }
		front_ = (front_ - 1 + capacity_) % capacity_; //add capacity to not go under 0
		data_[front_] = item;
		size_++;
	};
    void pushBack(const T& item) override{
		if(size_ == capacity_){ ensureCapacity(); }
		data_[back_] = item;
		back_ = (back_ + 1) % capacity_;
		size_++;
	};

    // Deletion
    T popFront() override{
		if(size_ == 0){ throw std::runtime_error("ABDQ popFront() on empty array"); }
		T retVar = data_[front_];
		front_ = (front_ + 1) % capacity_;
		size_--;
		shrinkIfNeeded();
		return retVar;
	};
    T popBack() override{
		if(size_ == 0){ throw std::runtime_error("ABDQ popBack() on empty array"); }
		T retVar = data_[(back_ - 1 + capacity_) % capacity_];
		back_ = (back_ - 1 + capacity_) % capacity_;
		size_--;
		shrinkIfNeeded(); //shrink if small enough
		return retVar;
	};

    // Access
    const T& front() const override{
		if(size_ == 0){ throw std::runtime_error("ABDQ front() on empty array"); }
		return data_[front_];
	};
    const T& back() const override{
		if(size_ == 0){ throw std::runtime_error("ABDQ back() on empty array"); }
		return data_[(back_ - 1 + capacity_) % capacity_];
	};

    // Getters
    std::size_t getSize() const noexcept override{ return size_; }

	//additional methods
	void ensureCapacity(){
		std::size_t double_capacity_ = capacity_ * 2;
		T* data_copy_ = new T[double_capacity_]; //same as shrink, lets reorganize
		std::size_t currIndex = front_;
		for(std::size_t i = 0; i < size_; i++){
			data_copy_[i] = data_[currIndex];
			currIndex = (currIndex + 1) % capacity_;
		};
		delete[] data_;
		data_ = data_copy_;
		capacity_ = double_capacity_;
		front_ = 0;
		back_ = size_;
	}; //Resizes to capacity_ * 2

	void shrinkIfNeeded(){
		std::size_t half_capacity_= (capacity_ + 1)/2;
		if(half_capacity_ < size_){ return; } //if half of capacity less than size, then shrink not needed
		//new array stored locally
		T* data_copy_ = new T[half_capacity_];
		std::size_t currIndex = front_;
		for(std::size_t i = 0; i < size_; i++){
			data_copy_[i] = data_[currIndex];
			currIndex = (currIndex + 1) % capacity_;
		};
		//now we remove our old data and bring in the new
		delete[] data_;
		data_ = data_copy_;
		capacity_ = half_capacity_;
		front_ = 0;
		back_ = size_;
	}; //Reduces to half when sparse

	void PrintForward(){
		std::size_t currIndex = front_;
		for(std::size_t i = 0; i < size_; i++){
			std::cout << data_[currIndex] << std::endl;
			currIndex = (currIndex + 1) % capacity_;
		};
	}; //Traverses queue order

	void PrintReverse(){
		std::size_t currIndex = (back_ - 1 + capacity_) % capacity_;
		for(std::size_t i = 0; i < size_; i++){
			std::cout << data_[currIndex] << std::endl;
			currIndex = (currIndex - 1 + capacity_) % capacity_;
		};
	}; //Traverses reverse order
};
