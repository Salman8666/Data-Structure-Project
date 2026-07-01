#include<iostream>
#include "phone.h"
using namespace std;

int main(){
    PhoneDirectory directory;
    int choice;

    do{
        cout<<"\n====== PHONE DIRECTORY SYSTEM ======\n";
        cout<<"1. Add Contact"<<endl;
        cout<<"2. Search Contact"<<endl;
        cout<<"3. Update Contact"<<endl;
        cout<<"4. Delete Contact"<<endl;
        cout<<"5. Display All Contacts (Sorted)"<<endl;
        cout<<"6. Show Total Contacts"<<endl;
        cout<<"7. Exit"<<endl;


        cout<<"\nEnter your choice: ";
        cin>>choice;

        switch(choice){
            case 1:directory.addContact();
            break;
            case 2:directory.searchContact();
            break;
            case 3:directory.updateContact();
            break;
            case 4:directory.deleteContact();
            break;
            case 5:directory.displayContacts();
            break;
            case 6:directory.totalContacts();
            break;
            case 7:cout<<"Exiting system..."<<endl;
            break;
            default:cout<<" Invalid choice!"<<endl;
        }
    }while(choice!=7);

    return 0;
}
