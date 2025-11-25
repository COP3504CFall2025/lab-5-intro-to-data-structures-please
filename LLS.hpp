#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLS : public StackInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLS() = default;

    // Insertion
    void push(const T& item) override{
		list.AddHead(item);
	}

    // Deletion
    T pop() override{
		if(!list.getHead()){ throw std::out_of_range("LLS pop() on empty list"); }//if no head
		T retData =  list.getHead()->data;
		list.RemoveHead();
		return retData;
	}

    // Access
    T peek() const override{
		if(!list.getHead()){ throw std::out_of_range("LLS peek() on empty list"); }
		return list.getHead()->data;
	}

    //Getters
    std::size_t getSize() const noexcept override{ return list.getCount(); }

	//extra methods
	void PrintForward(){ list.PrintForward(); }
	void PrintReverse(){ list.PrintReverse(); }

	//big five

	//constructor copy
	LLS(const LLS& other){
		list = other.list;
	};
	//constructor move
	LLS(LLS&& other) noexcept{
		list = std::move(other.list);
	};
	//assignment copy
	LLS& operator=(const LLS& other){
		list = other.list;
		return *this;
	};
	//assignment move
	LLS& operator=(LLS&& other) noexcept{
		list = std::move(other.list);
		return *this;
	};
	//destructor
	~LLS() = default;
};