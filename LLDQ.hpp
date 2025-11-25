#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <utility>



template <typename T>
class LLDQ : public DequeInterface<T> {
private:
    LinkedList<T> list;

public:
    // Constructor
    LLDQ() = default;

    // Core Insertion Operations
    void pushFront(const T& item) override{
		list.AddHead(item);
	}
    void pushBack(const T& item) override{
		list.AddTail(item);
	}

    // Core Removal Operations
    T popFront() override{
		if(!list.getHead()){ throw std::out_of_range("LLDQ popFront() on empty list"); }
		T retData =  list.getHead()->data;
		list.RemoveHead();
		return retData;
	}
    T popBack() override{
		if(!list.getTail()){ throw std::out_of_range("LLDQ popBack() on empty list"); }
		T retData =  list.getTail()->data;
		list.RemoveTail();
		return retData;
	}

    // Element Accessors
    const T& front() const override{
		if(!list.getHead()){ throw std::out_of_range("LLDQ front() on empty list"); }
		return list.getHead()->data;
	}
    const T& back() const override{
		if(!list.getTail()){ throw std::out_of_range("LLDQ back() on empty list"); }
		return list.getTail()->data;
	}

    // Getter
    std::size_t getSize() const noexcept override{ return list.getCount(); }

	// Printers
	void PrintForward(){ list.PrintForward(); }
	void PrintReverse(){ list.PrintReverse(); }

	// Big Five
	// copy constructor
	LLDQ(const LLDQ& other){
		list = other.list;
	};
	// move constructor
	LLDQ(LLDQ&& other) noexcept{
		list = std::move(other.list);
	}
	// copy assignment
	LLDQ& operator=(const LLDQ& other){
		list = other.list;
		return *this;
	};
	// move assignment
	LLDQ& operator=(LLDQ&& other) noexcept{
		list = std::move(other.list);
		return *this;
	};
	// destructor
	~LLDQ() = default;
};






