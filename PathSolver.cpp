#include "PathSolver.h"
#include <iostream>

PathSolver::PathSolver()
{
    // TODO
    //nodesExplored = new NodeList();
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
    openList->addElement(start);
    Node *navi = nullptr;
    Node *north = nullptr;
    Node *east = nullptr;
    Node *south = nullptr;
    Node *west = nullptr;
    int shortest_dist = 100;
    int shortest_index = 0;;
    bool reachedGoal = false;
    do
    {
        std::cout << "Starting..." << std::endl;
        //Finds the node with the shortest distance to
        for (int i = 0; i < openList->getLength(); i++)
        {
            if (openList->getNode(i)->getEstimatedDist2Goal(goal) < shortest_dist && !nodeExistsinList(openList->getNode(i),nodesExplored))
            {
                shortest_dist = openList->getNode(i)->getEstimatedDist2Goal(goal);
                shortest_index = i;
                
            }
        }
        if(shortest_index==0){std::cout << "0" << std::endl;}
        std::cout << "Index of node: " << shortest_index << std::endl;
        std::cout << "Node found" << std::endl;
        //Adds node details to navi and displays details
        navi = new Node(openList->getNode(shortest_index)->getRow(),
        openList->getNode(shortest_index)->getCol(),
        openList->getNode(shortest_index)->getDistanceTraveled());
        std::cout << navi->getCol() << ", " << 
        navi->getRow() << ", " << 
        navi->getDistanceTraveled() <<  std::endl;
        std::cout << "Node Added" << std::endl;

       //Ends node search
        if (env[(navi->getRow() - 1)][(navi->getCol())] == '.' || env[(navi->getRow() - 1)][(navi->getCol())] == 'G')
        {
            if(shortest_index ==81){std::cout << "North node found" << std::endl;}
            north = new Node(navi->getRow() - 1, 
            navi->getCol(),
            navi->getDistanceTraveled());
            north->setDistanceTraveled(navi->getDistanceTraveled());
            if(!nodeExistsinList(north,openList))
            {
                if(shortest_index ==81){std::cout << "North node added" << std::endl;}
                openList->addElement(north);
            }else
            {
                delete north;
            }

        }
        if (env[navi->getRow() + 1][navi->getCol()] == '.' || env[navi->getRow() + 1][navi->getCol()] == 'G')
        {
            if(shortest_index ==81){std::cout << "South node found" << std::endl;}
            south = new Node(navi->getRow() + 1, 
            navi->getCol(),
            navi->getDistanceTraveled());
            south->setDistanceTraveled(navi->getDistanceTraveled());
            if(!nodeExistsinList(south,openList))
            {
                if(shortest_index ==81){std::cout << "South node added" << std::endl;}
                openList->addElement(south);
            }else
            {
                delete south;
            }
        }
        if (env[navi->getRow()][navi->getCol() - 1] == '.' || env[navi->getRow()][navi->getCol() - 1] == 'G')
        {
            if(shortest_index ==81){std::cout << "West node found" << std::endl;}
            west = new Node(navi->getRow(), 
            navi->getCol() - 1,
            navi->getDistanceTraveled());
            west->setDistanceTraveled(navi->getDistanceTraveled());
            if(!nodeExistsinList(west,openList))
            {
                if(shortest_index ==81){std::cout << "West node added" << std::endl;}
                openList->addElement(west);
            }else
            {
                delete west;
            }
        }
        if (env[navi->getRow()][navi->getCol() + 1] == '.' || env[navi->getRow()][navi->getCol() + 1] == 'G')
        {
            if(shortest_index ==81){std::cout << "East node found" << std::endl;}
            east = new Node(navi->getRow(), 
            navi->getCol() + 1,
            navi->getDistanceTraveled());
            east->setDistanceTraveled(navi->getDistanceTraveled());
            if(!nodeExistsinList(east,openList))
            {
                if(shortest_index ==81){std::cout << "East node added" << std::endl;}
                openList->addElement(east);
            }else
            {
                delete east;
            }
        }
        if(shortest_index ==81){north->printNode();} 
        nodesExplored->addElement(navi);
        shortest_dist = 100;
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
    // for (int i = 0; i < nodesExplored->getLength(); i++)
    // {nodesExplored->getNode(i)->printNode();}
    return nodesExplored;

    //return nullptr;
}

NodeList *PathSolver::getPath(Env env)
{
    // TODO
    NodeList *path = new NodeList();
    int path_dist = -1;
    int nodesLength = nodesExplored->getLength();
    bool nextStep = false;
    if(nodesLength==0){}
    path->addElement(new Node(nodesExplored->getNode(nodesExplored->getLength()-1)->getRow(),
    nodesExplored->getNode(nodesExplored->getLength()-1)->getCol(),
    nodesExplored->getNode(nodesExplored->getLength()-1)->getDistanceTraveled()));
    do
    {
        for(int i = 0; i < nodesLength && !nextStep; i++){
            if(/*!nextStep &&*/ nodeNeighbour(path->getNode(path->getLength()-1),
             nodesExplored->getNode(i))){

                path->addElement(new Node(nodesExplored->getNode(i)->getRow(),
                nodesExplored->getNode(i)->getCol(), nodesExplored->getNode(i)->getDistanceTraveled()));
                path_dist = nodesExplored->getNode(i)->getDistanceTraveled();
                nextStep = true;
            }
        }
        nextStep = false;
    }while(path_dist!=0);
    // for (int i = 0; i < path->getLength(); i++)
    // {path->getNode(i)->printNode();}
    // std::cout << "Pure path retrieved" << std::endl;

    NodeList *path_rev = new NodeList();
    for(int i = path->getLength()-1; i >= 0; i--)
    {
        path_rev->addElement(new Node(path->getNode(i)->getRow(),
        path->getNode(i)->getCol(), path->getNode(i)->getDistanceTraveled()));
    }
    // for (int i = 0; i < path->getLength(); i++)
    // {path_rev->getNode(i)->printNode();}
    // std::cout << "Reverse of pure path retrieved" << std::endl;
    return path_rev;
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
        std::cout << "Starting goal check" << std::endl;
        if (closedList->getNode(i)->getCol() == goal->getCol() && closedList->getNode(i)->getRow() == goal->getRow())
        {
            return false;
        }
    }
    std::cout << "Finishing goal check" << std::endl;
    return true;
}

bool PathSolver::nodeExistsinList(Node* n,NodeList* list){
    for (int i = 0; i < list->getLength(); i++)
    {
        if (n->nodeEquals(list->getNode(i)))
        {
            return true;
        }
    }
    return false;    
}

bool PathSolver::nodeNeighbour(Node* pathNode, Node* listNode){
    // pathNode->printNode();
    // listNode->printNode();
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

//-----------------------------