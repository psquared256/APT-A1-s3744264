#include "NodeList.h"
#include <iostream>

NodeList::NodeList(){
    // TODO
    nodes = new Node*[NODE_LIST_ARRAY_MAX_SIZE];
    this->length = 0;
}

NodeList::~NodeList(){
    // TODO
    for (int i=0;i<this->length;i++){
        delete nodes[i];
    }
    delete[] nodes;
}

NodeList::NodeList(NodeList& other){
    // TODO
    nodes = new Node*[other.length];
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

//Milestone 4 functions
// NodeList::NodeList(int rows, int columns)
// {
//     nodes = new Node*[4*(rows*columns)];
//     this->length = 0;
// }

NodeList::NodeList(int area)
{
    nodes = new Node*[4*area];
    this->length = 0;
}
