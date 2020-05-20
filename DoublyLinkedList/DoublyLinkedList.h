#pragma once
#include <vector>
#include <cstdlib>
#include <iostream>
#include <cassert>
// потом поменяем на шаблоны
using ValueType = double;

class DoublyLinkedList
{
	// класс узла списка
	// по своей сути, может содержать любые данные,
	// можно реализовать и ассоциативный массив, просто добавив 
	// поле с ключем в узел и, с учетом этого, поменять методы DoublyLinkedList
	// (доступ по ключу, поиск по ключу и т.д.)
	struct Node {
		Node(const ValueType& value, Node* next = nullptr, Node* previous = nullptr);
		~Node();

		void insertNext(const ValueType& value);
		void removeNext();

		ValueType value;
		Node* next;
		Node* previous;
	};

public:
	////
	DoublyLinkedList();
	DoublyLinkedList(const DoublyLinkedList& copyList);
	DoublyLinkedList& operator=(const DoublyLinkedList& copyList);

	DoublyLinkedList(DoublyLinkedList&& moveList) noexcept;
	DoublyLinkedList& operator=(DoublyLinkedList&& moveList) noexcept;

	~DoublyLinkedList();
	////
	// доступ к значению элемента по индексу
	ValueType& operator[](const size_t pos) const;
	// доступ к узлу по индексу
	DoublyLinkedList::Node* getNode(const size_t pos) const;
	void print();
	void printBackwards();
	// вставка элемента по индексу, сначала ищем, куда вставлять (О(n)), потом вставляем (O(1))
	void insert(const size_t pos, const ValueType& value);
	// вставка элемента после узла, (O(1))
	void insertAfterNode(Node* node, const ValueType& value);
	// вставка в конец (О(n))
	void pushBack(const ValueType& value);
	// вставка в начало (О(1))
	void pushFront(const ValueType& value);

	// удаление
	void remove(const size_t pos);
	void removeNextNode(Node* node);
	void removeFront();
	void removeBack();

	void Swap(Node* a, Node* b);
	// поиск, О(n)
	long long int findIndex(const ValueType& value) const;
	Node* findNode(const ValueType& value) const;

	// разворот списка
	void reverse();						// изменение текущего списка
	DoublyLinkedList reverse() const;			// полчение нового списка (для константных объектов)
	DoublyLinkedList getReverseList() const;	// чтобы неконстантный объект тоже мог возвращать новый развернутый список

	size_t size() const;
private:
	Node*	_lastNode;
	size_t	_size;
	Node* _firstNode;
	void forceNodeDelete(Node* node);
};

