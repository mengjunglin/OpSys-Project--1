// Tiffany Milano and Meng Jung Lin 
// Project 1 - Operating Systems 
// October 20th 2011

#include <iostream>
#include "classSim.h"
using namespace std;

int main()
{
	//okay, now I know how to upload
	//trying to download now...
	cout << "Hello World" << endl;

	Sim simulation;
	simulation.setiTime(20);
	int k = simulation.getITime();
	cout << k << endl;

	system("pause");
	return 0;
}