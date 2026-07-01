#ifndef QUEUE_H
#define QUEUE_H

#include "Node.h"
#include <iostream>

class Queue {
private:
    Node* front;
    Node* rear;

public:
    Queue();
    ~Queue();

    void enqueue(string);
    string dequeue();
    bool isEmpty() const;
    void display() const;

    friend ostream& operator<<(ostream&, const Queue&);
    friend istream& operator>>(istream&, Queue&);
};

#endif
