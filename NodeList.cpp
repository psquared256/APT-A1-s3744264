#include "NodeList.h"
#include <iostream>

NodeList::NodeList(){
    // TODO

    this->length = 0;
}

NodeList::~NodeList(){
    // TODO
    for (int i=0;i<this->length;i++){
        delete nodes[i];
    }
}

NodeList::NodeList(NodeList& other){
    // TODO
    this->length = other.length;
    for (int i=0; i<other.length; i++){
        this->nodes[i] = new Node(other.nodes[i]->getRow(),
        other.nodes[i]->getCol(),other.nodes[i]->getDistanceTraveled());
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