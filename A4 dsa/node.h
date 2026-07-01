#ifndef NODE_H
#define NODE_H

#include <string>
using namespace std;

class Node {
public:
    string data;
    Node* next;

    Node(string d = "");
};

#endif
