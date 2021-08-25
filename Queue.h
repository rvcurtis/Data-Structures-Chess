//
// Created by raymo on 3/1/2021.
//

#ifndef QUEUE_H
#define QUEUE_H
#include "Node.h"


template<typename Object>

// constructor
class Queue{
private:
    Node<Object>* front; // location of the front of the queue
    Node<Object>* back; // location of the back of the queue


public:
// default constructor
Queue(){
    // Queues are FIFO structures, so the last item in the queue is the first one out
    front = nullptr;
    back = front;
}

// Destructor
~Queue(){
    while(back != nullptr) // similar to stack, but now we want to say while the back != nullptr we pop, due to FIFO
        pop();
}

void push(Object item){
    if(back != nullptr){
        Node<Object>* newNode = new Node<Object>(item);
        back -> setNext(newNode);
        back = newNode;
    }
    else{
        Node<Object>* newNode = new Node<Object>(item);
        back = newNode;
        front = newNode;
    }
}

Object pop(){
    //similar implementation to the stack class
    if (back == nullptr) {
        // queue is empty, return the object
        return Object();
    }
    else {
        if (front == nullptr){
            Object item = back->getItem();
            back = nullptr;
            return item;
        }
        else {
            // copy of object
            Object item = back->getItem();
            Node<Object>* backCopy = front;
            // Update front node
            front = front->getNext();
            // use delete keyword to deallocate
            delete backCopy;

            return item;
        }
    }
}


void printQueue(){
        std::cout << "Start of Queue" << std::endl;
        Node<Object>* current = front;

        while(current!=nullptr){
            std::cout<< current-> getItem() << std::endl;
            current = current-> getNext();
        }
        std::cout<<"End of the queue" << std::endl;

}


bool find(Object item){
    Node<Object>* current = front;

    // while loop, if front != nullptr, search for next item
    while(current != nullptr){
        if(current->getItem() == item){
            //we have found the object
            return true;
        }
        current = current->getNext();
        }
        // the object was not in the queue
        return false;
}

bool isEmpty(){
        if (back == nullptr) {
            return true;
        }
        return false;
}

};



#endif //QUEUE_H
