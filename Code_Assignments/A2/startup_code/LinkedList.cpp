#include "LinkedList.h"

LinkedList::LinkedList() {
   Node* head = nullptr;

   // TODO
}
void LinkedList::appendNode(Node * node){
    //if no node head make node head
    if (this->head == nullptr){
        this->head == node;
    }
    else{
        //search through Nodes till find last node
        Node * currNode = this->head;
        while (currNode != nullptr){
           currNode = (*currNode).next;
        }
        currNode = node;

    }
}

LinkedList::~LinkedList() {
    // TODO
}
