#include "Node.h"
#include <iostream>

Node::Node(int row, int col, int dist_traveled)
{
    // TODO
    this->row = row;
    this->col = col;
    this->dist_traveled = dist_traveled;
}

Node::~Node()
{
    // TODO
}

int Node::getRow()
{
    // TODO
    return row;
}

int Node::getCol()
{
    // TODO
    return col;
}

int Node::getDistanceTraveled()
{
    // TODO
    return dist_traveled;
}

void Node::setDistanceTraveled(int dist_traveled)
{
    // TODO
    this->dist_traveled = dist_traveled + 1;
}

int Node::getEstimatedDist2Goal(Node *goal)
{
    // TODO
    //return -1;
    int manhattan_dist = std::abs(this->getCol() - goal->getCol());
    manhattan_dist += std::abs(this->getRow() - goal->getRow());
    return this->getDistanceTraveled() + manhattan_dist;
}

//Custom methods/functions

//Searches the position of the node which contains the character
void Node::searchPosition(char position, Env env){
    int x = 0;
    int y = 0;
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            if (env[i][j] == position)
            {
                
                x = j;
                y = i;
            }
        }
    }
    col = x;
    row = y;
}

//Checks to see if two nodes are equal
bool Node::nodeEquals(Node* n){
    if(this->getCol() == n->getCol() && this->getRow() == n->getRow()){
        return true;
    }else{
        return false;
    }
}

void Node::printNode(){
    std::cout << this->getCol() << ", " << this->getRow() << 
    ", " << this->getDistanceTraveled() << std::endl;
}

//--------------------------------