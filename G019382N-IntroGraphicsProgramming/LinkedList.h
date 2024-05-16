#pragma once
#include <iostream>
#include <vector>
//#include "SceneObject.h"
#include "GLObject.h"

struct Node {
	//Start Node
	Node(SceneObject* object)
	{
		this->data = object;
	}
	//Adding to end
	Node(Node* last, SceneObject* data)
	{
		this->next = nullptr;
		this->last = last;
		this->data = data;

		last->next = this;
	}
	//Implicing within
	Node(Node* last, Node* next, SceneObject* data)
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
	SceneObject* data = nullptr;
	Node* next = nullptr;
	Node* last = nullptr;
};

class LinkedList {
public:
	Node* head;

	LinkedList(SceneObject* headObject)
	{
		head = new Node(headObject);
	}

	void AddAtBegining(SceneObject* object) {
		Node* node = new Node(object);
		head->last = node;
		node->next = head;
	}

	void AddNodeToEnd(SceneObject* object)
	{
		Node* i = head;
		while (i->next != nullptr)
		{
			i = i->next;
		}

		Node* newNode = new Node(i, object);
	}

	void AddNodeAtIndex(SceneObject* object, int desiredIndex)
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

	void AddNodeAtNodeReference(SceneObject* object, Node* desiredNode)
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

	SceneObject* GetObjectByName(const std::string& desiredName, Node* current) {
		if (current == nullptr) {
			// Base case: Reached the end of the list, object not found
			return nullptr;
		}

		if (current->data->name == desiredName) {
			// Found the object with the specified name
			return current->data;
		}

		// Search within children (if any)
		if (current->next->data->graph != nullptr) {
			SceneObject* childObject = GetObjectByName(desiredName, current->next->data->graph->head);
			if (childObject != nullptr) {
				return childObject; // Found in children
			}
		}

		// Move to the next node
		return GetObjectByName(desiredName, current->next);
	}

	std::vector<GLObject*> GetAllObjects(Node* current)
	{
		std::vector<GLObject*> objects = std::vector<GLObject*>();

		if (current == nullptr) {
			// Base case: Reached the end of the list, object not found
			return objects;
		}

		if (GLObject* q = dynamic_cast<GLObject*>(current->data)) {
			// Found the object with the specified name
			objects.push_back(q);
		}

		// Search within children (if any)
		if (current->next != nullptr) {
			if (current->next->data->graph != nullptr)
			{
				std::vector<GLObject*> toCombine = GetAllObjects(current->next->data->graph->head);
				objects.insert(objects.end(), toCombine.begin(), toCombine.end());
			}
			
		}

		// Move to the next node
		std::vector<GLObject*> toCombine = GetAllObjects(current->next);
		objects.insert(objects.end(), toCombine.begin(), toCombine.end());
	}




	void UpdateNodes(Node* node) {
		std::vector<GLObject*> all = this->GetAllObjects(head);

		for (size_t i = 0; i < all.size(); i++)
		{
			all[i]->Update();
		}
	}
};