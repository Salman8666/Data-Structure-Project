#ifndef STACK_H
#define STACK_H

#include <string>
using namespace std;

class Stack {
private:
    struct SNode {
        char data;
        SNode* next;
    };
    SNode* top;

public:
    Stack();
    ~Stack();

    void push(char);
    char pop();
    char peek() const;
    bool isEmpty() const;
};

#endif
