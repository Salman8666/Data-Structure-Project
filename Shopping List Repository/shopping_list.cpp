#include "shopping_list.h"

SinglyLinkedShoppingList::SinglyLinkedShoppingList():head(nullptr),size(0){}

SinglyLinkedShoppingList::~SinglyLinkedShoppingList(){
    Node* current=head;
    while(current!=nullptr){
        Node* next=current->next;
        delete current;
        current=next;
    }
    head=nullptr;
    size=0;
}

SinglyLinkedShoppingList::SinglyLinkedShoppingList(const SinglyLinkedShoppingList& other):head(nullptr),size(0){
    Node* current=other.head;
    while(current!=nullptr){
        insertAtEnd(current->itemName,current->quantity,current->unitPrice);
        current=current->next;
    }
}

SinglyLinkedShoppingList& SinglyLinkedShoppingList::operator=(const SinglyLinkedShoppingList& other){
    if(this!=&other){
        Node* current=head;
        while(current!=nullptr){
            Node* next=current->next;
            delete current;
            current=next;
        }
        head=nullptr;
        size=0;
        
        current=other.head;
        while(current!=nullptr){
            insertAtEnd(current->itemName,current->quantity,current->unitPrice);
            current=current->next;
        }
    }
    return*this;
}

void SinglyLinkedShoppingList::insertAtBeginning(const string& name,int quantity,double price){
    if(!isValidQuantity(quantity)||!isValidPrice(price)){
        cout<<"Error: Quantity and price must be non-negative."<<endl;
        return;
    }
    
    Node* newNode=new Node(name,quantity,price,head);
    head=newNode;
    size++;
    cout<<"Item '"<<name<<"' inserted at beginning successfully."<<endl;
}

void SinglyLinkedShoppingList::insertAtEnd(const string& name,int quantity,double price){
    if(!isValidQuantity(quantity)||!isValidPrice(price)){
        cout<<"Error: Quantity and price must be non-negative."<<endl;
        return;
    }
    
    Node* newNode=new Node(name,quantity,price);
    
    if(head==nullptr){
        head=newNode;
    }else{
        Node* current=head;
        while(current->next!=nullptr){
            current=current->next;
        }
        current->next=newNode;
    }
    size++;
    cout<<"Item '"<<name<<"' inserted at end successfully."<<endl;
}

bool SinglyLinkedShoppingList::insertAtPosition(const string& name,int quantity,double price,int position){
    if(!isValidQuantity(quantity)||!isValidPrice(price)){
        cout<<"Error: Quantity and price must be non-negative."<<endl;
        return false;
    }
    
    if(position==1){
        insertAtBeginning(name,quantity,price);
        return true;
    }
    
    if(position==size+1){
        insertAtEnd(name,quantity,price);
        return true;
    }
    
    if(!isValidPosition(position)&&position!=size+1){
        cout<<"Error: Invalid position. Must be between 1 and "<<size+1<<"."<<endl;
        return false;
    }
    
    Node* prev=getNodeAtPosition(position-1);
    if(prev!=nullptr){
        Node* newNode=new Node(name,quantity,price,prev->next);
        prev->next=newNode;
        size++;
        cout<<"Item '"<<name<<"' inserted at position "<<position<<" successfully."<<endl;
        return true;
    }
    
    return false;
}

bool SinglyLinkedShoppingList::removeByName(const string& name){
    if(head==nullptr){
        cout<<"Error: List is empty."<<endl;
        return false;
    }
    
    if(head->itemName==name){
        Node* temp=head;
        head=head->next;
        cout<<"Item '"<<temp->itemName<<"' removed successfully."<<endl;
        delete temp;
        size--;
        return true;
    }
    
    Node* current=head;
    while(current->next!=nullptr&&current->next->itemName!=name){
        current=current->next;
    }
    
    if(current->next!=nullptr&&current->next->itemName==name){
        Node* temp=current->next;
        current->next=temp->next;
        cout<<"Item '"<<temp->itemName<<"' removed successfully."<<endl;
        delete temp;
        size--;
        return true;
    }
    
    cout<<"Error: Item '"<<name<<"' not found."<<endl;
    return false;
}

bool SinglyLinkedShoppingList::removeAtPosition(int position){
    if(!isValidPosition(position)){
        cout<<"Error: Invalid position. Must be between 1 and "<<size<<"."<<endl;
        return false;
    }
    
    if(position==1){
        Node* temp=head;
        head=head->next;
        cout<<"Item '"<<temp->itemName<<"' removed from position "<<position<<" successfully."<<endl;
        delete temp;
        size--;
        return true;
    }
    
    Node* prev=getNodeAtPosition(position-1);
    if(prev!=nullptr&&prev->next!=nullptr){
        Node* temp=prev->next;
        prev->next=temp->next;
        cout<<"Item '"<<temp->itemName<<"' removed from position "<<position<<" successfully."<<endl;
        delete temp;
        size--;
        return true;
    }
    
    return false;
}

bool SinglyLinkedShoppingList::updateItemName(const string& oldName,const string& newName){
    Node* current=head;
    while(current!=nullptr){
        if(current->itemName==oldName){
            string oldNameCopy=current->itemName;
            current->itemName=newName;
            cout<<"Item name updated from '"<<oldNameCopy<<"' to '"<<newName<<"' successfully."<<endl;
            return true;
        }
        current=current->next;
    }
    
    cout<<"Error: Item '"<<oldName<<"' not found."<<endl;
    return false;
}

bool SinglyLinkedShoppingList::updateItemQuantity(const string& name,int newQuantity){
    if(!isValidQuantity(newQuantity)){
        cout<<"Error: Quantity must be non-negative."<<endl;
        return false;
    }
    
    Node* current=head;
    while(current!=nullptr){
        if(current->itemName==name){
            int oldQuantity=current->quantity;
            current->quantity=newQuantity;
            cout<<"Quantity for '"<<name<<"' updated from "<<oldQuantity<<" to "<<newQuantity<<" successfully."<<endl;
            return true;
        }
        current=current->next;
    }
    
    cout<<"Error: Item '"<<name<<"' not found."<<endl;
    return false;
}

bool SinglyLinkedShoppingList::updateItemPrice(const string& name,double newPrice){
    if(!isValidPrice(newPrice)){
        cout<<"Error: Price must be non-negative."<<endl;
        return false;
    }
    
    Node* current=head;
    while(current!=nullptr){
        if(current->itemName==name){
            double oldPrice=current->unitPrice;
            current->unitPrice=newPrice;
            cout<<"Price for '"<<name<<"' updated from Rs"<<fixed<<setprecision(2) 
                 <<oldPrice<<" to Rs"<<newPrice<<" successfully."<<endl;
            return true;
        }
        current=current->next;
    }
    
    cout<<"Error: Item '"<<name<<"' not found."<<endl;
    return false;
}

void SinglyLinkedShoppingList::searchByName(const string& name)const{
    Node* current=head;
    bool found=false;
    int index=1;
    
    cout<<endl<<"Search Results for '"<<name<<"':"<<endl;
    cout<<string(60,'-')<<endl;
    cout<<left<<setw(8)<<"Index"<<setw(20)<<"Item Name" 
          <<setw(12)<<"Quantity"<<setw(15)<<"Unit Price" 
          <<setw(15)<<"Line Total"<<endl;
    cout<<string(60,'-')<<endl;
    
    while(current!=nullptr){
        if(current->itemName==name){
            double lineTotal=current->quantity*current->unitPrice;
            cout<<left<<setw(8)<<index 
                  <<setw(20)<<current->itemName 
                  <<setw(12)<<current->quantity 
                  <<"Rs"<<setw(14)<<fixed<<setprecision(2)<<current->unitPrice
                  <<"Rs"<<setw(14)<<lineTotal<<endl;
            found=true;
        }
        current=current->next;
        index++;
    }
    
    if(!found){
        cout<<"No items found with name '"<<name<<"'."<<endl;
    }
    cout<<string(60,'-')<<endl;
}

void SinglyLinkedShoppingList::searchByPrice(double price)const{
    Node* current=head;
    bool found=false;
    int index=1;
    
    cout<<endl<<"Search Results for price Rs"<<fixed<<setprecision(2)<<price<<":"<<endl;
    cout<<string(60,'-')<<endl;
    cout<<left<<setw(8)<<"Index"<<setw(20)<<"Item Name" 
          <<setw(12)<<"Quantity"<<setw(15)<<"Unit Price" 
          <<setw(15)<<"Line Total"<<endl;
    cout<<string(60,'-')<<endl;
    
    while(current!=nullptr){
        if(current->unitPrice==price){
            double lineTotal=current->quantity*current->unitPrice;
            cout<<left<<setw(8)<<index 
                  <<setw(20)<<current->itemName 
                  <<setw(12)<<current->quantity 
                  <<"Rs"<<setw(14)<<fixed<<setprecision(2)<<current->unitPrice
                  <<"Rs"<<setw(14)<<lineTotal<<endl;
            found=true;
        }
        current=current->next;
        index++;
    }
    
    if(!found){
        cout<<"No items found with price Rs"<<fixed<<setprecision(2)<<price<<"."<<endl;
    }
    cout<<string(60,'-')<<endl;
}

void SinglyLinkedShoppingList::displayAll()const{
    if(head==nullptr){
        cout<<"Shopping list is empty."<<endl;
        return;
    }
    
    cout<<endl<<"Shopping List:"<<endl;
    cout<<string(60,'-')<<endl;
    cout<<left<<setw(8)<<"Index"<<setw(20)<<"Item Name" 
          <<setw(12)<<"Quantity"<<setw(15)<<"Unit Price" 
          <<setw(15)<<"Line Total"<<endl;
    cout<<string(60,'-')<<endl;
    
    Node* current=head;
    int index=1;
    double grandTotal=0.0;
    
    while(current!=nullptr){
        double lineTotal=current->quantity*current->unitPrice;
        grandTotal+=lineTotal;
        
        cout<<left<<setw(8)<<index 
              <<setw(20)<<current->itemName 
              <<setw(12)<<current->quantity 
              <<"Rs"<<setw(14)<<fixed<<setprecision(2)<<current->unitPrice
              <<"Rs"<<setw(14)<<lineTotal<<endl;
        
        current=current->next;
        index++;
    }
    
    cout<<string(60,'-')<<endl;
    cout<<right<<setw(55)<<"Grand Total: Rs"<<fixed<<setprecision(2)<<grandTotal<<endl;
    cout<<string(60,'-')<<endl;
}

int SinglyLinkedShoppingList::countItems()const{
    return size;
}

double SinglyLinkedShoppingList::computeTotalCost()const{
    double total=0.0;
    Node* current=head;
    
    while(current!=nullptr){
        total+=current->quantity*current->unitPrice;
        current=current->next;
    }
    
    return total;
}

bool SinglyLinkedShoppingList::isEmpty()const{
    return head==nullptr;
}
