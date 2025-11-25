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
		list.addTail(item);
	}
    // Deletion
    T dequeue() override{
		if(!list.getHead()){ throw std::runtime_error("LLQ dequeue() on empty list"); }
		T retData = list.getHead()->data;
		list.removeHead();
		return retData;
	}
    // Access
    T peek() const override{
		if(!list.getHead()){ throw std::runtime_error("LLQ peek() on empty list"); }
		return list.getHead()->data;
	}
    // Getter
    std::size_t getSize() const noexcept override{ return list.getCount(); }

	// Print
	void printForward(){ list.printForward(); }
	void printReverse(){ list.printReverse(); }

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