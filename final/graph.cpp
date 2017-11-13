//NAME: Marky Santos-Tankia
//SECTION: A

#include "graph.h"


void Graph::buildGraph()
{
	m_graphNumber = 0;
	cin >> m_graphName >> m_graphNumber; //NewNewYork 4

	array = new Location [m_graphNumber];

	for(int i = 0; i < m_graphNumber; i++)
	{
		cin >> array[i].m_locationName >> array[i].m_numNeighbours; //airport 1
		
		array[i].head = new Neighbour [array[i].m_numNeighbours];
		
		for(int j = 0; j < array[i].m_numNeighbours; j++)
			cin >> array[i].head[j].m_neighbourName >> array[i].head[j].m_neighbourWeight;
	}
}

void Graph::buildldTable()//graph must be built before executing this
{
	ldTable = new LocationDistance [m_graphNumber];
  for(int i = 0; i < m_graphNumber; i++)
  {
    ldTable[i].l=array[i];
    ldTable[i].distance=-1;
  }
}
int Graph::findldTable(LocationDistance ld)//ldTable must be built before executing this
{
  for(int i = 0; i < m_graphNumber; i++)
  {
    if(ldTable[i].l.m_locationName==ld.l.m_locationName)
      return i;
  }
  return -1;//not found
}


Location Graph::find(string locationName)
{
	for(int i = 0; i < m_graphNumber; i++)
	{
		if(array[i].m_locationName == locationName)
			return array[i];
	}
	cout << "ERROR:"<<locationName<<" is not found in the city" << endl;
	//returns first Location if locationname is not stated; not necessary
	return array[0];
}

int Graph::shortestPath (Location v,Location w)
{	
	priority_queue<LocationDistance,vector<LocationDistance>,LocationDistanceComparator > H;

	LocationDistance ldStart;
	ldStart.l=v;
	ldStart.distance=0;

	H.push(ldStart);
	
	int pos_Start=findldTable(ldStart);
	ldTable[pos_Start].distance=0;

	while (!(H.empty()) )
	{	
		LocationDistance u= H.top(); //a node u and its distance du (distance to node u from origin)
    //cout<<"Top of Stack: "<<u.l.m_locationName<<" "<<u.distance<<endl;
		H.pop();
    int pos_u=findldTable(u);

		if(u.l.m_locationName==w.m_locationName)
			return u.distance;
		else if (u.distance <ldTable[pos_u].distance || ldTable[pos_u].distance==-1) //always refers to the smallest one
			ldTable[pos_Start].distance=u.distance;
		
    for(int i=0;i<u.l.m_numNeighbours;i++)
		{
      LocationDistance neighbour_ld;
      Location neighbour=find(u.l.head[i].m_neighbourName);
      int neighbourWeight=u.l.head[i].m_neighbourWeight;

      neighbour_ld.distance= u.distance+neighbourWeight;
      neighbour_ld.l=neighbour;

			H.push(neighbour_ld);
		}
	}
	return -1;//fail			
}

Graph::~Graph()
{
	for(int i = 0; i < m_graphNumber; i++)
	{
		delete [] array[i].head;
	}
	delete [] array;
	array = NULL;
  delete [] ldTable;
  ldTable = NULL;
}

