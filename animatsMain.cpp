/*
4/19/2017
Main file to test and run simulations.

This acts as user interface to change settings of manager class for testing
*/

//include files
#include "manager.h" //holds tester
#include <iomanip>

//function declarations

int main()
{
	//variables
	//random number
	srand(time(NULL));

	manager test; //initalize tester

	//start testing
	test.menu();
	
	test.runTest();

	test.compareStats();

	//end program
	system("pause");
	return 0;
}