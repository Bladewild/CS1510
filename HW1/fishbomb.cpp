/*
	Marky (Alain Markus) P. Santos-Tankia 1A
	Homework 1 CS1510

*/
using namespace std;
#include <iostream>

int main()
{
	int num_testCases;
	int gridHeight,gridWidth; 
	int **grid=NULL;
	int num_fish;
	int bombY,bombX;
	cin>>num_testCases;
	for(int i=0;i<num_testCases;i++)
	{

		cin>>gridHeight>>gridWidth;
		//cout<<"Grid is "<<gridHeight<<"x"<<gridWidth<<endl;
		grid =new int*[gridHeight];
		for(int j=0;j<gridHeight;j++)//Creates Coloumns
		  grid[j]=new int[gridWidth];

		for(int j=0;j<gridHeight;j++)//Row
		{
			for(int k=0;k<gridWidth;k++)//Coloumn
    	{
    		cin>>grid[j][k];
    	  //cout<<grid[j][k]<<" ";
    	}
    	   //cout<<endl;

		}
     //cout<<endl;
		for(int j=0;j<3;j++) //Places and detonates bombs. Catches fish
		{
    	cin>>bombY>>bombX;

     	//Row=y, Coloumn=x;
    	//cout<<"Bomb Thrown at "<<bombY<<"x"<<bombX<<endl;
    	for(int k=bombY-2;k<=bombY+2;k++)//Row
			{
				for(int l=bombX-2;l<=bombX+2;l++)//Coloumn
    		{

    	  	//cout<<grid[k][l]<<" ";
    			num_fish+=grid[k][l];
    			grid[k][l]=0;
    		}
    	  //cout<<endl;
			}
			//cout<<endl;
		}
		cout<<"#"<<i<<": Bender catches "
		    <<num_fish<<" fish"<<endl;
		num_fish=0; //reset fish count;
		//clean array
		for(int j=0;j<gridHeight;j++)
			delete [] grid[j];
	}
	delete [] grid;
	grid=NULL;
	return 0;
}
