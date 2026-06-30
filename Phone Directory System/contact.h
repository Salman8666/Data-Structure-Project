#ifndef CONTACT_H
#define CONTACT_H

#include <string>
using namespace std;

struct Contact {
    string name;
    string email;
    string phone;

    Contact* left;
    Contact* right;

    Contact(string n,string e,string p) {
        name=n;
        email=e;
        phone=p;
        left=right=nullptr;
    }
};

#endif
