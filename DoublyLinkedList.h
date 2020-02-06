#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H
#include "Node.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

using std::cout;
using std::endl;

//////////////////////////////////////////////////////////////////////////////
//                         class template definition                        //
//////////////////////////////////////////////////////////////////////////////

template<typename T>
class DoublyLinkedList {
public:
    /* uncomment the declarations as you implement them */
    DoublyLinkedList();
    DoublyLinkedList(T);
	void insert_back(T data);
    DoublyLinkedList(const DoublyLinkedList<T>&);
    DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>&);
    ~DoublyLinkedList();
    unsigned int size() const { return sz; }
    T& front();
    const T& front() const;
    T& back();
    const T& back() const;
    void push_back(T);
    void push_front(T);
    void pop_back();
    void pop_front();
    void erase(unsigned int);
    void insert(T data, unsigned int idx);
    void clear();
    std::string to_str() const;
	T& get(T index);
    // breaks encapsulation... gives operator== access to private data... not great approach, but makes the homework easier for you since we haven't talked about iterators :).
    template<typename U> friend bool operator==(DoublyLinkedList<U> const&, DoublyLinkedList<U> const&);
private:
    // do not change ordering.
    Node<T> *head;
    Node<T> *tail;
    unsigned int sz;
};

//////////////////////////////////////////////////////////////////////////////
//                       helper function declarations                       //
//////////////////////////////////////////////////////////////////////////////
template<typename T> std::ostream& operator<<(std::ostream &, DoublyLinkedList<T> const&);

template<typename T> bool operator==(DoublyLinkedList<T> const&, DoublyLinkedList<T> const&);

template<typename T> bool operator!=(DoublyLinkedList<T> const&, DoublyLinkedList<T> const&);

//////////////////////////////////////////////////////////////////////////////
//                     member template function definitions                 //
//////////////////////////////////////////////////////////////////////////////

template <typename T>
T& DoublyLinkedList<T>::get(T index) {
		
    if (index < 0 || index >= size()) {
        throw std::out_of_range(std::to_string(index));
    }

    T i = 0;
    Node<T>* current = head;
    while (current && i < index) {
        current = current->next;
        i++;
    }
    return current->data;
}



template<typename T>
DoublyLinkedList<T>::DoublyLinkedList() : head(nullptr), tail(nullptr), sz(0) { // intialization list 
	cout << "default constructor" << endl;
}

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(T data) : head(nullptr), tail(nullptr), sz(0) {
    Node<T>* current = new Node<T>(data);
	head = current;
	tail = current;
	sz++;
	cout << "parameterized constructor" << endl;
} 

template<typename T>
void DoublyLinkedList<T>::insert_back(T data) {

    Node<T>* node = new Node<T>(data);
	if (head) { // not empty
		tail->next = node;
		tail = node;
		sz++;
	} else { // empty
		head = node;
		tail = node;
		sz = 1;
	}
	cout << "insert back" << endl;
}

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& otherList) : head(nullptr), tail(nullptr), sz(0){
	
	Node<T>* curr = otherList.head;
	while(curr) {
		this->push_back(curr->data);
		curr = curr->next;
	}
	//curr->prev = otherList.tail;
	cout << "copy constructor" << endl;
}

template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList(){
	
	Node<T>* curr = head;
	while(curr){
		Node<T>* next = curr->next;
		delete curr;
		curr = next;
	}
	sz = 0;
	head = nullptr;
	tail = nullptr;
	
	cout << "destructor" << endl;
}

template <typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& otherList){
	
	if (this != &otherList){
		Node<T>* current = head;
		while(current){
			Node<T>* next = current->next;
			delete current;
			current = next;
		}
		sz = 0;
		head = nullptr;
		tail = nullptr;
	
		
		current = otherList.head;
		while(current) {
			this->push_back(current->data);
			current = current->next;
		}
	}

	cout << "copy assignment" << endl;
	return *this;
}

template <typename T>
T& DoublyLinkedList<T>::front(){
	cout << "front: " << head->data << endl;
    return head->data;
}

template <typename T>
const T& DoublyLinkedList<T>::front() const{
	cout << "const front: " << head-> data << endl;
    return head->data;
}

template <typename T>
T& DoublyLinkedList<T>::back() {
	cout << "back: " << tail->data << endl;
	return tail->data;
}

template <typename T>
const T& DoublyLinkedList<T>::back() const {
	cout << "const back: " << tail->data << endl;
	return tail->data;
}

template <typename T>
void DoublyLinkedList<T>::clear() {
	
	Node<T>* curr = head;
	while(curr){
		Node<T>* next = curr->next;
		delete curr;
		curr = next;
	}
	
	sz = 0;
	head = nullptr;
	tail = nullptr;
	
	cout << "clear" << endl;
}

template <typename T> 
void DoublyLinkedList<T>::push_back(T data) {
	Node<T>* node = new Node<T>(data);
    if (head) {
		node->prev = tail;
		tail->next = node;
		node->next = nullptr;
    } else {
        head = node;
    }
    tail = node;
    sz++;
	
	cout << "push_back" << endl;
}

template <typename T>
void DoublyLinkedList<T>::push_front(T data) {
	Node<T>* node = new Node<T>(data);
    if (head) {
		node->next = head;
		head->prev = node;
		node->prev = nullptr;
    } else {
        tail = node;
    }
    head = node;
    sz++;	
	
	cout << "push_front" << endl;
}

template <typename T>
void DoublyLinkedList<T>::pop_front(){
	if (sz == 0) {
        throw std::out_of_range("empty list");
    }
    if (head == tail) {
        // 1 node
        delete head;
        head = nullptr;
        tail = nullptr;
    } else {
        // > 1 node
        Node<T>* next = head->next;
        delete head;
        head = next;
		head->prev = nullptr;
    }
    sz--;
	
	cout << "pop_front" << endl;
}

template <typename T>
void DoublyLinkedList<T>::pop_back(){
	if (sz == 0) {
		throw std::out_of_range("empty list");
	}
	if (head == tail) {
		delete tail;
		head = nullptr;
		tail = nullptr;
	}
	else {
		cout << "entered the else block" << endl;
		Node<T>* curr = tail->prev;
		delete tail; 
		tail = curr;
		tail->next = nullptr;
	}
	sz--;
	cout << "pop_back" << endl;
}

template <typename T>
void DoublyLinkedList<T>::insert(T data, unsigned int idx) {
	if (idx < 0 || idx >= size()) {
        return;
    }
	
	//is it at the beginning of the list push_front
	if (idx == 0) {
		push_front(data);
		return;
	}
	//is it at the end of the list use push_back
	else if (idx == sz - 1) {
		Node<T>* pos = head;
		for (int k = 0; k < sz - 2; ++k) {
			pos = pos->next;	
		}
		Node<T>* node = new Node<T>(data);
		node->prev = pos;
		node->next = tail;
		pos->next = node;
		node->next->prev = node;
		sz++;

		return;
	}
	
	//inserting in the middle
	Node<T>* curr = head;
	//int count = 0;
	for (int i = 0; i < idx -1; ++i) {
		curr = curr->next;
		
	}
	
	Node<T>* node = new Node<T>(data);
	node->prev = curr;
	node->next = curr->next;
		
	curr->next = node;
	node->next->prev = node;
	
	
	sz++;
	cout << "insert" << endl;

}



template <typename T>
void DoublyLinkedList<T>::erase(unsigned int idx){
	
	if (idx < 0 || idx >= size()) {
        return;
    }
	
	
	//if int is zero do a pop_front()
	if (idx == 0) {
		pop_front();
		return;
	}
	else if (idx == sz - 1){
		pop_back();
		return;
	}
	
	//if somewhere in middle you got this:)
	Node<T>* temp = head;
	for (int i = 0; i < idx ; ++i)  {	
		temp = temp->next;
	}
	//Node<T>* next = temp->next->next;
	//delete temp->next;
	//temp->next= next;
	temp->prev->next = temp->next;
	temp->next->prev = temp->prev;
	delete temp;
	//temp = nullptr;

	sz--;
}


//attach node inserting to curr + 1 
//then change what curr is pointing to 

/* deep copy for copy constructor
-given a linked list create a new node
-have a list.get(i) or traverse through get the value and insert_back(curr.value or other.get(i))
-insert_back will take care of creating a new node and it will also update the pointer
- this inserts every node of the old into the new list
- make a getter function

keeping track of two pointers and data rather than one in a singly linked list

Node {
	T data;
	Node* next;
}

copy constructor:
LinkedList(const LinkedList& other) : head(nullptr) {
	Node* curr = other.head;
	while(curr) {
		insert_back(curr->data);
		curr = curr->next;
	}
}
*/

template<typename T>
std::string DoublyLinkedList<T>::to_str() const
{
    std::stringstream os;
    const Node<T> *curr = head;
    os << std::endl << std::setfill('-') << std::setw(80) << '-' << std::setfill(' ') << std::endl;
    os << "head: " << head << std::endl;
    os << "tail: " << tail << std::endl;
    os << "  sz: " << sz << std::endl;
    os << std::setw(16) << "node" << std::setw(16) << "node.prev" << std::setw(16) << "node.data" <<  std::setw(16) << "node.next" << std::endl;
    while (curr) {
        os << std::setw(16) << curr;
        os << std::setw(16) << curr->prev;
        os << std::setw(16) << curr->data;
        os << std::setw(16) << curr->next;
        os << std::endl;
        curr = curr->next;
    }
    os << std::setfill('-') << std::setw(80) << '-' << std::setfill(' ') << std::endl;
    return os.str();
}

//////////////////////////////////////////////////////////////////////////////
//                     helper template function definitions                 //
//////////////////////////////////////////////////////////////////////////////
template<typename U>
bool operator==(DoublyLinkedList<U> const& lhs, DoublyLinkedList<U> const& rhs)
{
    // getting you started on this once... definition for this overloaded operator will go here.
	if (rhs.sz != lhs.sz) {
		return false;
	}
	Node<U>* curr = rhs.head;
	Node<U>* temp = lhs.head;
	int count = 0;
	while(curr){
		if (curr->data == temp->data){
			count++;
		}
		curr = curr->next;
		temp = temp->next;
	}
	if (count == rhs.sz)
		return true;
	return false;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, DoublyLinkedList<T> const& rhs)
{
    os << rhs.to_str();
    return os;
}

template<typename T>
std::ostream operator<<(std::ostream& os, Node<T> const& rhs){
	
	os << rhs.data << endl;
	return os;
}

template<typename T> 
bool operator!=(DoublyLinkedList<T> const& rhs, DoublyLinkedList<T> const& lhs) {
	
	if (rhs.sz != lhs.sz){
		return false;
	}
	
	Node<T>* curr = rhs.head;
	Node<T>* temp = lhs.head;
	int count = 0;
	while(curr){
		if (curr.data != temp.data){
			count++;
		}
		curr = curr->next;
		temp = temp->next;
	}
	if (count == rhs.sz)
		return true;
	return false;
}


#endif
