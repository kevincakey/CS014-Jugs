#ifndef JUG_H
#define JUG_H

#include<string>
#include<sstream>
#include<vector>
#include<queue>
#include<iostream>

using namespace std; //Kevin Gao, Jordan Chan, Brian Martell , cpp reference, zybooks, qstacks

struct Node
{
public:
    Node(int, int);
    int valA = 0;
    int valB = 0;
    int distance = 2147483647;
    Node* predN = nullptr;
    Node* nfillA = nullptr;
    Node* nfillB = nullptr;
    Node* nemptyA = nullptr;
    Node* nemptyB = nullptr;
    Node* npourAB = nullptr;
    Node* npourBA = nullptr;
};

class Jug {
public:
    Jug(int Ca, int Cb, int N, int cfA, int cfB, int ceA, int ceB, int cpAB, int cpBA);

	//Ca and Cb are the capacities of the jugs A and B, respectively, and N is the goal. 
	//cfA is the cost to fill A, cfB is the cost to fill B, ceA, is the cost to empty A, 
	//ceB is the cost to empty B, cpAB is the cost to pour A to B and cpBA is the cost to 
	//pour B to A. A solution is  a sequence of steps that leaves jug A empty, and exactly N gallons in jug B. 
    ~Jug();

    //solve is used to check input and find the solution if one exists
    //returns -1 if invalid inputs. solution set to empty string.
    //returns 0 if inputs are valid but a solution does not exist. solution set to empty string.
    //returns 1 if solution is found and stores solution steps in solution string.
    int solve(string& solution);
private:
    //anything else you need
	bool itwork = true;
    int capA;
    int capB;
    int N;
    int cfA;
    int cfB;
    int ceA;
    int ceB;
    int cpAB;
    int cpBA;
    int numNodes;
    queue<Node*> cheater;

    Node* start;
    int totalOperationCost;
    void makeGraph(Node*);
    bool nodeExist(int, int);
	Node* search(int, int);

};

#endif