#include "LinkedList.h"
#include <iostream> // Add this include for cout
#include <iomanip> // Add this include for setw
#include <string> // Add this include for to_string

using std::cout;
using std::endl;
using std::setw;
using std::left;
using std::to_string;

LinkedList::LinkedList() {
    head = nullptr;
}

void LinkedList::appendNode(Node* node) {
    if (head == nullptr) {
        head = node;
    }
    else {
        Node* currNode = head;
        Node* prevNode = nullptr;

        // Access the name attribute through the data member of the Node class
        while (currNode != nullptr && currNode->data.name < node->data.name) {
            prevNode = currNode;
            currNode = currNode->next;
        }

        if (prevNode == nullptr) {
            node->next = head;
            head = node;
        }
        else {
            node->next = currNode;
            prevNode->next = node;
        }
    }
}

void LinkedList::displayItems() const {
    Node* currNode = head;

    const int idWidth = 5;
    const int nameWidth = 40;
    const int availableWidth = 9;
    const int priceWidth = 12;
    const int optionsWidth = 20;

    cout << "Items Menu" << endl;
    cout << "----------" << endl;
    cout << setw(idWidth) << left << "ID" << " | "
    << setw(nameWidth) << left << "Name" << " | "
    << setw(availableWidth) << left << "Available" << " | "
    << setw(priceWidth) << left << "Price" << " | "
    << setw(optionsWidth) << left << "Options" << endl;
    cout << "---------------------------------------------------------------------------------------" << endl;

    while (currNode != nullptr) {
        Stock& item = currNode->data;

        cout << setw(idWidth) << left << item.id << " | "
             << setw(nameWidth) << left << item.name << " | "
             << setw(availableWidth) << left << item.on_hand << " | "
             << "$ " << setw(priceWidth) << left << (to_string(item.price.dollars) + "." + to_string(item.price.cents)) << " | ";

        // Check if item_options is not nullptr before trying to access it
        if (item.item_options != nullptr) {
            Node* optionsNode = item.item_options->head;
            while (optionsNode != nullptr) {
                cout << optionsNode->data.name;
                optionsNode = optionsNode->next;
                if (optionsNode != nullptr) {
                    cout << ", ";
                }
            }
        }

        cout << endl;

        currNode = currNode->next;
    }
}

void LinkedList::displayItemsOG() const {
    Node* currNode = head;

    const int idWidth = 5;
    const int nameWidth = 40;
    const int availableWidth = 9;
    const int priceWidth = 12;

    cout << "Items Menu" << endl;
    cout << "----------" << endl;
    cout << setw(idWidth) << left << "ID" << " | "
    << setw(nameWidth) << left << "Name" << " | "
    << setw(availableWidth) << left << "Available" << " | "
    << setw(priceWidth) << left << "Price" << endl;
    cout << "-------------------------------------------------------------------" << endl;

    while (currNode != nullptr) {
        Stock& item = currNode->data;

        cout << setw(idWidth) << left << item.id << " | "
             << setw(nameWidth) << left << item.name << " | "
             << setw(availableWidth) << left << item.on_hand << " | "
             << "$ " << setw(priceWidth) << left << (to_string(item.price.dollars) + "." + to_string(item.price.cents)) << endl;

        currNode = currNode->next;
    }
}

void LinkedList::addItem(){
    // Generates the new node for the data to be stored in.
    Node* newNode = new Node;
    if (newNode == NULL) {exit(1);}
    newNode->next = NULL;

    // Variables.
    std::string newName;
    std::string newDesc;
    std::string newCost;
    std::string newDollars;
    std::string newCents;
    Price newPrice;

    // Finds the highest id in the list and increments by 1 for the new item.
    Node* temp = head;
    int highestId = 0;
    while (temp != NULL) {
        std::string currId = temp->data.id.substr(1); // Removes "I" prefix
        int currIdNum = std::stoi(currId);
        if (currIdNum > highestId) {
            highestId = currIdNum;
        }
        temp = temp->next;
    }

    int newIdNum = highestId + 1;
    std::string newId = "I" + std::string(4 - std::to_string(newIdNum).length(), '0') + std::to_string(newIdNum); // Pads with zeros
    newNode->data.id = newId;

    // can change to make it so that the 000's fit accordingly. eg 0009 -> 0010.
    std::cout << "The id of the new stock will be: " << newId << std::endl;
    std::cin.ignore();  // To ignore the newline character left in the input buffer by the previous input operation.

    std::cout << "Enter the item name: ";
    std::getline(std::cin, newName);
    
    std::cout << "\nEnter the item description: ";
    std::getline(std::cin, newDesc);

    std::string delimiter = ".";

    bool validPrice = false;
    while (!validPrice) {
        std::cout << "\nEnter the item price: ";
        std::cin >> newCost;

        size_t pos = newCost.find(delimiter);
        if (pos != std::string::npos && newCost.size() - pos == 3) {
            newDollars = newCost.substr(0, pos);
            newCents = newCost.substr(pos + 1, std::string::npos);
            if (!newDollars.empty() && !newCents.empty()) {
                newPrice.dollars = std::stoi(newDollars);
                newPrice.cents = std::stoi(newCents);
                validPrice = true;
            }
        }
        if (!validPrice) {
            std::cout << "Invalid price format. Please enter a price in the format 'dollars.cents: +0.00'.\n";
        }
    }

    // adds all the new node data.
    newNode->data.name = newName;
    newNode->data.description = newDesc;
    newNode->data.price = newPrice;
    newNode->data.on_hand = DEFAULT_STOCK_LEVEL;

    
    Node* currNode = head;
    if (currNode == NULL) {
        // If list is empty, make newNode the head
        head = newNode;
    } else {
        // Else, find the end of the list and append newNode
        while (currNode->next != NULL) {
            currNode = currNode->next;
        }
        currNode->next = newNode;
        std::cout << "The item \"" << newName << "\" has been successfully added to the stock.\n";
    }
}

void LinkedList::removeItem() {
    if (head != NULL){
        Node* currNode = head;

        std::string itemID;
        std::cout << "Enter the item id of the item to remove from the menu: ";
        std::cin >> itemID;

        if (head->data.id == itemID){
            head = head->next;
            printf("\"%s - %s - %s\"\n\n",currNode->data.id.c_str(), currNode->data.name.c_str(), currNode->data.description.c_str());
            delete currNode;
        } else {
            Node * prevNode = NULL;
            while (currNode != NULL && currNode->data.id != itemID) {
                prevNode = currNode;
                currNode = currNode->next;
            }
            if (currNode != NULL) {
                printf("\"%s - %s - %s\"\n\n",currNode->data.id.c_str(), currNode->data.name.c_str(), currNode->data.description.c_str());
                prevNode->next = currNode->next;
                delete currNode;
            }
            else {std::cout << "Item ID not found.\n\n";}
        }
    }

}

Node* LinkedList::findItem(const std::string& item_id) const {
    Node* currentNode = head;

    while (currentNode != nullptr) {
        if (currentNode->data.id == item_id) {
            return currentNode;
        }
        currentNode = currentNode->next;
    }

    return nullptr;
}

void LinkedList::saveStock(std::string stockFile) const{
    // get node head and start save values
    Node* currNode = head;
    std::ofstream MyFile(stockFile);
    while (currNode != nullptr) {
        Node* nextNode = currNode->next;
        //save data
        MyFile << currNode->data.id<<"|" << currNode->data.name<<"|"<<currNode->data.description<<"|"<<currNode->data.price.dollars<<"."<<currNode->data.price.cents<<"|" <<currNode->data.on_hand;

        // Save item options
        LinkedList* item_options = currNode->data.item_options;
        if (item_options != nullptr) {
            Node* optionNode = item_options->head;
            MyFile << "|"; // Start of the options field
            while (optionNode != nullptr) {
                MyFile << optionNode->data.name;
                if (optionNode->next != nullptr) {
                    MyFile << ","; // Separate options with commas
                }
                optionNode = optionNode->next;
            }
        }

        MyFile << "|" << std::endl; // End of the line
        //get next node head
        currNode = nextNode;
    }
}


 
void LinkedList::Reset() {
    Node* currNode = head;
    while (currNode != nullptr) {
        currNode->data.on_hand = DEFAULT_STOCK_LEVEL;
        currNode = currNode->next;
        
    }
    std::cout << "All stock has been reset to the default level of " << DEFAULT_STOCK_LEVEL << std::endl;
}

LinkedList::~LinkedList() {
    Node* currNode = head;
    while (currNode != nullptr) {
        Node* nextNode = currNode->next;
        delete currNode;
        currNode = nextNode;
    }
}
