#pragma once
#include<iostream>
#include "NodeList.h"

class NodeList
{
	class Node
	{
		friend class NodeList;
		int data;
		//int lastParent;
		Node* next;
	public:
		Node(int dataValue = -1, Node* nextNode = nullptr) : data(dataValue), next(nextNode) {}
	};
	Node* head;
	Node* tail;

public:

	NodeList() : head(nullptr), tail(nullptr) {}

	~NodeList()
	{
		Node* current = head;
		while (current != nullptr)
		{
			Node* temp = current;
			current = current->next;
			delete temp;
		}
	}

	void addNodeToEnd(int dataValue)
	{
		Node* newNode = new Node(dataValue, nullptr);
		if (tail)
		{
			tail->next = newNode;
		}
		else
		{
			head = newNode;
		}
		tail = newNode;
	}

	bool contains(int dataValue) const
	{
		bool returnValue = false;
		Node* current = head;
		while (current != nullptr && !returnValue)
		{
			returnValue = current->data == dataValue;
			current = current->next;
		}
		return returnValue;
	}

	void printList() const
	{
		Node* current = head;
		while (current != nullptr) {
			std::cout << current->data << " -> ";
			current = current->next;
		}
		std::cout << "nullptr" << std::endl;
	}
};


int main() {
	NodeList list;

	list.addNodeToEnd(10);
	list.addNodeToEnd(20);
	list.addNodeToEnd(30);

	list.printList();

	std::cout << "Contains 20? " << (list.contains(20) ? "Yes" : "No") << std::endl;
	std::cout << "Contains 40? " << (list.contains(40) ? "Yes" : "No") << std::endl;

	return 0;
}