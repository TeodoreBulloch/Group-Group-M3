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
        //Node* prevNode = nullptr;
        while (currNode->next != nullptr){
            currNode = currNode->next;
        }
        while (currNode->next == nullptr) {
            //prevNode = currNode;
            currNode->next = node;
        }

    }
}

void LinkedList::displayItems() const {
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

void LinkedList::addItem() const{
    // Generates the new node for the data to be stored in.
    Node* newNode = new Node;
    if (newNode == NULL) {exit(1);}
    newNode->next = NULL;

    // Goes to the tail of the LinkedList.
    Node* temp = head;
    int count = 1;
    while (temp != NULL) {
        count = count+1;
        temp = temp->next;
    }

    // generates the next available id for the new item.
    newNode->data.id = "I000" + std::to_string(count);
    // Variables.
    std::string newName;
    std::string newDesc;
    std::string newCost;
    std::string newDollars;
    std::string newCents;
    Price newPrice;

    // can change to make it so that the 000's fit accordingly. eg 0009 -> 0010.
    std::cout << "The id of the new stock will be: I000" << count << std::endl;
    std::cout << "Enter the item name: ";
    std::cin >> newName;
    
    std::cout << "\nEnter the item description: ";
    std::cin >> newDesc;

    std::cout << "\nEnter the item price: ";
    std::cin >> newCost;

    // seperates the dollars from the cents to add to Price class.
    std::string s = newCost;
    std::string delimiter = ".";

    newDollars = s.substr(0, s.find(delimiter));
    newPrice.dollars = std::stoi(newDollars);

    newCents = s.substr(s.find(delimiter) + 1, std::string::npos);
    newPrice.cents = std::stoi(newCents);

    // adds all the new node data.
    newNode->data.name = newName;
    newNode->data.description = newDesc;
    newNode->data.price = newPrice;
    newNode->data.on_hand = DEFAULT_STOCK_LEVEL;

    Node* currNode = head;
    while (currNode->next != NULL){
        currNode = currNode->next;
    } 
    currNode->next = newNode;

}

void LinkedList::removeItem() {
    if (head != NULL){
        Node* currNode = head;

        std::string itemID;
        std::cout << "Enter the item id of the item to remove from the menu: ";
        std::cin >> itemID;
        int headCount = 1;
        int count = 2;

        if (head->data.id == itemID){
            head = head->next;
            printf("\"%s - %s - %s\"\n\n",currNode->data.id.c_str(), currNode->data.name.c_str(), currNode->data.description.c_str());
            delete currNode;
            // updates head to be id0001
            head->data.id = "I0001";
            // updates other nodes to be sequencial.
            while (currNode->next != NULL){
                currNode = currNode->next;
                currNode->data.id = "I000" + std::to_string(headCount);
                headCount++;
            }

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

                if (currNode->next != NULL){
                    currNode = currNode->next;
                    currNode->data.id = itemID;

                    currNode = head;

                    while (currNode->next != NULL){
                        currNode = currNode->next;
                        currNode->data.id = "I000" + std::to_string(count);
                        count++;
                    }
                }
            }    
            else {std::cout << "Item ID not found.\n\n";}
        }
    }

}

Node* LinkedList::findItem(const std::string& item_id) const {
    Node* currentNode = head;

    while (currentNode != NULL && currentNode->data.id != item_id) {
        currentNode = currentNode->next;
    }
    if (currentNode != NULL){
        return currentNode;
    }
    else {
        std::cout << "Item ID not found.\n\n";
        return NULL;
    }
}



void LinkedList::saveStock() const{
    // get node head and start save values
    Node* currNode = head;
    std::ofstream MyFile("stock.dat");
    while (currNode != nullptr) {
        Node* nextNode = currNode->next;
        //save data
        MyFile << currNode->data.id<<"|" << currNode->data.name<<"|"<<currNode->data.description<<"|"<<currNode->data.price.dollars<<"."<<currNode->data.price.cents<<"|" <<currNode->data.on_hand<< std::endl;
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


