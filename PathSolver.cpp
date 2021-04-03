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
    start->searchPosition('S', env);
    Node *goal = new Node(0, 0, 0);
    goal->searchPosition('G', env);
    openList->addElement(new Node(start->getRow(), start->getCol(), start->getDistanceTraveled()));
    Node *navi = nullptr;
    Node *north = nullptr;
    Node *east = nullptr;
    Node *south = nullptr;
    Node *west = nullptr;
    int shortest_dist = 400;
    int shortest_index = 0;
    bool reachedGoal = false;
    do
    {
        if(openList->getLength() == 81)
        {std::cout << std::endl;}
        //Finds the node with the shortest distance to
        for (int i = 0; i < openList->getLength(); i++)
        {
            if (openList->getNode(i)->getEstimatedDist2Goal(goal) < shortest_dist && !nodeExistsinList(openList->getNode(i),nodesExplored, nodesExplored->getLength()))
            {
                shortest_dist = openList->getNode(i)->getEstimatedDist2Goal(goal);
                shortest_index = i;
                
            }
        }

        //Adds node details to navi and displays details
        navi = new Node(openList->getNode(shortest_index)->getRow(),
        openList->getNode(shortest_index)->getCol(),
        openList->getNode(shortest_index)->getDistanceTraveled());


       //Ends node search
        if (env[(navi->getRow() - 1)][(navi->getCol())] == '.' || env[(navi->getRow() - 1)][(navi->getCol())] == 'G')
        {
            north = new Node(navi->getRow() - 1, 
            navi->getCol(),
            navi->getDistanceTraveled());
            north->setDistanceTraveled(navi->getDistanceTraveled());
            if(!nodeExistsinList(north,openList,openList->getLength()))
            {
                openList->addElement(new Node(north->getRow(),north->getCol(),north->getDistanceTraveled()));
                delete north;
            }else
            {
                delete north;
            }

        }
        if (env[navi->getRow() + 1][navi->getCol()] == '.' || env[navi->getRow() + 1][navi->getCol()] == 'G')
        {
            south = new Node(navi->getRow() + 1, 
            navi->getCol(),
            navi->getDistanceTraveled());
            south->setDistanceTraveled(navi->getDistanceTraveled());
            if(!nodeExistsinList(south,openList,openList->getLength()))
            {
                openList->addElement(new Node(south->getRow(),south->getCol(),south->getDistanceTraveled()));
                delete south;
            }else
            {
                delete south;
            }
        }
        if (env[navi->getRow()][navi->getCol() - 1] == '.' || env[navi->getRow()][navi->getCol() - 1] == 'G')
        {
            west = new Node(navi->getRow(), 
            navi->getCol() - 1,
            navi->getDistanceTraveled());
            west->setDistanceTraveled(navi->getDistanceTraveled());
            if(!nodeExistsinList(west,openList,openList->getLength()))
            {
                openList->addElement(new Node(west->getRow(),west->getCol(),west->getDistanceTraveled()));
                delete west;
            }else
            {
                delete west;
            }
        }
        if (env[navi->getRow()][navi->getCol() + 1] == '.' || env[navi->getRow()][navi->getCol() + 1] == 'G')
        {
            east = new Node(navi->getRow(), 
            navi->getCol() + 1,
            navi->getDistanceTraveled());
            east->setDistanceTraveled(navi->getDistanceTraveled());
            if(!nodeExistsinList(east,openList,openList->getLength()))
            {
                openList->addElement(new Node(east->getRow(),east->getCol(),east->getDistanceTraveled()));
                delete east;
            }else
            {
                delete east;
            }
        }
        nodesExplored->addElement(new Node(navi->getRow(),navi->getCol(),navi->getDistanceTraveled()));
        delete navi;
        shortest_dist = 400;
        shortest_index = 0;       
        for (int i = 0; i < nodesExplored->getLength(); i++)
        {
            if (nodesExplored->getNode(i)->getCol() == goal->getCol() && nodesExplored->getNode(i)->getRow() == goal->getRow())
            {
                reachedGoal = true;
            }
        }
    } while (!reachedGoal);
    std::cout << "Search completed" << std::endl;

}

NodeList *PathSolver::getNodesExplored()
{
    //TODO
    for (int i = 0; i < nodesExplored->getLength(); i++)
    {std::cout << nodesExplored->getNode(i) << std::endl;}
    return nodesExplored;

    //return nullptr;
}

NodeList *PathSolver::getPath(Env env)
{
    // TODO
    return nullptr;
}

//Custom methods/functions

void PathSolver::selectNode(NodeList *openList, Node *p, Node *goal)
{
    int shortest_dist = 100;
    int shortest_index = 0;
    for (int i = 0; i < openList->getLength(); i++)
    {
        if (openList->getNode(i)->getEstimatedDist2Goal(goal) < shortest_dist)
        {
            shortest_dist = openList->getNode(i)->getEstimatedDist2Goal(goal);
            shortest_index = i;
        }
    }
    p = openList->getNode(shortest_index);
}

bool PathSolver::goalReached(NodeList *closedList, Node *goal)
{
    for (int i = 0; i < closedList->getLength(); i++)
    {
        // std::cout << "Starting goal check" << std::endl;
        if (closedList->getNode(i)->getCol() == goal->getCol() && closedList->getNode(i)->getRow() == goal->getRow())
        {
            return false;
        }
    }
    // std::cout << "Finishing goal check" << std::endl;
    return true;
}

bool PathSolver::nodeExistsinList(Node* n,NodeList* list, int length){
    for (int i = 0; i < length; i++)
    {
        if (n->nodeEquals(list->getNode(i)))
        {
            return true;
        }
    }
    return false;    
}

//-----------------------------