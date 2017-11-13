//NAME: Marky Santos-Tankia
//SECTION: A

#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <queue>
#include <vector>

using namespace std;

//Neighbouring struct
struct Neighbour
{
	string m_neighbourName;
	int m_neighbourWeight;
};

//Location struct nodes within the graph class
struct Location
{
	string m_locationName;
	int m_numNeighbours;
	Neighbour *head;
};

struct LocationDistance
{
	Location l;
	int distance; //-1 is infinite
};

class LocationDistanceComparator
{
  public:
    bool operator()(LocationDistance a,LocationDistance b) //friend or public
    {
     return a.distance>b.distance; //< max heap,> min heap
    }
};


//Graph class
class Graph
{

	public:
    string m_graphName;
    int m_graphNumber;
    Location *array;
    LocationDistance *ldTable;//airport to robotbar

		//constructor
		Graph() : m_graphName(" "), m_graphNumber(0), array(NULL),ldTable(NULL) {}

		//creates Location graph
		void buildGraph();
		
		//finds airport
		Location find(string locationName);

		//gives number of locations in the graph
		int getGraphNumber() { return m_graphNumber; }

		//gives the Location from the array of locations
		Location getLocation(int index) { return array[index]; }

    void buildldTable();//graph must be built before executing this

    int findldTable(LocationDistance ld);//ldtable must be built before executing this

    int shortestPath (Location v,Location w);

		

		//destructor, clears the graph
		~Graph();

};

#endif