#ifndef NODE_H
#define NODE_H

template<typename Object>


class Node {
private:
    Object item;
    Node* next;

public:
    // Constructors
    Node(Object newItem) {
        item = newItem;
        next = nullptr;
    }

    Node(Object newItem, Node* nextNode) {
        item = newItem;
        next = nextNode;
    }

    // Setters
    void setItem(Object newItem) {
        item = newItem;
    }

    void setNext(Node* nextNode) {
        next = nextNode;
    }

    // Getters
    Object getItem() {
        return item;
    }

    Node* getNext() {
        return next;  // Returns a pointer
    }
};

#endif // NODE_H