#include "LinkedList.h"

#include "LinkedList.h"

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


LinkedList::~LinkedList() {
    Node* currNode = head;
    while (currNode != nullptr) {
        Node* nextNode = currNode->next;
        delete currNode;
        currNode = nextNode;
    }
}
