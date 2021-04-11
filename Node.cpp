#include "Node.h"
#include <iostream>

Node::Node(int row, int col, int dist_traveled)
{
    this->row = row;
    this->col = col;
    this->dist_traveled = dist_traveled;
}

Node::~Node()
{
}

int Node::getRow()
{
    return row;
}

int Node::getCol()
{
    return col;
}

int Node::getDistanceTraveled()
{
    return dist_traveled;
}

void Node::setDistanceTraveled(int dist_traveled)
{
    this->dist_traveled = dist_traveled + 1;
}

int Node::getEstimatedDist2Goal(Node *goal)
{
    int manhattan_dist = std::abs(this->getCol() - goal->getCol());
    manhattan_dist += std::abs(this->getRow() - goal->getRow());
    return this->getDistanceTraveled() + manhattan_dist;
}

//Custom methods/functions

//Takes 4 parameters: The character to find (char position), 
//the environment to search through (Env env),
//the number rows (int rows) and the number of columns (int columns).
//
//The function iterates through the environment until the cell containing
//the character is found, where the values of row iterator 'i' and column
//iterator 'j' are assigned to the 'row' and 'col' variables of 
//the node that called the method.
void Node::searchPosition(char position, Env env, int rows, int columns){
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (env[i][j] == position)
            {
                
                col = j;
                row = i;
            }
        }
    }
}

//Takes one parameter, a Node (Node* n)
//
//Compares the coordinates of the node that called the method and
//the node passed as a parameter.  Returns a boolean value
//based on whether both pairs of coordiantes match.
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