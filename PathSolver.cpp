#include "PathSolver.h"
#include <iostream>

PathSolver::PathSolver()
{
    // TODO
    nodesExplored = new NodeList();
}

PathSolver::~PathSolver()
{
    // TODO
    delete nodesExplored;
}

void PathSolver::forwardSearch(Env env)
{
//Start breakpoint at node index 80

    // TODO
    NodeList *openList = new NodeList();
    Node *start = new Node(0, 0, 0);
    start->searchPosition(SYMBOL_START, env);
    Node *goal = new Node(0, 0, 0);
    goal->searchPosition(SYMBOL_GOAL, env);
    openList->addElement(new Node(start->getRow(), start->getCol(), start->getDistanceTraveled()));
    Node *navi = nullptr;
    int shortest_index = 0;
    do
    {
        //Finds the node with the shortest distance to
        shortest_index = selectNode(openList, goal, openList->getLength());

        //Adds node details to navi and displays details
        navi = new Node(openList->getNode(shortest_index)->getRow(),
        openList->getNode(shortest_index)->getCol(),
        openList->getNode(shortest_index)->getDistanceTraveled());


        //Ends node search
        nodeNeighbour(env, navi->getRow() - 1, navi->getCol(), navi->getDistanceTraveled(), &openList);
        nodeNeighbour(env, navi->getRow() + 1, navi->getCol(), navi->getDistanceTraveled(), &openList);
        nodeNeighbour(env, navi->getRow(), navi->getCol() - 1, navi->getDistanceTraveled(), &openList);
        nodeNeighbour(env, navi->getRow(), navi->getCol() + 1, navi->getDistanceTraveled(), &openList);
        nodesExplored->addElement(new Node(navi->getRow(),navi->getCol(),navi->getDistanceTraveled()));
        delete navi;
    } while (goalReached(nodesExplored, goal, nodesExplored->getLength()));
    std::cout << "Search completed" << std::endl;

}

NodeList *PathSolver::getNodesExplored()
{
    //TODO
    for (int i = 0; i < nodesExplored->getLength(); i++)
    {std::cout << nodesExplored->getNode(i)->getCol() << ", " << nodesExplored->getNode(i)->getRow() << ", " << nodesExplored->getNode(i)->getDistanceTraveled() << std::endl;}
    return nodesExplored;

    //return nullptr;
}

NodeList *PathSolver::getPath(Env env)
{
    // TODO
    return nullptr;
}

//Custom methods/functions
int PathSolver::selectNode(NodeList *openList, Node *goal, int length)
{
    int shortest_dist = 400;
    int shortest_index = 0;
    for (int i = 0; i < length; i++)
    {
        if (openList->getNode(i)->getEstimatedDist2Goal(goal) < shortest_dist && 
        !nodeExistsinList(openList->getNode(i),nodesExplored,nodesExplored->getLength()))
        {
            shortest_dist = openList->getNode(i)->getEstimatedDist2Goal(goal);
            shortest_index = i;
        }
    }
    return shortest_index;
}

bool PathSolver::goalReached(NodeList *closedList, Node *goal, int length)
{
    for (int i = 0; i < length; i++)
    {
        if (closedList->getNode(i)->getCol() == goal->getCol() && 
        closedList->getNode(i)->getRow() == goal->getRow())
        {
            return false;
        }
    }
    return true;
}

bool PathSolver::nodeExistsinList(Node* n, NodeList* list, int length){
    for (int i = 0; i < length; i++)
    {
        if (n->nodeEquals(list->getNode(i)))
        {
            return true;
        }
    }
    return false;    
}

bool PathSolver::nodeExistsinList(int row, int col, NodeList* list, int length)
{
    for (int i = 0; i < length; i++)
    {
        if (list->getNode(i)->getRow() == row && list->getNode(i)->getCol() == col)
        {
            return true;
        }
    }
    return false;    
}

void PathSolver::nodeNeighbour(Env env, int row, int col, int dist, NodeList** openList)
{
    if (env[row][col] == SYMBOL_EMPTY || env[row][col] == SYMBOL_GOAL)
    {
        if(!nodeExistsinList(row, col,(*openList),(*openList)->getLength()))
        {
            (*openList)->addElement(new Node(row, col, dist));
            (*openList)->getNode((*openList)->getLength()-1)->setDistanceTraveled(dist);
        }
    }
}

//-----------------------------