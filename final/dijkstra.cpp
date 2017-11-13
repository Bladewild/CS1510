//NAME: Marky Santos-Tankia
//SECTION: A

#include <iostream>
using namespace std;

#include "graph.h"
//#include "graph.cpp"

//function declarations

int main()
{
	int minToken;
	int numCities;
	cin >> numCities;

	for(int i = 0; i < numCities; i++)
	{
		Graph city;
		city.buildGraph();
    city.buildldTable();

    Location v=city.find("airport");
    Location w=city.find("robotbar");
		minToken= city.shortestPath(v,w);
		cout<<"#"<<(i+1)<<" : "<<city.m_graphName<<", "<<minToken<<" tokens."<<endl;

	}


	return 0;
}