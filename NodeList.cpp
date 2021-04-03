#include "NodeList.h"
#include <iostream>

NodeList::NodeList(){
    // TODO
    //Not initialising node pointer array properly

    //Node* nodes[NODE_LIST_ARRAY_MAX_SIZE];
    // Node** nodes = new Node*[NODE_LIST_ARRAY_MAX_SIZE];
    // int* length = new int(0);
    this->length = 0;
}

NodeList::~NodeList(){
    // TODO
    for (int i=0;i<this->length;i++){
        this->nodes[i]->~Node();
        
    }

}

//Refactor to become deep copy
NodeList::NodeList(NodeList& other){
    // TODO
    this->length = other.length;
    for (int i=0; i<other.length; i++){
        this->nodes[i] = other.nodes[i];
    }
    

}

int NodeList::getLength(){
    // TODO
    return length;
    //return -1;

}

void NodeList::addElement(Node* newPos){
    nodes[length] = newPos;
    length++;
    // TODO
}

Node* NodeList::getNode(int i){
    // TODO
    return nodes[i];
    //return nullptr;
}