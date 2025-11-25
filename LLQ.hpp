#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLQ : public QueueInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLQ() = default;

    // Insertion
    void enqueue(const T& item) override{
		list.AddTail(item);
	}
    // Deletion
    T dequeue() override{
		if(!list.getHead()){ throw std::out_of_range("LLQ dequeue() on empty list"); }
		T retData = list.getHead()->data;
		list.RemoveHead();
		return retData;
	}
    // Access
    T peek() const override{
		if(!list.getHead()){ throw std::out_of_range("LLQ peek() on empty list"); }
		return list.getHead()->data;
	}
    // Getter
    std::size_t getSize() const noexcept override{ return list.getCount(); }

	// Print
	void PrintForward(){ list.PrintForward(); }
	void PrintReverse(){ list.PrintReverse(); }

	// Big Five
	// copy constructor
	LLQ(const LLQ& other){
		list = other.list;
	};
	// move constructor
	LLQ(LLQ&& other) noexcept{
		list = std::move(other.list);
	}
	// copy assignment
	LLQ& operator=(const LLQ& other){
		list = other.list;
		return *this;
	};
	// move assignment
	LLQ& operator=(LLQ&& other) noexcept{
		list = std::move(other.list);
		return *this;
	};
	// destructor
	~LLQ() = default;
};