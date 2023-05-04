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

void LinkedList::displayItems() {
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

LinkedList::~LinkedList() {
    Node* currNode = head;
    while (currNode != nullptr) {
        Node* nextNode = currNode->next;
        delete currNode;
        currNode = nextNode;
    }
}
