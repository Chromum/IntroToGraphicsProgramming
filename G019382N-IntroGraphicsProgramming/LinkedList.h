#pragma once
#include "GLObject.h"
#include <iostream>


struct Node {
	//Start Node
	Node(GLObject* object)
	{
		this->data = object;
	}
	//Adding to end
	Node(Node* last, GLObject* data)
	{
		this->next = nullptr;
		this->last = last;
		this->data = data;

		last->next = this;
	}
	//Implicing within
	Node(Node* last, Node* next, GLObject* data)
	{
		last->next = this;
		next->last = this;

		this->next = next;
		this->last = last;
		this->data = data;
	}

	~Node() 
	{
		
	}
	GLObject* data = nullptr;
	Node* next = nullptr;
	Node* last = nullptr;
};

class LinkedList {
	Node* head;

	LinkedList(GLObject* headObject)
	{
		head = new Node(headObject);
	}

	void AddAtBegining(GLObject* object) {
		Node* node = new Node(object);
		head->last = node;
		node->next = head;
	}

	void AddNodeToEnd(GLObject* object)
	{
		Node* i = head;
		while (i != nullptr)
		{
			i = i->next;
		}

		Node* newNode = new Node(i, object);
	}

	void AddNodeAtIndex(GLObject* object, int desiredIndex)
	{
		int index = 0;
		Node* currNode = head;

		while (index < desiredIndex || currNode == nullptr)
		{
			index++;
			currNode = currNode->next;
		}

		if (desiredIndex == index)
		{
			Node* newNode = new Node(currNode, currNode->next, object);
		}
		else {
			std::cout << "ERROR";
			return;
		}

	}

	void AddNodeAtNodeReference(GLObject* object, Node* desiredNode)
	{
		Node* currNode = head;

		while (currNode != desiredNode || currNode == nullptr)
		{
			currNode = currNode->next;
		}

		if (currNode == nullptr)
		{
			std::cout << "ERROR";
			return;
		}

		Node* newNode = new Node(currNode, currNode->next, object);
	}

	void RemoveNodeFromEnd()
	{
		Node* node = head;

		while (node->last != nullptr)
		{
			node = node->last;
		}

		node->last->next = nullptr;

		delete(node);
	}

	void RemoveNodeByIndex(int desiredIndex)
	{
		int index = 0;
		Node* currNode = head;

		while (index < desiredIndex || currNode == nullptr)
		{
			index++;
			currNode = currNode->next;
		}

		if (desiredIndex == index)
		{
			currNode->last->next = currNode->next;
			currNode->next->last = currNode->last;
			delete(currNode);
		}
		else 
		{
			std::cout << "ERROR";
			return;
		}
	}

	void RemoveNodeAtNodeReference(Node* desiredNode)
	{
		Node* currNode = head;

		while (currNode != desiredNode || currNode == nullptr)
		{
			currNode = currNode->next;
		}

		if (currNode == nullptr)
		{
			std::cout << "ERROR";
			return;
		}

	
		currNode->last->next = currNode->next;
		currNode->next->last = currNode->last;
		delete(currNode);
	}

	Node* GetNodeByIndex(int desiredIndex)
	{
		int index = 0;
		Node* node = head;

		while (desiredIndex < index || node != nullptr)
		{
			node = node->next;
			index++;
		}

		return node;
	}

	void DrawNodes(Node* node) {
		
		if (node->data->render3D != nullptr)
			node->data->render3D->RenderUpdate();

		if (node->data->graph != nullptr)
			DrawNodes(node->data->graph->head);

		if (node->next != nullptr) DrawNodes(node->next);
	}
};