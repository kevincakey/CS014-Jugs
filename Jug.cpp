#include "Jug.h"

Node::Node(int tempA, int tempB){
	valA = tempA;
	valB = tempB;
}

Jug::Jug(int Ca, int Cb, int N, int cfA,int cfB,int ceA, int ceB, int cpAB, int cpBA)
{
	capA = Ca;
	capB = Cb;
	this->N = N;
	this->cfA = cfA;
	this->cfB = cfB;
	this->ceA = ceA;
	this->ceB = ceB;
	this->cpAB = cpAB;
	this->cpBA = cpBA;
	numNodes = 0;
	start = new Node(0, 0);
	start->distance = 0;
	cheater.push(start);
	makeGraph(start);
}

Jug::~Jug()
{
	delete start;
}

bool Jug::nodeExist(int a, int b){
	Node* tempNo = search(a, b);
	if(tempNo == nullptr){
		return false;
	}
	return true;
}

Node* Jug::search(int a, int b){
	queue<Node*> tempq = cheater;
	Node* tempn;
	while (!tempq.empty()) {
		tempn = tempq.front();
		if(tempn->valA == a && tempn->valB == b){
			return tempn;
		}
		tempq.pop();
	}
	return nullptr;
}
	
int Jug::solve(string& solution)
{
	if ((0 > cfA) || (0 > cfB) || (0 > ceA) || (0 > ceB) || (0 > cpAB) || (0 > cpBA))
	{
		solution = "";
		return -1;
	}
	if (0 > capA)
	{
		solution = "";
		return -1;
	}
	if(capA >= capB){
		solution = "";
		return -1;
	}
	if (N >= capB)
	{
		solution = "";
		return -1;
	}
	if(capB >= 1000){
		solution = "";
		return -1;
	}
	if(!itwork){
		solution = "";
		return -1;
	}

	if (nodeExist(0, N))
	{
		queue<Node*> qtov = cheater;
		vector<Node*> v;
		while (!qtov.empty())
		{
			v.push_back(qtov.front());
			//cout << qtov.front()->valA << ", " << qtov.front()->valB << endl;
			qtov.pop();
		}
		vector<Node*> vshort = v;

		while (v.size() != 0)
		{
			Node* min = v.at(0);
			//int itemp;
			for (unsigned int i = 0; i < v.size(); i++)
			{
				//find min dist node
				if (min->distance > v.at(i)->distance)
				{
					min = v.at(i);
				}
				//itemp = i;
				//print vector
				//cout << "(" << v.at(i)->valA << ", " << v.at(i)->valB << ")" << endl;
			}
			//v.erase(v.begin() + itemp-1);
			for (unsigned int i = 0; i < v.size(); i++) {
				if (min->valA == v.at(i)->valA && min->valB == v.at(i)->valB) {
					v.erase(v.begin() + i);
				}
			}

			//cout << "min: " << min->valA << ", " << min->valB << endl;
			if (min->nfillA != nullptr)
			{
				if (min->nfillA->distance > (cfA + min->distance))
				{
					min->nfillA->distance = cfA + min->distance;
					min->nfillA->predN = min;
				//	cout << "Hit min fill A" << endl;
				}
			}
			if (min->nfillB != nullptr)
			{
				if (min->nfillB->distance > (cfB + min->distance))
				{
					min->nfillB->distance = cfB + min->distance;
					min->nfillB->predN = min;
					//cout << "Hit min fill B" << endl;
				}
			}
			if (min->nemptyA != nullptr)
			{
				if (min->nemptyA->distance > (ceA + min->distance))
				{
					min->nemptyA->distance = ceA + min->distance;
					min->nemptyA->predN = min;
					//cout << "Hit minemptyA" << endl;
				}
			}
			if (min->nemptyB != nullptr)
			{
				if (min->nemptyB->distance > (ceB + min->distance))
				{
					min->nemptyB->distance = ceB + min->distance;
					min->nemptyB->predN = min;
				//	cout << "Hit min empty B" << endl;
				}
			}
			if (min->npourAB != nullptr)
			{
				if (min->npourAB->distance > (cpAB + min->distance))
				{
					min->npourAB->distance = cpAB + min->distance;
					min->npourAB->predN = min;
				//	cout << "Hit min pourAB" << endl;
				}
			}
			if (min->npourBA != nullptr)
			{
				if (min->npourBA->distance > (cpBA + min->distance))
				{
					min->npourBA->distance = cpBA + min->distance;
					min->npourBA->predN = min;
				//	cout << "Hit min pour BA" << endl;
				}
			}
		}

	//	cout << "making connections completed" << endl;

		//determining the shortest path
		Node* destination;
		for (unsigned int j = 0; j < vshort.size();j++)
		{
			if (vshort.at(j)->valA == 0 && vshort.at(j)->valB == N)
			{
				destination = vshort.at(j);
			}
		}

		int cost = 0;
		//cout << "reached while loop" << endl;
		//cout << "predN: " << destination->predN << endl;
		while (destination->predN != nullptr)
		{
			//cout << "In while loop" << endl;
			//cost += destination->distance;
			if (destination->predN == destination->nfillA) {
				solution += "\nA ytpme";
				//cout << "empty A" << endl;
				cost += ceA;
			}
			if (destination->predN == destination->nfillB) {
				solution += "\nB ytpme";
				//cout << "empty B" << endl;
				cost += ceB;
			}
			if (destination->predN == destination->nemptyA) {
				solution += "\nA llif";
				//cout << "fill A" << endl;
				cost += cfA;
			}
			if (destination->predN == destination->nemptyB) {
				solution += "\nB llif";
				//cout << "fill B" << endl;
				cost += cfB;
			}
			if (destination->predN == destination->npourAB) {
				solution += "\nA B ruop";
				//cout << "pourBA" << endl;
				cost += cpBA;
			}
			if (destination->predN == destination->npourBA) {
				solution +="\nB A ruop";
				//cout << "pourAB" << endl;
				cost += cpAB;
			}
			//cout << "cost:" << cost << endl;
			destination = destination->predN;

		}
		for (unsigned int i = 0; i< solution.length()/2;++i)
		{
			swap(solution.at(i), solution.at(solution.length() - i - 1));
		}
		//cout << solution << "success " << cost;
		//cout << solution << "THIS IS THE END OF THE SOLUTION KEVIN SUCKS" << endl;
		solution += "success ";
		stringstream stemp;
		stemp << solution << cost;
		solution = stemp.str();
		return 1;
	}
	else
	{
		solution = "";
		return 0;
	}
	return 0;
}


void Jug::makeGraph(Node* temp)
{
	if ((0 > cfA) || (0 > cfB) || (0 > ceA) || (0 > ceB) || (0 > cpAB) || (0 > cpBA))
	{
		//solution = "";
		itwork = false;
		return;
	}
	if (0 > capA)
	{
		//solution = "";
		itwork = false;
		return;
	}
	if (capA >= capB) {
		//solution = "";
		itwork = false;
		return;
	}
	if (N >= capB)
	{
		//solution = "";
		itwork = false;
		return;
	}
	if (capB >= 1000) {
		//solution = "";
		itwork = false;
		return;
	}

	//fillA
	if(temp->nfillA == nullptr && !nodeExist(capA, temp->valB) && temp->valA != capA)
	{
		Node* filledA = new Node(capA, temp->valB);
		temp->nfillA = filledA;
		numNodes++;
		cheater.push(filledA);
		//cout << temp->valA << ", " << temp->valB << " nfillA to " << capA << ", " << temp->valB << endl;
		makeGraph(filledA);
	}
	else if(temp->nfillA == nullptr && temp->valA != capA){
		temp->nfillA = search(capA, temp->valB);
		//cout << temp->valA << ", " << temp->valB << " nfillA to " << capA << ", " << temp->valB << endl;
	}
 
	//fillB
	if (temp->nfillB == nullptr && !nodeExist(temp->valA, capB) && temp->valB != capB)
	{
		Node* filledB = new Node(temp->valA, capB);
		temp->nfillB = filledB;
		numNodes++;
		cheater.push(filledB);
		//cout << temp->valA << ", " << temp->valB << " nfillB to " << temp->valA << ", " << capB << endl;
		makeGraph(filledB);
	}
	else if (temp->nfillB == nullptr && temp->valB != capB) {
		temp->nfillB = search(temp->valA, capB);
		//cout << temp->valA << ", " << temp->valB << " nfillB to " << temp->valA << ", " << capB << endl;
	}

	//emptyA
	if(temp->nemptyA == nullptr && !nodeExist(0, temp->valB) && temp->valA != 0)
	{
		Node* emptiedA = new Node(0, temp->valB);
		temp->nemptyA = emptiedA;
		numNodes++;
		cheater.push(emptiedA);
		//cout << temp->valA << ", " << temp->valB << " nemptyA to " << 0 << ", " << temp->valB << endl;
		makeGraph(emptiedA);
	}
	else if(temp->nemptyA == nullptr && temp->valA != 0){
		temp->nemptyA = search(0, temp->valB);
		//cout << temp->valA << ", " << temp->valB << " nemptyA to " << 0 << ", " << temp->valB << endl;
	}

	//emptyB
	if(temp->nemptyB == nullptr && !nodeExist(temp->valA, 0) && temp->valB != 0)
	{
		Node* emptiedB = new Node(temp->valA,0);
		temp->nemptyB = emptiedB;
		numNodes++;
		cheater.push(emptiedB);
		//cout << temp->valA << ", " << temp->valB << " nemptyB to " << temp->valA << ", " << 0 << endl;
		makeGraph(emptiedB);
	}
	else if(temp->nemptyB == nullptr && temp->valB != 0){
		temp->nemptyB = search(temp->valA, 0);
		//cout << temp->valA << ", " << temp->valB << " nemptyB to " << temp->valA << ", " << 0 << endl;
	}

	//pourAB
	int apour;
	int bpour;
	if(temp->valA + temp->valB > capB){
		apour = temp->valA + temp->valB - capB;
		bpour = capB;
	}
	else{
		apour = 0;
		bpour = temp->valA + temp->valB;
	}
	
	if (temp->npourAB == nullptr && !nodeExist(apour, bpour) && temp->valA != 0){
		Node* pouredAB = new Node(apour, bpour);
		temp->npourAB = pouredAB;
		numNodes++;
		cheater.push(pouredAB);
		//cout << temp->valA << ", " << temp->valB << " npourAB to " << apour << ", " << bpour << endl;
		makeGraph(pouredAB);
	}
	else if(temp->npourAB == nullptr && temp->valA != 0){
		temp->npourAB = search(apour, bpour);
		//cout << temp->valA << ", " << temp->valB << " npourAB to " << apour << ", " << bpour << endl;
	}

	//pourBA
	if (temp->valA + temp->valB > capA) {
		bpour = temp->valA + temp->valB - capA;
		apour = capA;
	}
	else {
		bpour = 0;
		apour = temp->valA + temp->valB;
	}

	if (temp->npourBA == nullptr && !nodeExist(apour, bpour) && temp->valB != 0) {
		Node* pouredBA = new Node(apour, bpour);
		temp->npourBA = pouredBA;
		numNodes++;
		cheater.push(pouredBA);
		//cout << temp->valA << ", " << temp->valB << " npourBA to " << apour << ", " << bpour << endl;
		makeGraph(pouredBA);
	}
	else if (temp->npourBA == nullptr && temp->valB != 0) {
		temp->npourBA = search(apour, bpour);
		//cout << temp->valA << ", " << temp->valB << " npourBA to " << apour << ", " << bpour << endl;
	}
}