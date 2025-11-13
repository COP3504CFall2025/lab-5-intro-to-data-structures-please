#pragma once
#include <iostream>
using namespace std;



template <typename T>
class LinkedList {
public:
	// Behaviors
	void printForward() const{ //print from head to tail
		if(!head) { return; } //if no head just return
		Node* curNode = head;
		while(curNode){ //if curnode is not null continue
			std::cout << curNode->data << std::endl;
			curNode = curNode->next;
		}
	}
	void printReverse() const{ //print from tail to head
		if(!tail) { return; }
		Node* curNode = tail;
		while(curNode){
			std::cout << curNode->data << std::endl;
			curNode = curNode->prev;
		}
	}

	// Accessors
	[[nodiscard]] unsigned int getCount() const { return count; }
	Node* getHead() { return head; }
	const Node* getHead() const { return head; }
	Node* getTail() { return tail; }
	const Node* getTail() const { return tail; }

	// Insertion
	void addHead(const T& data){
		//lets assign a new pointer node for data
		Node* n = new Node(data);
		//does head exist? if not then it is first element, so head and tail
		if(!head){ head = n; tail = n; count++; return; }
		//if head does exist, time for swapping things around
		head->prev = n;
		//now next of new node should point to head
		n->next = head; //no & bc head is a pointer already
		//and then change head pointer to new node
		head = n;
		//finally increment count
		count++;
	}
	void addTail(const T& data){
		//same thing as addHead
		Node* n = new Node(data);
		//if no tail exists
		if(!tail) { tail = n; head = n; count++; return;}
		//otherwise do shenanigans
		tail->next = n;
		n->prev = tail;
		tail = n;
		count++;
	}

	// Removal
	bool removeHead(){
		//is there a head?
		if(!head) { return false; }
		//is there a next ptr? if not then it is a one element list
		if(!head->next){ delete head; head = nullptr; tail = nullptr; count = 0; return true; }
		//okay there is a head and a next, lets store its next
		Node* tempNext = head->next;
		tempNext->prev = nullptr;
		//bye bye
		delete head;
		count--;
		//hi
		head = tempNext;
		return true;
	}
	bool removeTail(){
		//same as remove head
		if(!tail) { return false; }
		if(!tail->prev) { delete tail; tail = nullptr; head = nullptr; count = 0; return true; }
		Node* tempPrev = tail->prev;
		tempPrev->next = nullptr;
		delete tail;
		count--;
		tail = tempPrev;
		return true;
	}
	void Clear(){
		//delete all nodes, we can just cycle a removehead or removetail ngl
		while(head){ //🧠
			removeHead();
		}
	}

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept; //move assignment
	LinkedList<T>& operator=(const LinkedList<T>& rhs); //copy assignment

	// Construction/Destruction
	LinkedList(); //constructor
	LinkedList(const LinkedList<T>& list); //copy constructor
	LinkedList(LinkedList<T>&& other) noexcept; //move constrctor
	~LinkedList(); //destructor

private:
	// Stores pointers to first and last nodes and count
	Node* head;
	Node* tail;
	unsigned int count;

	//actual nodes
	struct Node {
		T data;
		Node* prev;
		Node* next;

		Node(const T& input) :
			data(input), prev(nullptr), next(nullptr) {}
	};
};


