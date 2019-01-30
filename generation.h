/*
4/19/2017
Class keeping track of an entire generation of animats in a vector
*/

#include "animat.h"
#include <vector> //to hold the animats in a generation
#include <algorithm> //to sort the	genration by skill level, aka: score
#include <math.h> //creating statistics for generations

class generation
{
public:
	//constructors
	generation(); //default constructor
	generation(int); //overloaded constructor, takes the number of animats in the generation

	//methods
	//setters
	void setGen(int); //sets the generation number
	void setPopulation(int); //sets the number of animats to create and hold

	//getters
	int getAnimatScore(int); //returns the animat at position "int" in the generation
	int getGen(); //returns the generation number
	int getPopulation(); //returns the number on animats in the generation
	int getDead(); //returns number of dead
	double getMean(); //returns mean of scores in generation
	double getMedian(); //returns median of scores in generation
	int getMode(); //returns mode of scores in generation
	int getRange(); //returns the range of scores in generation
	int getMinScore(); //returns minimum score
	int getMaxScore(); //returns maximum score

	//custom
	void addAnimat(animat); //add another animat to the generation

	void rankAnimats(bool); //re-order the list of animats based on skill level

	generation reproduce(generation, bool); //reproduces animats, varies traits, adds mutations

	void makeFirstGen(int); //creates 100 standard animats for first generation

	void randomize(); //randomize scores

	void dieOff(bool); //determines which animats die

	void runSim(bool); //run simulation to test the animats' skills

	void calcStats(); //calculats mean, median, mode, and range of generation's scores

	void printStats(bool, bool, bool, bool, bool, bool, bool, bool); //prints population, death count, mean, median, mode, range, max, min with options to select specific

private:
	//variables
	vector <animat> animats; //holds roughly 100 animats
	int gen; //holds the number of the generation for reference in the vector of generations
	int population; //holds the number of animats to create and hold
	int dead; //keeps track of dead animats

	double mean; //mean of all scores in the generation
	double median; //median of all scores in the generation
	int mode; //mode of all scores in the generation
	int range; //returns the range of scores in the generation
	int minScore; //minimum score for a generation
	int maxScore; //maximum score for a generation
};

//constructors
generation::generation() //default constructor
{
	dead = 0;
}
generation::generation(int p) //overloaded constructor, takes the number of animats in the generation
{
	population = p; //set population
	animats.resize(p); //set size of the generation vector
	dead = 0; //set number of dead animats to 0
}

//methods
//setters
void generation::setGen(int g) //sets the generation number
{
	gen = g;
}
void generation::setPopulation(int p) //sets the number of animats to create and hold
{
	population = p;
}

//getters
int generation::getAnimatScore(int a) //returns the animat at position "a" in the generation
{
	return animats[a].getScore();
}
int generation::getGen() //returns the generation number
{
	return gen;
}
int generation::getPopulation() //returns the number on animats in the generation
{
	return population;
}
int generation::getDead() //return number of dead
{
	return dead;
}
double generation::getMean() //returns mean of scores in generation
{
	return mean;
}
double generation::getMedian() //returns median of scores in generation
{
	return median;
}
int generation::getMode() //returns mode of scores in generation
{
	return mode;
}
int generation::getRange() //returns the range of scores in generation
{
	return range;
}
int generation::getMinScore() //reurns min score
{
	return minScore;
}
int generation::getMaxScore() //returns max score
{
	return maxScore;
}

//custom
//add another animat to the generation
void generation::addAnimat(animat) 
{

}

//friend function to tell sort function what parameter to search by
bool sortByScore(const animat& lhs, const animat& rhs) 
{
	return (lhs.score > rhs.score); //sort highest to lowest score
}
//re-order the list of animats based on skill level
void generation::rankAnimats(bool p) 
{
	sort(animats.begin(), animats.end(), sortByScore); //sort the vector of animats based on their scores

	///* //testing cout
	if (p) //if user wants to print...
	{
		cout << "________________________________________________________" << endl;
		cout << "Ranked" << endl;
		for (int a = 0; a < animats.size(); a++) //test output
		{
			cout << a << " Score: " << animats[a].getScore() << endl;
		}
	}
	//*/
}

//reproduces animats, varies traits, adds mutations
generation generation::reproduce(generation genB, bool p)
{
	if (p) //if user wants to print...
	{
		cout << "________________________________________________________" << endl;
		cout << "Reproduce" << endl;
	}

	genB.animats.resize(0);
	genB.setPopulation((population - dead) * 2); //calc 2nd population

	for (int a = 0; a < population; a++) //go through animat population...
	{
		if (animats[a].getAlive()) //if an animat is alive...
		{
			genB.animats.resize(genB.animats.size() + 2); //add two to the population of next gen

			//create two new animats with same traits of predicessor
			genB.animats[genB.animats.size() - 2] = animats[a]; //first offspring
			genB.animats[genB.animats.size() - 1] = animats[a]; //second offspring

			//genB.setPopulation(genB.getPopulation() + 2); //add two animats to the population size

			//vary traits of offspring
			genB.animats[genB.animats.size() - 2].reproduceVariation(); //first offspring
			genB.animats[genB.animats.size() - 1].reproduceVariation(); //second offspring

			//add mutations
			//genB[genB.animats.size() - 2].mutation(); //first offspring
			//genB[genB.animats.size() - 1].mutation(); //second offspring

			if (p) //if user wants to print...
			{
				cout << genB.animats[genB.animats.size() - 2].gene() << endl; //first offspring test output
				cout << genB.animats[genB.animats.size() - 1].gene() << endl; //second offspring test output
			}
		}
	}
	return genB;
}

//creates 100 standard animats for first generation
void generation::makeFirstGen(int p) 
{
	population = p; //set population
	animats.resize(population);
	/* Test creation of animats
	for (int a = 0; a < population; a++)
	{
		cout << a << " Gene: " << animats[a].gene() << endl;
	}
	*/
}

//randomize scores //used for testing
void generation::randomize()
{
	for (int a = 0; a < animats.size(); a++) //randomize the scores of the animats
	{
		animats[a].setScore(rand() % 20);
		//cout << a << " Score: " << animats[a].getScore() << endl; //test output
	}
}

 //determines which animats die
void generation::dieOff(bool p)
{
	//variables
	int rNum, chance; //random number holder and chance the animat has to die

	/* //old method
	for (int a = 0; a < population; a++) //go through current generation...
	{
		chance = population - a; //higher ranking means less chance to die
		rNum = rand() % chance;

		if (rNum == 0)
		{
			animats[a].setAlive(0); //kill animat
			dead++;
		}
	}
	*/

	///* //new method
	for (int a = 0; a < population; a++) //go through current generation...
	{
		rNum = rand() % population;

		for (int b = 0; b < a; b++) //check every number from 0 to their rank to see if they died
		{
			if (rNum == b) //if the range includes the animat's number, it dies off
			{
				animats[a].setAlive(0); //kill animat
				dead++;
			}
		}
	}
	//*/

	///* //test death function
	if (p) //if user wants to print...
	{
		cout << "________________________________________________________" << endl;
		cout << "Death Function" << endl;
		for (int a = 0; a < population; a++)
		{
			if (animats[a].getAlive()) //if animat is alive
				cout << a << " is alive" << endl;
			else
				cout << a << " is dead" << endl;
		}
	}
	//*/
}

//run simulation to test the animats' skills
void generation::runSim(bool p)
{
	//test 1d skills
	if (p) //if user wants to print...
	{
		cout << "________________________________________________________" << endl;
		cout << "Starting Scores" << endl;
	}
	for (int a = 0; a < population; a++)
	{
		animats[a].setScore(animats[a].test1D()); //set sthe animat's score to their score in testing

		if (p) //if user wants to print...
		{
			cout << a << " Score: " << animats[a].getScore() << endl; //test output
		}
	}
}

//calculats mean, median, mode, and range of generation's scores
void generation::calcStats()
{
	//variables
	int total = 0; //holds total number for mean
	int min = animats[population - 1].getScore(); //save the minimum score
	int max = animats[0].getScore(); //set max score
	vector <int> scoreCounts(max - min + 1, 0); //range to save the score, all set to 0
	int finalMode = 0; //keep track of the mean

	//calculate mean
	for (int a = 0; a < population; a++) //go through all animats
	{
		total += animats[a].getScore(); //add score to total
	}
	mean = (double)total / population; //save mean

	//calculate median
	if (population % 2 == 0) //if population is even...
	{
		total = 0; //reset total
		total += animats[ceil(population / 2)].getScore() + animats[ceil(population / 2) - 1].getScore(); //add totals of middle scores
		median = (double)total / 2; //save median
	}
	else //if population is odd...
	{
		//use ceiling function
		median = animats[ceil(population / 2)].getScore(); //save median
	}

	//calculate range
	range = animats[0].getScore() - animats[population - 1].getScore(); //top score - bottom score is range

	//calculate mode
	for (int a = 0; a < population; a++) //go through population...
	{
		for (int b = min; b <= max; b++) //loop throught to check every possible score
		{
			if (animats[a].getScore() == b) //if the score is in the range
			{
				scoreCounts[(b - min)]++; //add to the count of the score - minimum score
			}
		}
	}

	for (int a = 0; a < scoreCounts.size(); a++) //go through score counts
	{
		if (scoreCounts[a] > finalMode) //if score is greater than the max, set max to the score
		{
			finalMode = scoreCounts[a]; //set new mode
			mode = a + min; //set the mode
		}
	}

	//set min and max
	minScore = animats[population - 1].getScore(); //gets score from the bottom ranked animat
	maxScore = animats[0].getScore(); //gets score from top ranked animat
}

//prints population, death count, mean, median, mode, range, max, min with options to select specific
/*
	population
	death count
	mean
	median
	mode
	range
	max score
	min score
*/
void generation::printStats(bool populationB, bool deathB, bool meanB, bool medianB, bool modeB, bool rangeB, bool maxB, bool minB)
{
	if (populationB || deathB || meanB || medianB || modeB || rangeB || maxB || minB) //test if user wants anything printed...
	{
		cout << "________________________________________________________" << endl;
		cout << "Stats" << endl;
	}

	if (populationB) //if user wants to print population
	{
		cout << "Population: " << population << endl;
	}
	if (deathB) //if user wants to print death count
	{
		cout << "Death Count: " << dead << endl;
	}
	if (meanB) //if user wants to print mean
	{
		cout << "Mean: " << mean << endl;
	}
	if (medianB) //if user wants to print median
	{
		cout << "Median: " << median << endl;
	}
	if (modeB) //if user wants to print mode
	{
		cout << "Mode: " << mode << endl;
	}
	if (rangeB) //if user wants to print range
	{
		cout << "Range: " << range << endl;
	}
	if (maxB) //if user wants to print max
	{
		cout << "Max: " << maxScore << endl;
	}
	if (minB) //if user wants to print min
	{
		cout << "Min: " << minScore << endl;
	}
}