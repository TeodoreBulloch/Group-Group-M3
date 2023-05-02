#include "Node.h"
#include <string>

//using 
using std:: string;

Node::Node(){
    // TODO
    
};

Node::Node(string id, string name, string descrption, Price price,  unsigned on_hand){
    this->data->id = id;
    this->data->description = descrption;
    this->data->price = price;
    this->data->on_hand = on_hand;

}
Node::~Node(){
    // TODO
    this->data = NULL;
    delete this->data;

    this->next = NULL;
    delete this->next;

};