#include <iostream>
#include <string>

using namespace std;

class ContactNode
{
public:
    ContactNode *connections[26];
    bool endOfContact;
    string phoneNumber;
    string email;
    string birthDate;
    string homeAddress;

    ContactNode()
    {
        for (int i = 0; i < 26; ++i)
        {
            connections[i] = nullptr;
        }
        endOfContact = false;
        phoneNumber = "";
        email = "";
        birthDate = "";
        homeAddress = "";
    }
};

class Directory
{
public:
    ContactNode *root;

    Directory()
    {
        root = new ContactNode();
    }

    void addContact(string fullName, string phoneNumber, string email = "", string birthDate = "", string homeAddress = "")
    {
        ContactNode *current = root;
        cout << "Adding contact: " << fullName << " (" << phoneNumber << ")" << endl;
        for (char c : fullName)
        {
            c = tolower(c);
            int index = c - 'a';
            if (current->connections[index] == nullptr)
            {
                current->connections[index] = new ContactNode();
            }
            current = current->connections[index];
        }
        current->endOfContact = true;
        current->phoneNumber = phoneNumber;
        current->email = email;
        current->birthDate = birthDate;
        current->homeAddress = homeAddress;
        cout << "Contact added!" << endl;
    }

    string findContact(string fullName)
    {
        ContactNode *current = root;
        for (char c : fullName)
        {
            int index = c - 'a';
            if (current->connections[index] == nullptr)
            {
                return ""; 
            }
            current = current->connections[index];
        }
        if (current->endOfContact)
        {
            return current->phoneNumber; 
        }
        else
        {
            return ""; 
        }
    }

    void displayContactsInfo(ContactNode *node, string fullName)
    {
        if (node->endOfContact)
        {   
            cout<<"Name: ";
            cout <<fullName <<endl<<"   Phone No: "<< node->phoneNumber << endl;
            cout << "   Email: " << node->email << endl;
            cout << "   Date of Birth: " << node->birthDate << endl;
            cout << "   Address: " << node->homeAddress << endl;
        }
        for (int i = 0; i < 26; ++i)
        {
            if (node->connections[i] != nullptr)
            {
                char c = 'a' + i;
                displayContactsInfo(node->connections[i], fullName + c);
            }
        }
    }

    void displayContacts()
    {
        displayContactsInfo(root, "");
    }
};

int main()
{
    int choice;
    Directory contactBook;

    do
    {
        cout << "Please Select Operation!w" << endl;
        cout << "1. Add a new contact" << endl;
        cout << "2. Display all contacts" << endl;
        cout << "3. Find a contact" << endl;
        cout << "4. Quit" << endl;

        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            string fullName, phoneNumber, email, birthDate, homeAddress;
            cout << "Enter full name: ";
            cin >> fullName;
            cout << "Enter phone number: ";
            cin >> phoneNumber;

            cout << "Enter email (or '-' to skip): ";
            cin >> email;
            if (email == "-")
            {
                email = ""; 
            }

            cout << "Enter date of birth (or '-' to skip): ";
            cin >> birthDate;
            if (birthDate == "-")
            {
                birthDate = ""; 
            }

            cout << "Enter address (or '-' to skip): ";
            cin >> homeAddress;
            if (homeAddress == "-")
            {
                homeAddress = ""; 
            }

            contactBook.addContact(fullName, phoneNumber, email, birthDate, homeAddress);
            cout << "Contact added!" << endl;
            break;
        }

        case 2:
        {
            cout << "Contacts:" << endl;
            contactBook.displayContacts();
            break;
        }
        case 3:
        {
            string fullName;
            cout << "Enter name to find: ";
            cin >> fullName;
            string phoneNumber = contactBook.findContact(fullName);
            if (!phoneNumber.empty())
            {
                cout << "Phone number of " << fullName << ": " << phoneNumber << endl;
            }
            else
            {
                cout << fullName << " not found in the contact book." << endl;
            }
            break;
        }
        case 4:
        {
            cout << "Exiting..." << endl;
            break;
        }
        default:
            cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 4);

    return 0;
}