#include "Queue.h"

Queue::Queue() {
    front = rear = nullptr;
}

Queue::~Queue() {
    while (!isEmpty())
        dequeue();
}

void Queue::enqueue(string exp) {
    Node* temp = new Node(exp);

    if (isEmpty()) {
        front = rear = temp;
    } else {
        rear->next = temp;
        rear = temp;
    }
}

string Queue::dequeue() {
    if (isEmpty())
        return "";

    Node* temp = front;
    string value = temp->data;
    front = front->next;

    if (!front)
        rear = nullptr;

    delete temp;
    return value;
}

bool Queue::isEmpty() const {
    return front == nullptr;
}

void Queue::display() const {
    Node* temp = front;
    while (temp) {
        cout << temp->data << " | ";
        temp = temp->next;
    }
    cout << endl;
}

ostream& operator<<(ostream& out, const Queue& q) {
    Node* temp = q.front;
    while (temp) {
        out << temp->data << " ";
        temp = temp->next;
    }
    return out;
}

istream& operator>>(istream& in, Queue& q) {
    string exp;
    in >> exp;
    q.enqueue(exp);
    return in;
}
