#ifndef LINKEDLISTS_H
#define LINKEDLISTS_H

#include <iostream>
using namespace std;

template<class T>
class Node {
  public:
    T data;
    Node *next;

    Node() {
        data = NULL;
        next = NULL;
    }

    Node(T data) {
        this->data = data;
        this->next = NULL;
    }
};

template<class T>
class Linkedlist {
    Node<T> *head;
    Node<T> *tail;

  public:
    // Default constructor
    Linkedlist() {
        head = NULL;
        tail = NULL;
    }

    void insertAtHead(T data) {

        // Create the new Node
        Node<T> *newNode = new Node<T>(data);
        if (head == NULL) {
            head = newNode;
            return;
        }
        newNode->next = this->head;
        this->head = newNode;
        
    }
    
    void insertAtTail(T data) {
        Node<T> *newNode = new Node<T>(data);
        // Assign to head of the list is empty
        if (head == NULL) {
            head = tail = newNode;
            return;
        }
		tail->next = newNode;
		tail = newNode;
		newNode->next = NULL;
        
    }
    void print() {
        Node<T> *temp = head;

        // Check for empty list
        if (head == NULL) {
            cout << "List empty" << endl;
            return;
        }

        // Traverse the list
        while (temp != NULL) {
            cout << temp->data << " ";
            temp = temp->next;
        }
    }
    
    Node<T> *getNode(){
    	return head;
	} 
};

#endif