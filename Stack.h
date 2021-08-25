//
// Created by raymo on 3/2/2021.
//
#ifndef STACK_H
#define STACK_H

#include <iostream>
#include "Node.h"

template<typename Object>
class Stack {
private:
    Node<Object>* top;

public:

    // Constructor
    Stack() {
        top = nullptr;  // By default the stack will be empty
    }

    // Destructor
    ~Stack() {
        while (top != nullptr) {
            pop();
        }
    }

    // Push an item onto the stack
    void push(Object item) {
        Node<Object>* newNode = new Node<Object>(item, top);
        top = newNode;
    }

    // Pop an item off the stack
    Object pop() {
        if (top == nullptr) {
            // The stack is empty so return a default object
            return Object();
        }
        Object item = top->getItem();
        Node<Object>* topCopy = top;
        top = top->getNext();
        delete topCopy;
        return item;
    }

    // Determine if an item is in the stack
    bool find(Object item) {
        Node<Object>* currentObject = top;
        while (currentObject != nullptr) {
            if (currentObject->getItem() == item) {
                return true;
            }
            currentObject = currentObject->getNext();
        }
        return false;
    }

    // Is the stack empty?
    bool isEmpty() {
        if (top == nullptr) {
            return true;
        }
        return false;
    }

    // Print the stack
    void printStack() {
        std::cout << "Top of stack" << std::endl;
        Node<Object>* currentObject = top;
        while (currentObject != nullptr) {
            std::cout << currentObject->getItem() << std::endl;
            currentObject = currentObject->getNext();
        }
        std::cout << "Bottom of stack" << std::endl;
    }

    void StackTest(){
        Stack<Object> testStack;

        testStack.push("hello");
        assert(testStack.find("hello"));

    }

};

#endif // STACK_H
