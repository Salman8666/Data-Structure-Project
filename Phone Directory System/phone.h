#ifndef PHONEDIRECTORY_H
#define PHONEDIRECTORY_H

#include<iostream>
#include"contact.h"
using namespace std;

class PhoneDirectory{
private:
    Contact* root;
    int count;

    Contact* insert(Contact* node,string name,string email,string phone){
        if(!node){
            count++;
            return new Contact(name,email,phone);
        }

        if(name<node->name)
            node->left=insert(node->left,name,email,phone);
        else if(name>node->name)
            node->right=insert(node->right,name,email,phone);
        else
            cout<<" Duplicate contact not allowed!\n";

        return node;
    }

    Contact* search(Contact* node,string name){
        if(!node||node->name==name)
            return node;

        if(name<node->name)
            return search(node->left,name);

        return search(node->right,name);
    }

    Contact* findMin(Contact* node){
        while(node&&node->left)
            node=node->left;
        return node;
    }

    Contact* deleteNode(Contact* node,string name){
        if(!node) return node;

        if(name<node->name)
            node->left=deleteNode(node->left,name);
        else if(name>node->name)
            node->right=deleteNode(node->right,name);
        else{
            count--;

            if(!node->left){
                Contact* temp=node->right;
                delete node;
                return temp;
            }
            if(!node->right){
                Contact* temp=node->left;
                delete node;
                return temp;
            }

            Contact* temp=findMin(node->right);
            node->name=temp->name;
            node->email=temp->email;
            node->phone=temp->phone;
            node->right=deleteNode(node->right,temp->name);
        }
        return node;
    }

    void inorder(Contact* node){
        if(!node) return;
        inorder(node->left);
        cout<<"Name: "<<node->name
            <<", Email: "<<node->email
            <<", Phone: "<<node->phone<<endl;
        inorder(node->right);
    }

public:
    PhoneDirectory(){
        root=nullptr;
        count=0;
    }

    void addContact(){
        string name,email,phone;
        cout<<"Enter Name: ";
        cin>>name;
        cout<<"Enter Email: ";
        cin>>email;
        cout<<"Enter Phone: ";
        cin>>phone;
        root=insert(root,name,email,phone);
    }

    void searchContact(){
        string name;
        cout<<"Enter name to search: ";
        cin>>name;
        Contact* result=search(root,name);

        if(result)
            cout<<"✔ Found -> Email: "<<result->email
                <<", Phone: "<<result->phone<<endl;
        else
            cout<<" Contact not found!\n";
    }

    void updateContact(){
        string name;
        cout<<"Enter name to update: ";
        cin>>name;

        Contact* node=search(root,name);
        if(!node){
            cout<<"Contact not found!"<<endl;;
            return;
        }

        cout<<"Enter new Email: ";
        cin>>node->email;
        cout<<"Enter new Phone: ";
        cin>>node->phone;
        cout<<"✔ Contact updated successfully!\n";
    }

    void deleteContact(){
        string name;
        cout<<"Enter name to delete: ";
        cin>>name;
        root=deleteNode(root,name);
    }

    void displayContacts(){
        if(!root){
            cout<<"Directory is empty.\n";
            return;
        }
        inorder(root);
    }

    void totalContacts(){
        cout<<"Total Contacts: "<<count<<endl;
    }
};

#endif
