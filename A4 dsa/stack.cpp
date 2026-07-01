#include "Stack.h"
#include <iostream>

Stack::Stack() {
    top = nullptr;
}

Stack::~Stack() {
    while (!isEmpty())
        pop();
}

void Stack::push(char value) {
    SNode* temp = new SNode;
    temp->data = value;
    temp->next = top;
    top = temp;
}

char Stack::pop() {
    if (isEmpty())
        return '\0';

    SNode* temp = top;
    char value = temp->data;
    top = temp->next;
    delete temp;
    return value;
}

char Stack::peek() const {
    return isEmpty() ? '\0' : top->data;
}

bool Stack::isEmpty() const {
    return top == nullptr;
}
