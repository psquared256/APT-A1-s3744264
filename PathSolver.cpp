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
    delete start;
    delete goal;
    delete openList;
}

NodeList *PathSolver::getNodesExplored()
{
    //TODO
    //for (int i = 0; i < nodesExplored->getLength(); i++)
    //{nodesExplored->getNode(i)->printNode();}
    NodeList* exploredPositions = new NodeList(*nodesExplored);
    return exploredPositions;
}

NodeList *PathSolver::getPath(Env env)
{
    // TODO
    NodeList *path = new NodeList();
    int path_dist = -1;
    int nodesLength = nodesExplored->getLength();
    bool nextStep = false;
    path->addElement(new Node(nodesExplored->getNode(nodesExplored->getLength()-1)->getRow(),
    nodesExplored->getNode(nodesExplored->getLength()-1)->getCol(),
    nodesExplored->getNode(nodesExplored->getLength()-1)->getDistanceTraveled()));
    do
    {
        for(int i = 0; i < nodesLength && !nextStep; i++){
            if(pathNeighbour(path->getNode(path->getLength()-1),
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
    delete path;
    return path_rev;
}

//Custom methods/functions
int PathSolver::selectNode(NodeList *openList, Node *goal, int length)
{
    int shortest_dist = 400;
    int shortest_index = 0;
    for (int i = 0; i < length; i++)
    {
        if (openList->getNode(i)->getEstimatedDist2Goal(goal) < shortest_dist && 
        !nodeExistsinList(openList->getNode(i)->getRow(), openList->getNode(i)->getCol(),nodesExplored,nodesExplored->getLength()))
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
