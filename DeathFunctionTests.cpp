/*
Test death function of Animats to determine if an artifical carrying capacity has been created
*/

#include <iostream>
#include <time.h>
#include <string>
#include <vector>

using namespace std;

//method declaration
int deathFunction(int); //determines number of deaths

int main()
{
	//variables
	srand(time(NULL)); //random number voo-doo
	int population = 10; //starting population

	//main testing
	for (;;)
	{
		cout << "Starting Population: " << population << endl;

		population = deathFunction(population); //run death algorithm
		cout << "Death Count: " << population << endl;

		population *= 2; //double population similar to reproduction
		cout << "Ending Population: " << population << endl;
	
		system("pause&cls");
	}

	//end program
	system("pause");
	return 0;
}

int deathFunction(int population) //determines number of deaths
{
	//variables
	int rNum, dead = 0;
	vector <bool> animats(population); //create population of animats with the passed size

	//run death algorithm
	for (int a = 0; a < population; a++) //go through current generation...
	{
		rNum = rand() % population;

		for (int b = 0; b < a; b++) //check every number from 0 to their rank to see if they died
		{
			if (rNum == b) //if the range includes the animat's number, it dies off
			{
				animats[a] = 0; //kill animat
				dead++;
			}
		}
	}

	return dead;
}