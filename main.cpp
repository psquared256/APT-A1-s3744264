/* Pemal Padukkage (s3744264)
* 
* This implementation takes an iterative approach.  One step is completed at a 
* time so that the code is not too complex, where part 1 reads in an array,
* part 2 focuses on finding the goal, part 3 focuses on thinning the nodelist 
* so that only the shortest path is present, part 4 modifies the environment 
* using the thinned nodelist, and part 5 focuses on reading an environment
* of any given size.
* The main issue encountered was in milestone 2 concerning the handling of 
* dynamic memory management, where certain functions would fail due to initial
* mishandling of memory on heap.  This issue was resolved by duplicating 
* elements when necessary such as Nodes and NodeLists and reducing the use of
* heap memory when possible such as with methods forwardSearch and NodeContains.
* The main issue encountered in milestone 4 was being able to determine the
* size of the environment solely from the input redirection, as once said input
* was used or taken in any way, it was lost forever.  This issue was resolved
* by first appending all input to a string by character, and then casting the
* string as a character array before passing it through the methods 'findRows',
* 'findColumns' and 'readEnvStdin'.
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
void readEnvStdin(Env env, const char* envArray);

// Print out a Environment to standard output with path.
// To be implemented for Milestone 3
void printEnvStdout(Env env, NodeList *solution, int rows, int columns);

//Milestone 4 functions
int findRows(const char* envArray);
int findColumns(const char* envArray);
Env make_env(const int rows, const int cols);
void delete_env(Env env, int rows, int cols);

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

    
    std::string envString = "";
    char envPos = 'a';
    while(!std::cin.eof()){
        std::cin.get(envPos);
        envString += envPos;
    }
    envString.pop_back();
    int envRows = findRows(envString.c_str());
    int envColumns = findColumns(envString.c_str());
    

    // Load Environment
    Env env = make_env(envRows, envColumns);
    readEnvStdin(env, envString.c_str());

    //milestone 4 code
    PathSolver *pathSolver = new PathSolver(envRows, envColumns);
    pathSolver->forwardSearch(env, envRows, envColumns);   
    NodeList *exploredPositions = nullptr;
    exploredPositions = pathSolver->getNodesExplored();    
    NodeList *solution = pathSolver->getPath(env);
    printEnvStdout(env, solution, envRows, envColumns);
    //milestone 4 code ends


    // Solve using forwardSearch
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 2
        //PathSolver *pathSolver = new PathSolver();
        //pathSolver->forwardSearch(env);

        //NodeList *exploredPositions = nullptr;
        //exploredPositions = pathSolver->getNodesExplored();

    // Get the path
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 3
        //NodeList *solution = pathSolver->getPath(env);

        //printEnvStdout(env, solution);
    delete_env(env, envRows, envColumns);
    delete pathSolver;
    delete exploredPositions;
    delete solution;
}

void readEnvStdin(Env env, const char* envArray)
{
    int position = 0;
    int row = 0;
    int column = 0;
    bool arrayFilled = false;
    while (!arrayFilled)
    {
        if(envArray[position] == '\0')
        {
            arrayFilled = true;
        } else if (envArray[position] == '\n')
        {
            row++;
            column = 0;
            position++;
        } else
        {
            env[row][column] = envArray[position];
            column++;
            position++;
        }
        
    }
    // std::cout << "Environment successfully read" << std::endl;

}

//Iterates through the array of nodes, and replaces the character of the environment
//with the direction the robot has moved from any given position until the goal node.
//Prints out the environment when completed.
void printEnvStdout(Env env, NodeList *solution, int rows, int columns)
{
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

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if(env[i][j] != '\0'){std::cout << env[i][j];}
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

//Milestone 4 functions

//Takes 1 parameter: a char array representing the given environment
//(const char* envArray).

//This function iterates through the array, incrementing the
//value in numRows every time the character '\n' is found.

//When the function reaches the character '\0', it returns the int numRows.
int findRows(const char* envArray)
{
    int numRows = 0;
    int position = 0;
    while(true)
    {
        if(envArray[position] == '\n')
        {
            numRows++;
            position++;
        } else if (envArray[position] == '\0')
        {
            numRows++;
            return numRows;
        } else{
            position++;
        }
    }
}

//Takes 1 parameter: a char array representing the given environment
//(const char* envArray).

//This function iterates through the start of the array, incrementing the
//value in numColumns if the current element is not '\n'

//When the function reaches the character '\n', it returns the int numColumns.
int findColumns(const char* envArray)
{
    int numColumns = 0;
    int position = 0;
    while(true)
    {
        if(envArray[position] == '\n')
        {
            return numColumns;
        } else {
            numColumns++;
            position++;
        }
    }
}

Env make_env(const int rows, const int cols) {
   Env env = nullptr;

   if (rows >= 0 && cols >= 0) {
      env = new char*[rows];
      for (int i = 0; i != rows; ++i) {
         env[i] = new char[cols];
      }
   }
   return env;
}

void delete_env(Env env, int rows, int cols) {
   if (rows >= 0 && cols >= 0) {
      for (int i = 0; i != rows; ++i) {
         delete env[i];
      }
      delete env;
   }

   return;
}