#include "Node.h"
#include <string>

using std::string;

Node::Node() : next(nullptr) {
}

Node::Node(const string& id, const string& name, const string& description, const Price& price, unsigned on_hand) {
    this->data.id = id;
    this->data.name = name;
    this->data.description = description;
    this->data.price = price;
    this->data.on_hand = on_hand;
    this->next = nullptr;
    
}

Node::~Node() {
}
