#include "NodeList.h"
#include <iostream>

NodeList::NodeList(){
    // TODO
    //Not initialising node pointer array properly

    this->length = 0;
}

NodeList::~NodeList(){
    // TODO
    for (int i=0;i<this->length;i++){
        delete nodes[i];
    }

    // for (int i=0;i<this->length;i++){
    //     if(this->nodes[i] == nullptr)
    //     {
    //         delete this->nodes[i];
    //     }
    // }

    // delete[] this->nodes;

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

}

void NodeList::addElement(Node* newPos){
    nodes[length] = newPos;
    length++;
    // TODO
}

Node* NodeList::getNode(int i){
    // TODO
    return nodes[i];
}