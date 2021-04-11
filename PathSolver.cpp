#include "PathSolver.h"
#include <iostream>

PathSolver::PathSolver()
{
    nodesExplored = new NodeList();
}

PathSolver::~PathSolver()
{
    delete nodesExplored;
}

void PathSolver::forwardSearch(Env env)
{

    NodeList *openList = new NodeList();
    Node *start = new Node(0, 0, 0);
    start->searchPosition(SYMBOL_START, env, 20, 20);
    Node *goal = new Node(0, 0, 0);
    goal->searchPosition(SYMBOL_GOAL, env, 20, 20);
    openList->addElement(new Node(start->getRow(),
     start->getCol(), start->getDistanceTraveled()));
    Node *navi = nullptr;
    int shortest_index = 0;
    do
    {
        
        shortest_index = selectNode(openList,goal,openList->getLength(),20*20);

        //Adds node details to navi
        navi = new Node(openList->getNode(shortest_index)->getRow(),
        openList->getNode(shortest_index)->getCol(),
        openList->getNode(shortest_index)->getDistanceTraveled());


        nodeContains(env, navi->getRow() - 1, navi->getCol(),
         navi->getDistanceTraveled(), &openList);
        nodeContains(env, navi->getRow() + 1, navi->getCol(),
         navi->getDistanceTraveled(), &openList);
        nodeContains(env, navi->getRow(), navi->getCol() - 1,
         navi->getDistanceTraveled(), &openList);
        nodeContains(env, navi->getRow(), navi->getCol() + 1,
         navi->getDistanceTraveled(), &openList);
        nodesExplored->addElement(new Node(navi->getRow(),
         navi->getCol(), navi->getDistanceTraveled()));
        delete navi;
    } while (!goalReached(nodesExplored, goal, nodesExplored->getLength()));
    delete start;
    delete goal;
    delete openList;
}

NodeList *PathSolver::getNodesExplored()
{
    NodeList* exploredPositions = new NodeList(*nodesExplored);
    return exploredPositions;
}

NodeList *PathSolver::getPath(Env env)
{
    NodeList *path = new NodeList(this->nodesExplored->getLength());
    int path_dist = -1;
    int nodesLength = nodesExplored->getLength();
    bool nextStep = false;
    path->addElement(new Node(nodesExplored->
     getNode(nodesExplored->getLength()-1)->getRow(),
     nodesExplored->getNode(nodesExplored->getLength()-1)->getCol(),
     nodesExplored->getNode(nodesExplored->getLength()-1)->
     getDistanceTraveled()));
    do
    {
        for(int i = 0; i < nodesLength && !nextStep; i++){
            if(pathNeighbour(path->getNode(path->getLength()-1),
             nodesExplored->getNode(i))){

                path->addElement(new Node(nodesExplored->getNode(i)->getRow(),
                 nodesExplored->getNode(i)->getCol(), 
                 nodesExplored->getNode(i)->getDistanceTraveled()));
                path_dist = nodesExplored->getNode(i)->getDistanceTraveled();
                nextStep = true;
            }
        }
        nextStep = false;
    }while(path_dist!=0);

    NodeList *path_rev = new NodeList(path->getLength());
    for(int i = path->getLength()-1; i >= 0; i--)
    {
        path_rev->addElement(new Node(path->getNode(i)->getRow(),
        path->getNode(i)->getCol(), path->getNode(i)->getDistanceTraveled()));
    }
    delete path;
    return path_rev;
}

//Custom methods/functions

//Takes 4 parameters: the list of available nodes (NodeList *openList),
//the goal node (Node *goal), the length of the nodelist (int length),
//and the maximum distance possible to the goal in the environment 
//(int max_dist).

//The function iterates through the open list and should the loop find a node
//that contains a shorter distance than the value in 'shortest_dist', it will
//assign that node's distance to the goal to 'shortest_dist' as well as the
//index of the node containing the shortest distance.

//After the end of the loop, the function returns an int representing the
//index of whatever node had the shortest distance to the goal.
int PathSolver::selectNode(NodeList *openList, Node *goal, int length, int max_dist)
{
    int shortest_dist = max_dist;
    int shortest_index = 0;
    for (int i = 0; i < length; i++)
    {
        if (openList->getNode(i)->getEstimatedDist2Goal(goal) < shortest_dist&&
         !nodeExistsinList(openList->getNode(i)->getRow(), 
         openList->getNode(i)->getCol(),
         nodesExplored,nodesExplored->getLength()))
        {
            shortest_dist = openList->getNode(i)->getEstimatedDist2Goal(goal);
            shortest_index = i;
        }
    }
    return shortest_index;
}

//Takes 3 parameters: a NodeList that contains all the nodes explored
//(NodeList *closedList), the goal node (Node *goal), and the length
//of the closedList (int length).

//This function iterates through the closedList and compares the coordinates
//of each each node in the list against the coordinates of the goal node.

//Returns a boolean value depending on whether a match is found
//(true for a found match, false for no match found).
bool PathSolver::goalReached(NodeList *closedList, Node *goal, int length)
{
    for (int i = 0; i < length; i++)
    {
        if (closedList->getNode(i)->getCol() == goal->getCol() && 
        closedList->getNode(i)->getRow() == goal->getRow())
        {
            return true;
        }
    }
    return false;
}

//Takes two parameters, a node from the path NodeList (Node *pathNode),
//and a node from the list of explored nodes (Node *listNode).

//This function checks whether the distance traveled of the listNode
//is less than the distance travelled of the pathNode by one
//AND
//whether the listNode is neighbouring the pathNode (e.g. above the
//pathNode by one, below the pathNode, left of the pathNode, or 
//right of the pathNode).

//Returns a boolean value depending on whether both those conditions
//have been met.
bool PathSolver::pathNeighbour(Node* pathNode, Node* listNode){
    if (pathNode->getDistanceTraveled() - 1 == listNode->getDistanceTraveled())
    {
        if (pathNode->getCol() + 1 == listNode->getCol() &&
                pathNode->getRow() == listNode->getRow())
        {
            return true;
        }else if (pathNode->getCol() == listNode->getCol() &&
            pathNode->getRow() + 1 == listNode->getRow())
        {
            return true;
        } else if (pathNode->getCol() - 1 == listNode->getCol() &&
                pathNode->getRow() == listNode->getRow())
        {
            return true;
        } else if (pathNode->getCol() == listNode->getCol() &&
                pathNode->getRow() - 1 == listNode->getRow())
        {
            return true;
        }
    }
    return false;
}

//Takes 4 parameters: a row number (int row), a column number (int column)
//a NodeList (NodeList *list), and the length of the NodeList (int length)

//This function iterates through any given list and compares the coordinates
//of the current node in the loop against the given row and column coordinates
//passed into the function.

//Returns a boolean variable depending on whether match was found in the list
//of nodes.
bool PathSolver::nodeExistsinList(int row, int col, NodeList* list, int length)
{
    for (int i = 0; i < length; i++)
    {
        if (list->getNode(i)->getRow()==row && list->getNode(i)->getCol()==col)
        {
            return true;
        }
    }
    return false;    
}

//Takes 5 parameters: An environment (Env env), a row number (int row), 
//a column number (int col), a number for distance travelled (int dist),
// and a pointer to a NodeList representing the nodes available to explore 
//(NodeList** openList).

//This function compares the element in the environment with the given 
//coordinates against the characters '.' & 'G'.  Nested inside the if statement
//is another if statement that uses the nodeExistsInList method to check
//whether these coordinates already belong to a node in the openList.

//Should the position contain either '.' or 'G', and it is not already
//present in the openList, it is then added to the openList, and its
//distance travelled is incremented by one.
void PathSolver::nodeContains(Env env, int row, int col, int dist, NodeList** openList)
{
    if (env[row][col] == SYMBOL_EMPTY || env[row][col] == SYMBOL_GOAL)
    {
        if(!nodeExistsinList(row, col,(*openList),(*openList)->getLength()))
        {
            (*openList)->addElement(new Node(row, col, dist));
            (*openList)->getNode((*openList)->getLength()-1)->
             setDistanceTraveled(dist);
        }
    }
}

//Milestone 4 functions

//This overloaded constructor takes 2 parameters, the number of rows (int rows)
//and the number of columns (int columns).

//This constructor multiplies the number of rows with the number of columns,
//and passes the resulting value to the overloaded NodeList constructor.
PathSolver::PathSolver(int rows, int columns)
{
    nodesExplored = new NodeList(rows*columns);
}

void PathSolver::forwardSearch(Env env, int rows, int columns)
{
    NodeList *openList = new NodeList(rows*columns);
    Node *start = new Node(0, 0, 0);
    start->searchPosition(SYMBOL_START, env, rows, columns);
    Node *goal = new Node(0, 0, 0);
    goal->searchPosition(SYMBOL_GOAL, env, rows, columns);
    openList->addElement(new Node(start->getRow(), 
     start->getCol(), start->getDistanceTraveled()));
    Node *navi = nullptr;
    int shortest_index = 0;
    do
    {
        
        shortest_index = selectNode(openList, goal,
         openList->getLength(), rows*columns);

        //Adds node details to navi
        navi = new Node(openList->getNode(shortest_index)->getRow(),
        openList->getNode(shortest_index)->getCol(),
        openList->getNode(shortest_index)->getDistanceTraveled());


        nodeContains(env, navi->getRow() - 1, navi->getCol(), 
         navi->getDistanceTraveled(), &openList);
        nodeContains(env, navi->getRow() + 1, navi->getCol(), 
         navi->getDistanceTraveled(), &openList);
        nodeContains(env, navi->getRow(), navi->getCol() - 1, 
         navi->getDistanceTraveled(), &openList);
        nodeContains(env, navi->getRow(), navi->getCol() + 1, 
         navi->getDistanceTraveled(), &openList);
        nodesExplored->addElement(new Node(navi->getRow(),
         navi->getCol(),navi->getDistanceTraveled()));
        delete navi;
    } while (!goalReached(nodesExplored, goal, nodesExplored->getLength()));
    delete start;
    delete goal;
    delete openList;
}
//-----------------------------
