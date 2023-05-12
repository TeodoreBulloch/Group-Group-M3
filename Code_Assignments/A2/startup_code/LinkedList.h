#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Node.h"
#include <string> 


class LinkedList
{
public:
    LinkedList();
    ~LinkedList();


    // more functions to be added perhaps...
    
    void appendNode(Node * node);
    void displayItems() const; 
    Node* findItem(const std::string& item_id) const; // Add the std namespace before string
    void saveStock() const;
    void addItem() const;
    void removeItem();
    void Reset();
    void sortItems();

private:
    // the beginning of the list
    Node* head;
    
    // how many nodes are there in the list?
    unsigned count;
};

#endif  // LINKEDLIST_H


