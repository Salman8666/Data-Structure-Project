#ifndef SHOPPING_LIST_H
#define SHOPPING_LIST_H

#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

class ShoppingListInterface {
public:
    virtual ~ShoppingListInterface()=default;
    
    virtual void insertAtBeginning(const string& name,int quantity,double price)=0;
    virtual void insertAtEnd(const string& name,int quantity,double price)=0;
    virtual bool insertAtPosition(const string& name,int quantity,double price,int position)=0;
    
    virtual bool removeByName(const string& name)=0;
    virtual bool removeAtPosition(int position)=0;
    
    virtual bool updateItemName(const string& oldName,const string& newName)=0;
    virtual bool updateItemQuantity(const string& name,int newQuantity)=0;
    virtual bool updateItemPrice(const string& name,double newPrice)=0;
    
    virtual void searchByName(const string& name)const=0;
    virtual void searchByPrice(double price)const=0;
    
    virtual void displayAll()const=0;
    virtual int countItems()const=0;
    virtual double computeTotalCost()const=0;
    
    virtual bool isEmpty()const=0;
};

class Node {
public:
    string itemName;
    int quantity;
    double unitPrice;
    Node* next;
    
    Node(const string& name,int qty,double price,Node* nextNode=nullptr)
        :itemName(name),quantity(qty),unitPrice(price),next(nextNode){}
};

class SinglyLinkedShoppingList : public ShoppingListInterface {
private:
    Node* head;
    int size;
    
    bool isValidPosition(int position)const{
        return position>=1&&position<=size;
    }
    
    bool isValidQuantity(int quantity)const{
        return quantity>=0;
    }
    
    bool isValidPrice(double price)const{
        return price>=0.0;
    }
    
    Node* getNodeAtPosition(int position)const{
        if(!isValidPosition(position))return nullptr;
        
        Node* current=head;
        for(int i=1;i<position&&current!=nullptr;i++){
            current=current->next;
        }
        return current;
    }

public:
    SinglyLinkedShoppingList();
    ~SinglyLinkedShoppingList();
    SinglyLinkedShoppingList(const SinglyLinkedShoppingList& other);
    SinglyLinkedShoppingList& operator=(const SinglyLinkedShoppingList& other);
    
    void insertAtBeginning(const string& name,int quantity,double price)override;
    void insertAtEnd(const string& name,int quantity,double price)override;
    bool insertAtPosition(const string& name,int quantity,double price,int position)override;
    
    bool removeByName(const string& name)override;
    bool removeAtPosition(int position)override;
    
    bool updateItemName(const string& oldName,const string& newName)override;
    bool updateItemQuantity(const string& name,int newQuantity)override;
    bool updateItemPrice(const string& name,double newPrice)override;
    
    void searchByName(const string& name)const override;
    void searchByPrice(double price)const override;
    
    void displayAll()const override;
    int countItems()const override;
    double computeTotalCost()const override;
    
    bool isEmpty()const override;
};

#endif