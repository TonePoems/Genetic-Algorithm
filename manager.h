/*
5/2/2017
Class keeping track of multiple generations and running tests, based on the ending criteria
*/

#include "generation.h"
#include <iomanip> //formatting output
#include <conio.h> //rapid input
#include <sstream>

class manager
{
public:
	//constructors
	manager(); //default constructor
	manager(int, double, int, bool); //overloaded constructor, takes the ending type and value, starting population size, oneStep

	//methods
	//setters
	void setEndingType(int); //sets ending condition type
	void setEndingValue(double); //set ending value
	void setPrintVars(bool, bool, bool, bool, bool, bool, bool, bool); //sets what user wants to display
	void setOneStep(bool); //set one step variable
	void setPrintFunctions(bool, bool, bool, bool); //bools to tell if user wants to print out messages from actions

	//getters
	int getEndingType(); //gets ending condition type
	double getEndingValue(); //gets ending value

	//custom
	void setStartPop(int); //creates the first generation with passed number of animats

	void runTest(); //runs tests on parameters set by user

	void compareStats(); //prints all stats for test

	void menu(); //provides user with options to change the testing

private:
	//variables
	vector <generation> epoch; //holds generations, starting at size 0

	/* Ending conditions
		1 = reach a specific number of generations
		2 = reach a specific average score
		3 = reach a specific median score
		4 = reach a specific minimum score
		5 = reach a specific maximum score
	*/
	int endingType; //saves what ending method the user would like
	double endingValue; //ending condition based on what ending type selected

	//stat printing settings variables
	bool populationB;
	bool deathB;
	bool meanB;
	bool medianB;
	bool modeB;
	bool rangeB;
	bool maxB;
	bool minB;

	bool oneStep; //move testing by one step at a time, simply adds a system pause between generations

	//stats for printing functions
	bool runB;
	bool rankB;
	bool dieB;
	bool reproduceB;

	//vectors for saving stats for the entire test
	vector <int> population;
	vector <int> deathCount;
	vector <double> mean;
	vector <double> median;
	vector <int> mode;
	vector <int> range;
	vector <int> min;
	vector <int> max;
};

//constructors
manager::manager() //default constructor
{
	epoch.resize(5); //set size to 5
	endingType = 1; //set ending condition to number of generations
	endingValue = 5; //use 5 generations
}
manager::manager(int t, double v, int p , bool o) //overloaded constructor, takes the ending type and value, starting population size, oneStep
{
	if (t == 1) //if user selects cutoff at number of generations, set that number of generations
	{
		epoch.resize(v); //set size of test to number of turns
	}
	else //if user does not set limit on generations, set background limit
	{
		epoch.resize(999); //set size limit for testing
	}
	endingType = t; //set ending type
	endingValue = v; //set ending value
	epoch[0].makeFirstGen(p); //create first generation with p members
	oneStep = o; //set onestep
}

//methods
//setters
void manager::setEndingType(int e) //sets ending condition type
{
	endingType = e;
}
void manager::setEndingValue(double e) //set ending value
{
	endingValue = e;
}
void manager::setPrintVars(bool p1, bool p2, bool p3, bool p4, bool p5, bool p6, bool p7, bool p8) //sets what user wants to display
{
	//set printing settings variables
	populationB = p1;
	deathB = p2;
	meanB = p3;
	medianB = p4;
	modeB = p5;
	rangeB = p6;
	maxB = p7;
	minB = p8;
}
void manager::setOneStep(bool o) //set one step variable
{
	oneStep = o;
}
void manager::setPrintFunctions(bool p1, bool p2, bool p3, bool p4) //bools to tell if user wants to print out messages from actions
{
	//set printing function variables
	runB = p1;
	rankB = p2;
	dieB = p3;
	reproduceB = p4;
}

//getters
int manager::getEndingType() //gets ending condition type
{
	return endingType;
}
double manager::getEndingValue() //gets ending value
{
	return endingValue;
}

//custom
//creates the first generation with passed number of animats
void manager::setStartPop(int p)
{
	epoch[0].makeFirstGen(p); //create first generation with p members
}

//runs tests on parameters set by user
void manager::runTest()
{
	system("cls");
	if (!populationB || !deathB || !meanB || !medianB || !modeB || !rangeB || !maxB || !minB || !runB || !rankB || !dieB || !reproduceB) //test if user wants anything printed...
	{
		cout << "Testing..." << endl; //if nothing is being printed, print message to user
	}

	//initalize sizes of stat vectors
	population.resize(0);
	deathCount.resize(0);
	mean.resize(0);
	median.resize (0);
	mode.resize(0);
	range.resize(0);
	min.resize(0);
	max.resize(0);

	int a = 0; //initalize loop counter

	switch (endingType) //switchcase for all of ending types
	{
	case 1: //reach a specific number of generations~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		for (a = 0; a < endingValue; a++) //keep going for each generation...
		{
			if (populationB || deathB || meanB || medianB || modeB || rangeB || maxB || minB || runB || rankB || dieB || reproduceB) //test if user wants anything printed...
			{
				cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
				cout << "Generation " << a + 1 << endl;
			}
			epoch[a].runSim(runB); //run the simulation
			epoch[a].rankAnimats(rankB); //rank based on score
			epoch[a].calcStats(); //calculate stats for each generation
			epoch[a].dieOff(dieB); //determine who dies off
			epoch[a].printStats(populationB, deathB, meanB, medianB, modeB, rangeB, maxB, minB); //print the specified stats

			//save stats
			population.resize(population.size() + 1); //resize
			population[a] = epoch[a].getPopulation(); //save population

			deathCount.resize(deathCount.size() + 1); //resize;
			deathCount[a] = epoch[a].getDead(); //save deathCount

			mean.resize(mean.size() + 1); //resize
			mean[a] = epoch[a].getMean(); //save mean

			median.resize(median.size() + 1); //resize
			median[a] = epoch[a].getMedian(); //save median

			mode.resize(mode.size() + 1); //resize
			mode[a] = epoch[a].getMode(); //save mode

			range.resize(range.size() + 1); //resize
			range[a] = epoch[a].getRange(); //save range

			min.resize(min.size() + 1); //resize
			min[a] = epoch[a].getMinScore(); //save min

			max.resize(max.size() + 1); //resize
			max[a] = epoch[a].getMaxScore(); //save max


			if (oneStep) //if user wants to oneStep through testing...
			{
				system("pause"); //add breaks
			}
			if (a != endingValue - 1) //if it is not on the last generation, reproduce
			{
				epoch[a + 1] = epoch[a].reproduce(epoch[a + 1], reproduceB); //reproduce animats
			}
		}
		break;

	case 2: //reach a specific average score
		do //loop the test
		{
			if (populationB || deathB || meanB || medianB || modeB || rangeB || maxB || minB || runB || rankB || dieB || reproduceB) //test if user wants anything printed...
			{
				cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
				cout << "Generation " << a + 1 << endl;
			}
			
			epoch[a].runSim(runB); //run the simulation
			epoch[a].rankAnimats(rankB); //rank based on score
			epoch[a].calcStats(); //calculate stats for each generation
			epoch[a].dieOff(dieB); //determine who dies off
			epoch[a].printStats(populationB, deathB, meanB, medianB, modeB, rangeB, maxB, minB); //print the specified stats

																								 //save stats
			population.resize(population.size() + 1); //resize
			population[a] = epoch[a].getPopulation(); //save population

			deathCount.resize(deathCount.size() + 1); //resize;
			deathCount[a] = epoch[a].getDead(); //save deathCount

			mean.resize(mean.size() + 1); //resize
			mean[a] = epoch[a].getMean(); //save mean

			median.resize(median.size() + 1); //resize
			median[a] = epoch[a].getMedian(); //save median

			mode.resize(mode.size() + 1); //resize
			mode[a] = epoch[a].getMode(); //save mode

			range.resize(range.size() + 1); //resize
			range[a] = epoch[a].getRange(); //save range

			min.resize(min.size() + 1); //resize
			min[a] = epoch[a].getMinScore(); //save min

			max.resize(max.size() + 1); //resize
			max[a] = epoch[a].getMaxScore(); //save max


			if (oneStep) //if user wants to oneStep through testing...
			{
				system("pause"); //add breaks
			}
			if (a != 998) //if it is not on the last generation, reproduce
			{
				epoch[a + 1] = epoch[a].reproduce(epoch[a + 1], reproduceB); //reproduce animats
			}
			a++; //loop counter
		} while (a < 200 && epoch[a - 1].getMean() < endingValue); //loop while the program does not hit either ending case

		if (epoch[a - 1].getMean() < endingValue) //if program ends without hitting the mean value limit...
		{
			cout << endl << "The test was not able to reach a mean of " << endingValue << " in 999 generations." << endl; //inform user
		}
		else //if the mean was achieved...
		{
			cout << endl << "A mean score of " << endingValue << " was reached in " << a << " generations." << endl;
		}
		break;

	case 3: //reach a specific median score~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		do //loop the test
		{
			if (populationB || deathB || meanB || medianB || modeB || rangeB || maxB || minB || runB || rankB || dieB || reproduceB) //test if user wants anything printed...
			{
				cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
				cout << "Generation " << a + 1 << endl;
			}

			epoch[a].runSim(runB); //run the simulation
			epoch[a].rankAnimats(rankB); //rank based on score
			epoch[a].calcStats(); //calculate stats for each generation
			epoch[a].dieOff(dieB); //determine who dies off
			epoch[a].printStats(populationB, deathB, meanB, medianB, modeB, rangeB, maxB, minB); //print the specified stats

																								 //save stats
			population.resize(population.size() + 1); //resize
			population[a] = epoch[a].getPopulation(); //save population

			deathCount.resize(deathCount.size() + 1); //resize;
			deathCount[a] = epoch[a].getDead(); //save deathCount

			mean.resize(mean.size() + 1); //resize
			mean[a] = epoch[a].getMean(); //save mean

			median.resize(median.size() + 1); //resize
			median[a] = epoch[a].getMedian(); //save median

			mode.resize(mode.size() + 1); //resize
			mode[a] = epoch[a].getMode(); //save mode

			range.resize(range.size() + 1); //resize
			range[a] = epoch[a].getRange(); //save range

			min.resize(min.size() + 1); //resize
			min[a] = epoch[a].getMinScore(); //save min

			max.resize(max.size() + 1); //resize
			max[a] = epoch[a].getMaxScore(); //save max


			if (oneStep) //if user wants to oneStep through testing...
			{
				system("pause"); //add breaks
			}
			if (a != 998) //if it is not on the last generation, reproduce
			{
				epoch[a + 1] = epoch[a].reproduce(epoch[a + 1], reproduceB); //reproduce animats
			}
			a++; //loop counter
		} while (a < 200 && epoch[a - 1].getMedian() < endingValue); //loop while the program does not hit either ending case

		if (epoch[a - 1].getMedian() < endingValue) //if program ends without hitting the median value limit...
		{
			cout << endl << "The test was not able to reach a median of " << endingValue << " in 999 generations." << endl; //inform user
		}
		else //if the median was achieved...
		{
			cout << endl << "A median score of " << endingValue << " was reached in " << a << " generations." << endl;
		}
		break;

	case 4: //reach a specific minimum score~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		do //loop the test
		{
			if (populationB || deathB || meanB || medianB || modeB || rangeB || maxB || minB || runB || rankB || dieB || reproduceB) //test if user wants anything printed...
			{
				cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
				cout << "Generation " << a + 1 << endl;
			}

			epoch[a].runSim(runB); //run the simulation
			epoch[a].rankAnimats(rankB); //rank based on score
			epoch[a].calcStats(); //calculate stats for each generation
			epoch[a].dieOff(dieB); //determine who dies off
			epoch[a].printStats(populationB, deathB, meanB, medianB, modeB, rangeB, maxB, minB); //print the specified stats

																								 //save stats
			population.resize(population.size() + 1); //resize
			population[a] = epoch[a].getPopulation(); //save population

			deathCount.resize(deathCount.size() + 1); //resize;
			deathCount[a] = epoch[a].getDead(); //save deathCount

			mean.resize(mean.size() + 1); //resize
			mean[a] = epoch[a].getMean(); //save mean

			median.resize(median.size() + 1); //resize
			median[a] = epoch[a].getMedian(); //save median

			mode.resize(mode.size() + 1); //resize
			mode[a] = epoch[a].getMode(); //save mode

			range.resize(range.size() + 1); //resize
			range[a] = epoch[a].getRange(); //save range

			min.resize(min.size() + 1); //resize
			min[a] = epoch[a].getMinScore(); //save min

			max.resize(max.size() + 1); //resize
			max[a] = epoch[a].getMaxScore(); //save max


			if (oneStep) //if user wants to oneStep through testing...
			{
				system("pause"); //add breaks
			}
			if (a != 998) //if it is not on the last generation, reproduce
			{
				epoch[a + 1] = epoch[a].reproduce(epoch[a + 1], reproduceB); //reproduce animats
			}
			a++; //loop counter
		} while (a < 200 && epoch[a - 1].getMinScore() < endingValue); //loop while the program does not hit either ending case

		if (epoch[a - 1].getMinScore() < endingValue) //if program ends without hitting the min value limit...
		{
			cout << endl << "The test was not able to reach a minimum score of " << endingValue << " in 999 generations." << endl; //inform user
		}
		else //if the min value was achieved...
		{
			cout << endl << "A minimum score of " << endingValue << " was reached in " << a << " generations." << endl;
		}
		break;

	case 5: //reach a specific maximum score~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		do //loop the test
		{
			if (populationB || deathB || meanB || medianB || modeB || rangeB || maxB || minB || runB || rankB || dieB || reproduceB) //test if user wants anything printed...
			{
				cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
				cout << "Generation " << a + 1 << endl;
			}

			epoch[a].runSim(runB); //run the simulation
			epoch[a].rankAnimats(rankB); //rank based on score
			epoch[a].calcStats(); //calculate stats for each generation
			epoch[a].dieOff(dieB); //determine who dies off
			epoch[a].printStats(populationB, deathB, meanB, medianB, modeB, rangeB, maxB, minB); //print the specified stats

																								 //save stats
			population.resize(population.size() + 1); //resize
			population[a] = epoch[a].getPopulation(); //save population

			deathCount.resize(deathCount.size() + 1); //resize;
			deathCount[a] = epoch[a].getDead(); //save deathCount

			mean.resize(mean.size() + 1); //resize
			mean[a] = epoch[a].getMean(); //save mean

			median.resize(median.size() + 1); //resize
			median[a] = epoch[a].getMedian(); //save median

			mode.resize(mode.size() + 1); //resize
			mode[a] = epoch[a].getMode(); //save mode

			range.resize(range.size() + 1); //resize
			range[a] = epoch[a].getRange(); //save range

			min.resize(min.size() + 1); //resize
			min[a] = epoch[a].getMinScore(); //save min

			max.resize(max.size() + 1); //resize
			max[a] = epoch[a].getMaxScore(); //save max


			if (oneStep) //if user wants to oneStep through testing...
			{
				system("pause"); //add breaks
			}
			if (a != 998) //if it is not on the last generation, reproduce
			{
				epoch[a + 1] = epoch[a].reproduce(epoch[a + 1], reproduceB); //reproduce animats
			}
			a++; //loop counter
		} while (a < 200 && epoch[a - 1].getMaxScore() < endingValue); //loop while the program does not hit either ending case

		if (epoch[a - 1].getMaxScore() < endingValue) //if program ends without hitting the max value limit...
		{
			cout << endl << "The test was not able to reach a maximum score of " << endingValue << " in 999 generations." << endl; //inform user
		}
		else //if the max was achieved...
		{
			cout << endl << "A maximum score of " << endingValue << " was reached in " << a << " generations." << endl;
		}
		break;
	}

	if (populationB || deathB || meanB || medianB || modeB || rangeB || maxB || minB || runB || rankB || dieB || reproduceB) //test if user wants anything printed...
	{
		system("pause");
	}
	system("cls");
}

 //prints all stats for review
void manager::compareStats()
{
	//print top banner
	cout << "Overview of Stats" << endl << endl;
	cout << right << setw(3) << "Gen" << setw(15) << "Population" << setw(10) << "Dead" << setw(15) << "Mean" << setw(10) << "Median" << setw(10) << "Mode" << setw(10) << "Range" << setw(10) << "Max" << setw(10) << "Min" << endl;
	cout << "_____________________________________________________________________________________________" << endl;
	for (int a = 0; a < population.size(); a++) //go through for the number of generations
	{
		cout << setw(3) << a + 1 << setw(15) << population[a] << setw(10) << deathCount[a] << setw(15) << mean[a] << setw(10) << median[a] << setw(10) << mode[a] << setw(10) << range[a] << setw(10) << max[a] << setw(10) << min[a] << endl;
	}
	cout << endl; //add another line of empty space
}

//provides user with options to change the testing
void manager::menu()
{
	//variables
	char input = 'a'; //stores user selection
	stringstream ss; //convert inputs
	double temp; //saves value to use
	
	//start selection menu for generation settings
	cout << "Let's set up your test" << endl << endl;

	//set ending type
	cout << "1: Reach a specific number of generations" << endl;
	cout << "2: Reach a specific average score" << endl;
	cout << "3: Reach a specific median score" << endl;
	cout << "4: Reach a specific minimum score" << endl;
	cout << "5: Reach a specific maximum score" << endl << endl;
	cout << "Please enter your selection: ";

	do
	{
		if (_kbhit()) //check if key is pressed
		{
			input = _getch(); //save input
		}
	} while (input != '1' && input != '2' &&input != '3' &&input != '4' &&input != '5');

	ss << input;
	ss >> temp;
	ss.clear();

	endingType = temp; //save ending type

	cout << endingType << endl;

	//set ending Value
	cout << endl; //skip lines

	do
	{
		cout << "Please enter the ";
		switch (endingType)
		{
		case 1:
			cout << "number of generations to reach: ";
			break;
		case 2:
			cout << "average score to reach: ";
			break;
		case 3:
			cout << "median score to reach: ";
			break;
		case 4:
			cout << "minimum score to reach: ";
			break;
		case 5:
			cout << "maximum score to reach: ";
			break;
		}

		cin >> temp; //get input

		if (temp < 1) //check if key is pressed
		{
			cout << endl << "Error: Please enter a number larger than 0." << endl;
			system("pause&cls");
		}
	} while (temp < 1);

	endingValue = temp; //save ending type

	if (endingType == 1) //if user selects cutoff at number of generations, set that number of generations
	{
		epoch.resize(endingValue); //set size of test to number of turns
	}
	else //if user does not set limit on generations, set background limit
	{
		epoch.resize(999); //set size limit for testing
	}

	cout << endl; //skip line

	do
	{
		cout << "Please enter the size of the starting population: ";

		cin >> temp; //get input

		if (temp < 10) //check if key is pressed
		{
			cout << endl << "Error: Please enter a number larger than 9." << endl;
			system("pause&cls");
		}
	} while (temp < 10);

	epoch[0].makeFirstGen(temp); //create first generation with temp members

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	system("cls");

	//start selection menu for print stat settings
	cout << "What statistics would you like to see for each generation?" << endl << endl;

	cout << left << setw(20) << "1: Population " << setw(3) << populationB << endl;
	cout << setw(20) << "2: Death Count " << setw(3) << deathB << endl;
	cout << setw(20) << "3: Mean Score " << setw(3) << meanB << endl;
	cout << setw(20) << "4: Median Score " << setw(3) << medianB << endl;
	cout << setw(20) << "5: Mode Score " << setw(3) << modeB << endl;
	cout << setw(20) << "6: Range " << setw(3) << rangeB << endl;
	cout << setw(20) << "7: Max Score " << setw(3) << maxB << endl;
	cout << setw(20) << "8: Min Score " << setw(3) << minB << endl;
	cout << endl << setw(20) << "9: Select All " << endl;
	cout << setw(20) << "0: Deselect All " << endl;
	cout << endl << setw(20) << "Space: Done" << endl;

	do
	{
		if (_kbhit()) //check if key is pressed
		{
			input = _getch(); //save input

			switch (input)
			{
			case '1':
				if (populationB) //switch population bool state
					populationB = 0;
				else
					populationB = 1;
				break;

			case '2':
				if (deathB) //switch death bool state
					deathB = 0;
				else
					deathB = 1;
				break;

			case '3':
				if (meanB) //switch meanB bool state
					meanB = 0;
				else
					meanB = 1;
				break;

			case '4':
				if (medianB) //switch medianB bool state
					medianB = 0;
				else
					medianB = 1;
				break;

			case '5':
				if (modeB) //switch modeB bool state
					modeB = 0;
				else
					modeB = 1;
				break;

			case '6':
				if (rangeB) //switch rangeB bool state
					rangeB = 0;
				else
					rangeB = 1;
				break;

			case '7':
				if (maxB) //switch maxB bool state
					maxB = 0;
				else
					maxB = 1;
				break;

			case '8':
				if (minB) //switch minB bool state
					minB = 0;
				else
					minB = 1;
				break;
			case '9': //set all states 1
				populationB = 1;
				deathB = 1;
				meanB = 1;
				medianB = 1;
				modeB = 1;
				rangeB = 1;
				maxB = 1;
				minB = 1;
				break;

			case '0': //set all states 0
				populationB = 0;
				deathB = 0;
				meanB = 0;
				medianB = 0;
				modeB = 0;
				rangeB = 0;
				maxB = 0;
				minB = 0;
				break;
			}

			system("cls"); //clear and print updated screen

			cout << "What statistics would you like to see for each generation?" << endl << endl;

			cout << left << setw(20) << "1: Population " << setw(3) << populationB << endl;
			cout << setw(20) << "2: Death Count " << setw(3) << deathB << endl;
			cout << setw(20) << "3: Mean Score " << setw(3) << meanB << endl;
			cout << setw(20) << "4: Median Score " << setw(3) << medianB << endl;
			cout << setw(20) << "5: Mode Score " << setw(3) << modeB << endl;
			cout << setw(20) << "6: Range " << setw(3) << rangeB << endl;
			cout << setw(20) << "7: Max Score " << setw(3) << maxB << endl;
			cout << setw(20) << "8: Min Score " << setw(3) << minB << endl;
			cout << endl << setw(20) << "9: Select All " << endl;
			cout << setw(20) << "0: Deselect All " << endl;
			cout << endl << setw(20) << "Space: Done" << endl;
		}
	} while (input != ' ');

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	system("cls"); //clear screen

	input = 'a'; //reset input
	//start selection menu for print stat settings
	cout << "What functions would you like to see during testing?" << endl << endl;

	cout << left << setw(20) << "1: Inital Scores " << setw(3) << runB << endl;
	cout << setw(20) << "2: Ranked Scores " << setw(3) << rankB << endl;
	cout << setw(20) << "3: List Dead " << setw(3) << dieB << endl;
	cout << setw(20) << "4: Next Gen's Genes " << setw(3) << reproduceB << endl;
	cout << setw(20) << "5: One Step " << setw(3) << oneStep << endl;
	cout << endl << setw(20) << "9: Select All " << endl;
	cout << setw(20) << "0: Deselect All " << endl;
	cout << endl << setw(20) << "Space: Done" << endl;

	do
	{
		if (_kbhit()) //check if key is pressed
		{
			input = _getch(); //save input

			switch (input)
			{
			case '1':
				if (runB) //switch runB bool state
					runB = 0;
				else
					runB = 1;
				break;

			case '2':
				if (rankB) //switch rankB bool state
					rankB = 0;
				else
					rankB = 1;
				break;

			case '3':
				if (dieB) //switch dieB bool state
					dieB = 0;
				else
					dieB = 1;
				break;

			case '4':
				if (reproduceB) //switch reproduceB bool state
					reproduceB = 0;
				else
					reproduceB = 1;
				break;

			case '5':
				if (oneStep) //switch oneStep bool state
					oneStep = 0;
				else
					oneStep = 1;
				break;

			case '9': //set all states 1
				runB = 1;
				rankB = 1;
				dieB = 1;
				reproduceB = 1;
				oneStep = 1;
				break;

			case '0': //set all states 0
				runB = 0;
				rankB = 0;
				dieB = 0;
				reproduceB = 0;
				oneStep = 0;
				break;
			}

			system("cls"); //clear and print updated screen

			cout << "What functions would you like to see during testing?" << endl << endl;

			cout << left << setw(20) << "1: Inital Scores " << setw(3) << runB << endl;
			cout << setw(20) << "2: Ranked Scores " << setw(3) << rankB << endl;
			cout << setw(20) << "3: List Dead " << setw(3) << dieB << endl;
			cout << setw(20) << "4: Next Gen's Genes " << setw(3) << reproduceB << endl;
			cout << setw(20) << "5: One Step " << setw(3) << oneStep << endl;
			cout << endl << setw(20) << "9: Select All " << endl;
			cout << setw(20) << "0: Deselect All " << endl;
			cout << endl << setw(20) << "Space: Done" << endl;
		}
	} while (input != ' ');
}