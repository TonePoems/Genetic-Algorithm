/*
4/19/2017
Class for each individual Animat, keeping track of alive state, mutations, traits and others
*/

#include <iostream>
#include <string>
#include <time.h> //random number
#include <sstream> //string stream

using namespace std;

class animat
{
public:
	//constructors
	animat(); //default constructor
	animat(double, double, int, int, int, int); //overloaded constructor with speed, motivation, vision, life span, resilience, stamina

	//methods
	//setters
	//trait setters
	void setSpeed(double);
	void setMotivation(double);
	void setVision(int);
	void setLifeSpan(int);
	void setResilience(int);
	void setStaminaMax(int);

	//other setters
	void setAlive(bool);
	void setLooking(int);
	void setSeekingFood(bool);
	void setX(int);
	void setY(int);
	void setFoodX(int);
	void setFoodY(int);
	void setScore(double);

	//getters
	//trait getters
	double getSpeed();
	double getMotivation();
	int getVision();
	int getLifeSpan();
	int getResilience();
	int getStaminaMax();

	//other getters
	bool getAlive();
	int getLooking();
	bool getSeekingFood();
	int getX();
	int getY();
	int getFoodX();
	int getFoodY();
	double getScore();

	//custom
	void reproduceVariation(); //takes the new animat's traits and adds some amount of variation
	void mutation(); //adds chance for different "genes" to be added
	string gene(); //returns a string holding all of the animat's genes

	//simple distance run test
	double test1D(); //returns the score of the animat's test

	//test pathfinding and 2D movement

	friend bool sortByScore(const animat& lhs, const animat& rhs); //friend function to access the score variable used in generation.h

private:
	//variables
	//traits
	double speed; //to determine the number of moves able to make
	double motivation; //increases the chance to move, 0 to 4
					   /* Vision is the same when passed down, but mutations can modify type of vision
							o
					   0 =  X

						   ooo
					   1 =  X

						   ooo
					   2 = oXo

					       ooo
					   3 = oXo
					       o o

					       ooo
					   4 = oXo
					       ooo

					   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

					        o
					   5 =  X

					        o
					        o
					   6 =  X

					        o
					        o
					        o
					   7 =  X

					        o
					        o
					       ooo
					   8 =  X

					        o
					       ooo
					       ooo
					   9 =  X

					   */
	int vision; //looking around, or the cone of vision changes takes up a turn, so larger vision is still beneficial
	int lifeSpan; //multiplied by speed to determint the number of moves in a turn
	int resilience; //higher resilliance decreases chance of dying to anything
	int staminaMax; //the max number of turns a creature can go in a row

	//others
	bool alive; //tell if animat is living or was eliminated
				/*
				1
				4X2
				3
				*/
	int looking; //which direction to point vision cone
	bool seekingFood; //tells if the animat is pathfinding towards food or just looking
	int x, y; //coords for the animat
	int foodX, foodY; //coords for the food the animat is seeking
	double score; //save the score to rank animats
};

//constructors
animat::animat() //default constructor
{
	//traits
	speed = 1;
	motivation = 2;
	vision = 2;
	lifeSpan = 20;
	resilience = 5;
	staminaMax = 4;

	//others
	alive = 1; //set the alive state to alive
	looking = 1; //looking up
	seekingFood = 0; //not currently seeking food, just looking
	x = 0; //for horizontal tests, temp, no y coord
		   //no y coord for testing
		   //no food for testing
	score = 0;
}
animat::animat(double s, double m, int v, int l, int r, int st) //overloaded constructor with speed, motivation, vision, life span, and resilience
{
	//set the passed traits
	speed = s;
	motivation = m;
	vision = v;
	lifeSpan = l;
	resilience = r;
	staminaMax = st;

	//other variables of the animat
	alive = 1; //set the alive state to alive
	looking = 1; //looking up
	seekingFood = 0; //not currently seeking food, just looking
	x = 0; //for horizontal tests, temp, no y coord
		   //no y coord for testing
		   //no food for testing
	score = 0;
}

//methods
//setters
//trait setters
void animat::setSpeed(double s)
{
	speed = s;
}
void animat::setMotivation(double m)
{
	motivation = m;
}
void animat::setVision(int v)
{
	vision = v;
}
void animat::setLifeSpan(int l)
{
	lifeSpan = l;
}
void animat::setResilience(int r)
{
	resilience = r;
}
void animat::setStaminaMax(int s)
{
	staminaMax = s;
}

//other setters
void animat::setAlive(bool a)
{
	alive = a;
}
void animat::setLooking(int l)
{
	looking = l;
}
void animat::setSeekingFood(bool s)
{
	seekingFood = s;
}
void animat::setX(int X)
{
	x = X;
}
void animat::setY(int Y)
{
	y = Y;
}
void animat::setFoodX(int f)
{
	foodX = f;
}
void animat::setFoodY(int f)
{
	foodY = f;
}
void animat::setScore(double s)
{
	score = s;
}

//getters
//trait getters
double animat::getSpeed()
{
	return speed;
}
double animat::getMotivation()
{
	return motivation;
}
int animat::getVision()
{
	return vision;
}
int animat::getLifeSpan()
{
	return lifeSpan;
}
int animat::getResilience()
{
	return resilience;
}
int animat::getStaminaMax()
{
	return staminaMax;
}

//other getters
bool animat::getAlive()
{
	return alive;
}
int animat::getLooking()
{
	return looking;
}
bool animat::getSeekingFood()
{
	return seekingFood;
}
int animat::getX()
{
	return x;
}
int animat::getY()
{
	return y;
}
int animat::getFoodX()
{
	return foodX;
}
int animat::getFoodY()
{
	return foodY;
}
double animat::getScore()
{
	return score;
}

//custom
//takes the new animat's traits and adds some amount of variation
void animat::reproduceVariation()
{
	//variables
	int rNum; //hold random number

			  //add variation to traits
			  //vary speed
	rNum = rand() % 13;
	if (rNum == 0) //decrease speed
	{
		speed -= .15; //extreme
	}
	else if (rNum == 1 || rNum == 2) //decrease speed
	{
		speed -= .05; //moderate
	}
	else if (rNum == 3 || rNum == 4 || rNum == 5) //decrease speed
	{
		speed -= .03; //slight
	}
	//if rNum == 6, do nothing
	else if (rNum == 7 || rNum == 8 || rNum == 9) //increase speed
	{
		speed += .03; //slight
	}
	else if (rNum == 10 || rNum == 11) //increase speed
	{
		speed += .05; //moderate
	}
	else if (rNum == 12) //increase speed
	{
		speed += .15; //extreme
	}

	if (speed < 0) //make sure no underflow
	{
		speed = 0;
	}

	//vary motivation
	rNum = rand() % 13;
	if (rNum == 0) //decrease motivation
	{
		motivation -= .5; //extreme
	}
	else if (rNum == 1 || rNum == 2) //decrease motivation
	{
		motivation -= .2; //moderate
	}
	else if (rNum == 3 || rNum == 4 || rNum == 5) //decrease motivation
	{
		motivation -= .1; //slight
	}
	//if rNum == 6, do nothing
	else if (rNum == 7 || rNum == 8 || rNum == 9) //increase motivation
	{
		motivation += .1; //slight
	}
	else if (rNum == 10 || rNum == 11) //increase motivation
	{
		motivation += .2; //moderate
	}
	else if (rNum == 12) //increase motivation
	{
		motivation += .5; //extreme
	}

	if (motivation < 0) //make sure no underflow
	{
		motivation = 0;
	}
	if (motivation > 4) //make sure motivation does not go over 4
	{
		motivation = 4;
	}

	//vision does not vary at reproduction, only mutations will change vision

	//vary life span
	rNum = rand() % 13;
	if (rNum == 0) //decrease lifespan
	{
		lifeSpan -= 2; //extreme
	}
	else if (rNum == 1 || rNum == 2 || rNum == 3) //decrease lifespan
	{
		lifeSpan -= 1; //moderate
	}
	//if rNum == 4, 5, 6, 7, or 8, do nothing
	else if (rNum == 9 || rNum == 10 || rNum == 11) //increase lifespan
	{
		lifeSpan += 1; //moderate
	}
	else if (rNum == 12) //increase lifespan
	{
		lifeSpan += 2; //extreme
	}

	if (lifeSpan < 0) //make sure no underflow
	{
		lifeSpan = 0;
	}

	//vary resilience
	rNum = rand() % 13;
	if (rNum == 0) //decrease resilience
	{
		resilience -= 2; //extreme
	}
	else if (rNum == 1 || rNum == 2 || rNum == 3) //decrease resilience
	{
		resilience -= 1; //moderate
	}
	//if rNum == 4, 5, 6, 7, or 8, do nothing
	else if (rNum == 9 || rNum == 10 || rNum == 11) //increase resilience
	{
		resilience += 1; //moderate
	}
	else if (rNum == 12) //increase resilience
	{
		resilience += 2; //extreme
	}

	if (resilience < 0) //make sure no underflow
	{
		resilience = 0;
	}

	//vary staminaMax
	rNum = rand() % 13;
	if (rNum == 0) //decrease staminaMax
	{
		staminaMax -= 2; //extreme
	}
	else if (rNum == 1 || rNum == 2 || rNum == 3) //decrease staminaMax
	{
		staminaMax -= 1; //moderate
	}
	//if rNum == 4, 5, 6, 7, or 8, do nothing
	else if (rNum == 9 || rNum == 10 || rNum == 11) //increase staminaMax
	{
		staminaMax += 1; //moderate
	}
	else if (rNum == 12) //increase staminaMax
	{
		staminaMax += 2; //extreme
	}

	if (staminaMax < 0) //make sure no underflow
	{
		staminaMax = 0;
	}
}

//adds chance for different "genes" to be added or chance to modify genes
void animat::mutation()
{
	//variables
	int rNum; //holds random number

	//test to see if animat will gain any mutations...
	rNum = rand() % 100;
}

//returns a string holding all of the animat's genes
string animat::gene()
{
	//variables
	//string stream
	stringstream ss;
	string temp;
	string gene = "";

	//convert traits to strings and add them to the gene
	//add speed
	ss << speed;
	ss >> temp;
	ss.clear();
	gene += "S" + temp;

	//add motivation
	ss << motivation;
	ss >> temp;
	ss.clear();
	gene += "-M" + temp;

	//add vision
	ss << vision;
	ss >> temp;
	ss.clear();
	gene += "-V" + temp;

	//add life span
	ss << lifeSpan;
	ss >> temp;
	ss.clear();
	gene += "-L" + temp;

	//add resilience
	ss << resilience;
	ss >> temp;
	ss.clear();
	gene += "-R" + temp;

	//add stamina
	ss << staminaMax;
	ss >> temp;
	ss.clear();
	gene += "-SM" + temp;

	return gene;
} //returns a string holding all of the animat's genes

  //simple distance run test
double animat::test1D() //returns the score of the animat's test
{
	//variables
	int turns = lifeSpan * speed + motivation; //lifespan times speed, plus a bonus for more motivation
	int stamina = staminaMax; //holds the number of move available in a row
	bool move = 0; //set bool to not having moved
	x = 0; //reset starting position

		   //cout << "Turns: " << turns << endl; //testing output

		   //random num vars
	int rMotivation;

	//test speed on a 2d grid
	for (int a = 0; a < turns; a++) //loop for the total number of turns
	{
		//chance animat can move forward
		rMotivation = rand() % 4;
		for (int b = 0; b < motivation; b++) //go through the motivation
		{
			if (rMotivation == b && stamina > 0) //higher motivation gives higher chance to move
			{
				x++; //move the animat forward one space
				b = motivation; //set b to end the loop
				stamina--; //decrease stamina
				move = 1; //tell if the animat has moved this turn
						  //cout << a << "   Animat moved, stamina is now " << stamina << endl; //testing output
			}
			else if (rMotivation == b) //if stamina is not greater than the max...
			{
				stamina++;
				b = motivation; //set b to end the loop
				move = 1;
				//cout << a << "   Animat did not have enough stamina to move... stamina is now " << stamina << endl; //testing output
			}
		}

		if (!move) //if the animat has not moved, 
		{
			if (stamina < staminaMax) //and stamina is not at max, increase stamina
			{
				stamina++;
			}
			//cout << a << "   Animat did not have motivation to move..." << endl; //testing output
		}
		move = 0;
	}

	//return score
	score = x;
	return score;
}