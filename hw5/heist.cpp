//NAME: Marky Santos-Tankia
//SECTION: A

#include <iostream>
#include <string>
using namespace std;

//function declarations
bool quest(int testX, int testY, char** map);
bool isValid(int testX, int testY);

int directions[4][2];
int start[2];
int end[2];
char **map;
int row = 1, col = 1;
int count = 0;

int main()
{

	//x,y

	// North
	directions[0][0] = 0;
	directions[0][1] = 1;
	// East
	directions[1][0] = 1;
	directions[1][1] = 0;
	// West
	directions[2][0] = -1;
	directions[2][1] =  0;
	// South
	directions[3][0] =  0;
	directions[3][1] = -1;

	while(col != 0 || row != 0)
	{
		
		// Get the size of the map
		cin >> row >> col; //y,x
		cin.ignore();

		if(row != 0 && col != 0)
		{
			// Creates rows of the map
			map = new char*[row];//y portion
			for(int i = 0; i < row; i++) //adds the coloumns/x of the map
			{
				map[i] = new char[col + 1];
				cin.getline(map[i], col+1);
			}

			// Find start/end
			for(int i = 0; i < row; i++)//y
			{
				for(int j = 0; j < col+1; j++)//x
				{
					if(map[i][j] == 'B')
					{
						start[0] = j;//x
						start[1] = i;//y
					} 
					else if(map[i][j] == 'E')
					{
						end[0] = j;//x
						end[1] = i;//y
					}
				}
			}

			// Check if solvable and solve
			if(!quest(start[0], start[1], map))
				cout << "Map is cannot be solved" << endl;
			else 
			{
				// Reintroduce exit and bender
				map[start[1]][start[0]] = 'B';
				map[end[1]][end[0]] = 'E';
				
				//Prints Map w/ path
				cout << "Map : " << count << endl;
				count++;
				for(int i = 0; i < row; i++)
					cout << map[i] << endl;
				cout << endl;
			}
		}
	}

	//De-allocates Map
  	for(int k=0; k < row; k++)
    	delete [] map[k];
  	delete [] map;

	return 0;
}

//quest function
bool quest(int testX, int testY, char** map)
{
	int newX, newY;
	//Does all possible turns, till valid
	for(int choice = 0; choice < 4; choice ++)
	{
		//cout<<"Choosing direction..."<<endl;
		

		newX = testX + directions[choice][0];
		newY = testY + directions[choice][1];

		//Check validity, if value is possible then it continues
		if(isValid(newX, newY))
		{
			//cout<<"Valid direction..."<<endl;
			//map[y][x]
			map[newY][newX] = '.';
			//cout<<"Dot was placed..."<<endl;
			if(newX == end[0] && newY == end[1])
			{
				//cout<<"End has been reached!!!"<<endl;
				return true;
			}
			else 
			{
				bool success = quest(newX, newY, map);
				if(success)
				{
					//cout<<"VALID PATH!!!!"<<endl;
					return true;
				}
				else
				{
					map[newY][newX] = ' ';
					//cout<<"ERASING DOT..."<<endl;
				}
			}
		}
	}
	return false;
}

//valid function
bool isValid(int testX, int testY)
{
	//cout<<"Validating direction..."<<endl;

	//Check if testY and testX are in bounds
	bool succeed = true;
	if(testX < 0 || testY < 0 || testX >= col || testY >= row)
		succeed = false;
	//Check the map if the bounds are inside array
	if(succeed)
	{
		if(map[testY][testX] == 'T')
			succeed = false;
		if(map[testY][testX] == '#')
			succeed = false;
		if(map[testY][testX] == '.')
			succeed = false;
	}
	return succeed;
}
