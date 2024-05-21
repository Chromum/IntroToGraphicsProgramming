#pragma once
#include <iostream>
#include <vector>
#include "Sphere.h"
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
		if (current->next != nullptr)
		{
			// Search within children (if any)
			if (current->next->data->graph != nullptr) {
				SceneObject* childObject = GetObjectByName(desiredName, current->next->data->graph->head);
				if (childObject != nullptr) {
					return childObject; // Found in children
				}
			}
		}

		// Move to the next node
		return GetObjectByName(desiredName, current->next);
	}

	std::vector<GLObject*> GetAllObjects(Node* current) {
		std::vector<GLObject*> objects;

		while (current != nullptr) {
			if (current->data) {
				if (GLObject* q = static_cast<GLObject*>(current->data)) {
					objects.push_back(q);
				}

				if (current->data->graph) {
					std::vector<GLObject*> children = current->data->graph->GetAllObjects(current->data->graph->head->next);
					objects.insert(objects.end(), children.begin(), children.end());
				}
			}
			// Move to the next node
			current = current->next;
		}

		return objects;
	}

	void RenderAllObjects(Node* startPoint) {
		glPushMatrix();
		Node* current = startPoint;
		while (current != nullptr) {
			if (GLObject* obj = dynamic_cast<GLObject*>(current->data)) {
				// Save the current transformation matrix
				glPushMatrix();

				if (obj != nullptr)
					obj->render3D->RenderUpdate();

				// Restore the previous transformation matrix
				

				if (obj->graph != nullptr && obj->graph != this)
					obj->graph->RenderAllObjects(obj->graph->head->next);
				glPopMatrix();
			}

			if (Sphere* sphere = dynamic_cast<Sphere*>(current->data)) {
				sphere->Transform.Position = this->head->data->Transform.Position;
				//sphere->Draw(Vector3(0, 0, 0));
				// No need for glPopMatrix() here since no push was done
			}

			current = current->next;
		}
		glPopMatrix();
	}

};