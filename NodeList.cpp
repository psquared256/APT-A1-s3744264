#include "NodeList.h"
#include <iostream>

NodeList::NodeList(){
    nodes = new Node*[NODE_LIST_ARRAY_MAX_SIZE];
    this->length = 0;
}

NodeList::~NodeList(){
    for (int i=0;i<this->length;i++){
        delete nodes[i];
    }
    delete[] nodes;
}

NodeList::NodeList(NodeList& other){
    nodes = new Node*[other.length];
    this->length = other.length;
    for (int i=0; i<other.length; i++){
        this->nodes[i] = new Node(other.nodes[i]->getRow(),
        other.nodes[i]->getCol(),other.nodes[i]->getDistanceTraveled());
    }
    

}

int NodeList::getLength(){
    return length;

}

void NodeList::addElement(Node* newPos){
    nodes[length] = newPos;
    length++;
}

Node* NodeList::getNode(int i){
    return nodes[i];
}

//Milestone 4 functions

//This overloaded constructor takes a single parameter, 
//the area of the environment (int area).

//This constructor creates an array of nodes of the same size as the area,
//and initialises the length of the nodelist to 0.
NodeList::NodeList(int area)
{
    nodes = new Node*[4*area];
    this->length = 0;
}
