#include <iostream>
#include <limits>
#include "shopping_list.h"

using namespace std;

void displayMainMenu() {
    cout<<endl<<"=== SHOPPING LIST MANAGEMENT SYSTEM ==="<<endl;
    cout<<"1. Insert Item"<<endl;
    cout<<"2. Remove Item"<<endl;
    cout<<"3. Update Item"<<endl;
    cout<<"4. Search Item"<<endl;
    cout<<"5. Display All Items"<<endl;
    cout<<"6. Count Total Items"<<endl;
    cout<<"7. Compute Total Cost"<<endl;
    cout<<"0. Exit"<<endl;
    cout<<"Enter your choice (0-7): ";
}

void displayInsertSubMenu() {
    cout<<endl<<"--- INSERT ITEM ---"<<endl;
    cout<<"1. Insert at Beginning"<<endl;
    cout<<"2. Insert at End"<<endl;
    cout<<"3. Insert at Specific Position"<<endl;
    cout<<"0. Back to Main Menu"<<endl;
    cout<<"Enter your choice (0-3): ";
}

void displayRemoveSubMenu() {
    cout<<endl<<"--- REMOVE ITEM ---"<<endl;
    cout<<"1. Remove by Name"<<endl;
    cout<<"2. Remove at Specific Position"<<endl;
    cout<<"0. Back to Main Menu"<<endl;
    cout<<"Enter your choice (0-2): ";
}

void displayUpdateSubMenu() {
    cout<<endl<<"--- UPDATE ITEM ---"<<endl;
    cout<<"1. Update Item Name"<<endl;
    cout<<"2. Update Item Quantity"<<endl;
    cout<<"3. Update Item Price"<<endl;
    cout<<"0. Back to Main Menu"<<endl;
    cout<<"Enter your choice (0-3): ";
}

void displaySearchSubMenu() {
    cout<<endl<<"--- SEARCH ITEM ---"<<endl;
    cout<<"1. Search by Name"<<endl;
    cout<<"2. Search by Price"<<endl;
    cout<<"0. Back to Main Menu"<<endl;
    cout<<"Enter your choice (0-2): ";
}

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
}

string getStringInput(const string& prompt) {
    string input;
    cout<<prompt;
    getline(cin,input);
    return input;
}

int getIntInput(const string& prompt) {
    int value;
    while(true) {
        cout<<prompt;
        cin>>value;
        if(cin.fail()) {
            cout<<"Error: Please enter a valid integer."<<endl;
            clearInputBuffer();
        } else {
            clearInputBuffer();
            break;
        }
    }
    return value;
}

double getDoubleInput(const string& prompt) {
    double value;
    while(true) {
        cout<<prompt;
        cin>>value;
        if(cin.fail()) {
            cout<<"Error: Please enter a valid number."<<endl;
            clearInputBuffer();
        } else {
            clearInputBuffer();
            break;
        }
    }
    return value;
}

void handleInsertOperation(ShoppingListInterface& shoppingList) {
    int subChoice;
    do {
        displayInsertSubMenu();
        cin>>subChoice;
        clearInputBuffer();
        
        if(subChoice==0) break;
        
        string name=getStringInput("Enter item name: ");
        int quantity=getIntInput("Enter quantity: ");
        double price=getDoubleInput("Enter unit price: Rs");
        
        switch(subChoice) {
            case 1:
                shoppingList.insertAtBeginning(name,quantity,price);
                break;
            case 2:
                shoppingList.insertAtEnd(name,quantity,price);
                break;
            case 3: {
                int position=getIntInput("Enter position (1-based): ");
                shoppingList.insertAtPosition(name,quantity,price,position);
                break;
            }
            default:
                cout<<"Error: Invalid choice. Please try again."<<endl;
        }
    } while(subChoice!=0);
}

void handleRemoveOperation(ShoppingListInterface& shoppingList) {
    int subChoice;
    do {
        displayRemoveSubMenu();
        cin>>subChoice;
        clearInputBuffer();
        
        if(subChoice==0) break;
        
        switch(subChoice) {
            case 1: {
                string name=getStringInput("Enter item name to remove: ");
                shoppingList.removeByName(name);
                break;
            }
            case 2: {
                int position=getIntInput("Enter position to remove (1-based): ");
                shoppingList.removeAtPosition(position);
                break;
            }
            default:
                cout<<"Error: Invalid choice. Please try again."<<endl;
        }
    } while(subChoice!=0);
}

void handleUpdateOperation(ShoppingListInterface& shoppingList) {
    int subChoice;
    do {
        displayUpdateSubMenu();
        cin>>subChoice;
        clearInputBuffer();
        
        if(subChoice==0) break;
        
        switch(subChoice) {
            case 1: {
                string oldName=getStringInput("Enter current item name: ");
                string newName=getStringInput("Enter new item name: ");
                shoppingList.updateItemName(oldName,newName);
                break;
            }
            case 2: {
                string name=getStringInput("Enter item name: ");
                int newQuantity=getIntInput("Enter new quantity: ");
                shoppingList.updateItemQuantity(name,newQuantity);
                break;
            }
            case 3: {
                string name=getStringInput("Enter item name: ");
                double newPrice=getDoubleInput("Enter new price: Rs");
                shoppingList.updateItemPrice(name,newPrice);
                break;
            }
            default:
                cout<<"Error: Invalid choice. Please try again."<<endl;
        }
    } while(subChoice!=0);
}

void handleSearchOperation(ShoppingListInterface& shoppingList) {
    int subChoice;
    do {
        displaySearchSubMenu();
        cin>>subChoice;
        clearInputBuffer();
        
        if(subChoice==0) break;
        
        switch(subChoice) {
            case 1: {
                string name=getStringInput("Enter item name to search: ");
                shoppingList.searchByName(name);
                break;
            }
            case 2: {
                double price=getDoubleInput("Enter price to search: Rs");
                shoppingList.searchByPrice(price);
                break;
            }
            default:
                cout<<"Error: Invalid choice. Please try again."<<endl;
        }
    } while(subChoice!=0);
}

int main() {
    SinglyLinkedShoppingList shoppingList;
    int choice;
    
    cout<<"Welcome to Shopping List Management System!"<<endl;
    
    do {
        displayMainMenu();
        cin>>choice;
        clearInputBuffer();
        
        switch(choice) {
            case 0:
                cout<<"Thank you for using Shopping List Management System. Goodbye!"<<endl;
                break;
            case 1:
                handleInsertOperation(shoppingList);
                break;
            case 2:
                handleRemoveOperation(shoppingList);
                break;
            case 3:
                handleUpdateOperation(shoppingList);
                break;
            case 4:
                handleSearchOperation(shoppingList);
                break;
            case 5:
                shoppingList.displayAll();
                break;
            case 6:
                cout<<"Total number of items: "<<shoppingList.countItems()<<endl;
                break;
            case 7:
                cout<<"Total cost of shopping list: Rs "<<fixed<<setprecision(2) 
                     <<shoppingList.computeTotalCost()<<endl;
                break;
            default:
                cout<<"Error: Invalid choice. Please enter a number between 0 and 7."<<endl;
        }
    } while(choice!=0);
    
    return 0;
}
