# APT-A1-s3744264

This is a path-finding program made for Assignment 1 of Advanced Programming Techniques.

## Building

To build this project, navigate to the folder and run the following command `g++ -Wall -Werror -std=c++14 -O -o assign1 Node.cpp NodeList.cpp PathSolver.cpp main.cpp`.

## Running the Program

To run this program, use the following command `./assign1 <{environment}`, with {environment} being the path to the environment file (e.g. `./assign1 <sampleTest/sample01.env`).

The environment used as input for the program must be contained inside a plaintext file, be rectangular, have a start point and a goal point (indicated in the environment file as 'S' and 'G'), 
and have a clear path from the start to the goal.

[Example Format](https://raw.githubusercontent.com/s3744264/APT-A1-s3744264/master/sampleTest/sample01.env?token=ATDESNTLMN3QABEJQQMPJHTBBAEHI)

