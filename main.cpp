/* Pemal Padukkage (s3744264)
* 
* This implementation takes an iterative approach.  One step is completed at a time
* so that the code is not too complex, where part 1 reads in an array, part 2 focuses 
* on finding the goal, part 3 focuses on thinning the nodelist so that only the 
* shortest path is present, and part 4 modifies the environment using the thinned nodelist.  
* The main issue encountered was in milestone 2 concerning the handling of dynamic memory
* management, where certain functions would fail due to initial mishandling of memory on heap.
* This issue was resolved by duplicating elements when necessary such as Nodes and NodeLists 
* and reducing the use of heap memory when possible such as with methods fowardSearch and NodeContains.
*/

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

#include "Types.h"
#include "Node.h"
#include "NodeList.h"
#include "PathSolver.h"

// Helper test functions
void testNode();
void testNodeList();

// Read a environment from standard input.
void readEnvStdin(Env env);

// Print out a Environment to standard output with path.
// To be implemented for Milestone 3
void printEnvStdout(Env env, NodeList *solution);

int main(int argc, char **argv)
{
    // THESE ARE SOME EXAMPLE FUNCTIONS TO HELP TEST YOUR CODE
    // AS YOU WORK ON MILESTONE 2. YOU CAN UPDATE THEM YOURSELF
    // AS YOU GO ALONG.
    // COMMENT THESE OUT BEFORE YOU SUBMIT!!!
    // std::cout << "TESTING - COMMENT THE OUT TESTING BEFORE YOU SUBMIT!!!" << std::endl;
    // testNode();
    // testNodeList();
    // std::cout << "DONE TESTING" << std::endl
    //           << std::endl;

    // Load Environment
    Env env;
    readEnvStdin(env);

    // Solve using forwardSearch
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 2
    PathSolver *pathSolver = new PathSolver();
    pathSolver->forwardSearch(env);

    NodeList *exploredPositions = nullptr;
    exploredPositions = pathSolver->getNodesExplored();

    // Get the path
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 3
    NodeList *solution = pathSolver->getPath(env);

    printEnvStdout(env, solution);

    delete pathSolver;
    delete exploredPositions;
    delete solution;
}

void readEnvStdin(Env env)
{
    //TODO

    int line = 0;
    while (!std::cin.eof() && line < 20)
    {
        std::cin >> env[line];
        line++;
    }

}

//Iterates through the array of nodes, and replaces the character of the environment
//with the direction the robot has moved from any given position until the goal node.
//Prints out the environment when completed.
void printEnvStdout(Env env, NodeList *solution)
{
    //TODOs
    int solLength = solution->getLength();
    for (int i = 1; i < solLength - 1; i++)
    {
        if (solution->getNode(i)->getCol() + 1 == solution->getNode(i + 1)->getCol() &&
            solution->getNode(i)->getRow() == solution->getNode(i + 1)->getRow())
        {
            env[solution->getNode(i)->getRow()][solution->getNode(i)->getCol()] = '>';
        }
        else if (solution->getNode(i)->getCol() == solution->getNode(i + 1)->getCol() &&
                 solution->getNode(i)->getRow() + 1 == solution->getNode(i + 1)->getRow())
        {
            env[solution->getNode(i)->getRow()][solution->getNode(i)->getCol()] = 'v';
        }
        else if (solution->getNode(i)->getCol() - 1 == solution->getNode(i + 1)->getCol() &&
                 solution->getNode(i)->getRow() == solution->getNode(i + 1)->getRow())
        {
            env[solution->getNode(i)->getRow()][solution->getNode(i)->getCol()] = '<';
        }
        else if (solution->getNode(i)->getCol() == solution->getNode(i + 1)->getCol() &&
                 solution->getNode(i)->getRow() - 1 == solution->getNode(i + 1)->getRow())
        {
            env[solution->getNode(i)->getRow()][solution->getNode(i)->getCol()] = '^';
        }
    }

    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            std::cout << env[i][j];
        }
        std::cout << std::endl;
    }

}

void testNode()
{
    std::cout << "TESTING Node" << std::endl;

    // Make a Node and print out the contents
    Node *node = new Node(1, 1, 2);
    Node *goal = new Node(3, 4, 0);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceTraveled() << std::endl;
    std::cout << node->getEstimatedDist2Goal(goal) << std::endl;
    delete node;
    delete goal;

    // Change Node and print again
    node = new Node(4, 2, 3);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceTraveled() << std::endl;
    delete node;

    //Test node comparison
    Node *n1 = new Node(1, 1, 2);
    Node *n2 = new Node(1, 1, 2);
    std::cout << (n1 == n2) << std::endl;
    std::cout << n1->nodeEquals(n2) << std::endl;
    delete n1;
    delete n2;
}

void testNodeList()
{
    std::cout << "TESTING NodeList" << std::endl;

    // Make a simple NodeList, should be empty size
    NodeList *nodeList = new NodeList();
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Add a Node to the NodeList, print size
    Node *b1 = new Node(1, 1, 1);
    nodeList->addElement(b1);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    //Copy of a nodelist to check whether copy constructor produces a deep copy
    NodeList *nodeList_copy = new NodeList(*nodeList);

    // Add second Nodetest
    Node *b2 = new Node(0, 0, 1);
    nodeList->addElement(b2);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;
    //Checks nodelist copy length to verify it is a deep copy
    std::cout << "NodeList copy size: " << nodeList_copy->getLength() << std::endl;

    Node *b3 = new Node(2, 2, 2);
    nodeList_copy->addElement(b3);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;
    std::cout << "NodeList copy size: " << nodeList_copy->getLength() << std::endl;

    // Test Get-ith - should be 0,0,1
    Node *getB = nodeList->getNode(1);
    std::cout << getB->getRow() << ",";
    std::cout << getB->getCol() << ",";
    std::cout << getB->getDistanceTraveled() << std::endl;

    // Test Get-ith - should be 2,2,2 if it is a deep copy
    Node *getC = nodeList_copy->getNode(1);
    std::cout << getC->getRow() << ",";
    std::cout << getC->getCol() << ",";
    std::cout << getC->getDistanceTraveled() << std::endl;

    // Test Get-ith - should fail retrieval if nodelist copy is a deep copy
    // Node *getD = nodeList->getNode(2);
    // std::cout << getD->getRow() << ",";
    // std::cout << getD->getCol() << ",";
    // std::cout << getD->getDistanceTraveled() << std::endl;

    delete b1;
    delete b2;
    delete b3;

    delete nodeList;
    delete nodeList_copy;

    // Print out the NodeList
    std::cout << "PRINTING OUT A NODELIST IS AN EXERCISE FOR YOU TO DO" << std::endl;
}
