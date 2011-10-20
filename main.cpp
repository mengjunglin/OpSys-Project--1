<<<<<<< HEAD
///* Tiffany Milano and Meng Jung Lin 
// * Project 1 - Operating Systems 
// * October 20th 2011 */ 
//
//#include <iostream>
//#include <time.h>
//#include <ctime>
//#include "classSim.h"
//#include <string>
//#include <memory>
//#include <iomanip> 
//#include <fstream>
//
//using namespace std;
//
//Sim* createProcesses(const int size); 
//
//void fcfs(Sim* p, int size);  // First-Come First Served(FCFS)
//void sjf(Sim* p, int size);   // Shortest-Job First (SFS)
//void psjf(Sim* p, int size);  // Preemptive Shortest-Job First (SJF)
//void rr(Sim* p, int size);    // Round-Robin (RR)
//void pp(Sim* p, int size);    // Preemptive Priority (PP) 
//
//void dataToCollect(Sim* p, int size, int minTurnAround, int maxTurnAround, 
//					int turnTotal, int minInitialWait, int maxInitialWait, 
//					int initialTotal, int minWaitTime, int maxWaitTime, 
//					int totalWait);
//Sim* sortProcesses(Sim* p, int size); 
//Sim* sortPriority(Sim* p, const int size);
//void printProcessCreate(Sim* p, const int size);
//void printContextSwitch(int waitTime, int location1, int location2);
//void printFirst(int eTime, int pId, int waitTime);
//void printTerminate(int eTime, int pId, int tTime, int waitTime); 
//bool compareSim(Sim a, Sim b);
//int totalElapsedTime(int eTime);
//
//// The elapsed time will be simulated using this global variable  
//int elapsedTime = 0;  
//
//
////int main(int argc, char * argv[])
////{	
////	streambuf *psbuf, *backup;
////	ofstream filestr;
////	filestr.open("output.txt");
////	backup = cout.rdbuf(); //backup cout streambuf
////	psbuf = filestr.rdbuf(); //get file streambuf
////	cout.rdbuf(psbuf); //assign streambuf to cout
////
////	/* To call a specific process management simulation functions use 	*
////	 * fscs, sjf, psjf, rr, or pp as the second argument when calling 	*
////	 * the program for example: bash$ ./a.exe fscs 						*/ 
////
////	const int n = 20; 
////	if(argc > 2) { 
////		cout << "ERROR: too many arguments, enter either 1 or 2 arguments."; 
////		return 1; 
////	}
////
////	Sim* pArr; 
////	pArr = createProcesses(n); 
////
////
////	/* if there is two arguments then check to compare the arguments with the
////	 * specific functions if it does not compare return 1 with an error */ 
////	if(argc == 2) {  
////		if((string)argv[1] == "fcfs") { fcfs(pArr, n); } 
////		else if((string)argv[1] == "sjf"){ sjf(pArr, n); }
////		else if((string)argv[1] == "psjf"){ psjf(pArr, n); } 
////		else if((string)argv[1] == "rr"){ rr(pArr, n); } 
////		else if((string)argv[1] == "pp"){ pp(pArr, n); }
////		else{ 
////			cout << "ERROR: This argument does not match any of the test functions." <<
////					"\nPlease use fcfs, sjf, psjf, rr, or pp as your second argument.\n"; 
////			system("pause"); 
////			return 0; 
////		}
////	}
////	else {
////		// Send the processes to the different functions 
////		fcfs(pArr, n); 
////		sjf(pArr, n); 
////		psjf(pArr, n); 
////		rr(pArr, n); 
////		pp(pArr, n); 
////	}
////	/* 1. Process creation (display the process ID, required CPU time, and priority, if applicable) - DONE for FCFS, DONE for SJF
////	 * 2. Context switch (display the two before/after process IDs involved) - DONE for FCFS, DONE for SJF
////	 * 3. Process's first CPU usage (display the process ID and initial wait time) - DONE for FCFS, DONE for SJF
////	 * 4. Process termination (display the process ID, its turnaround time, and its total wait time) - DONE for FCFS, DONE for SJF */ 
////
////	filestr.close();
////
////	system("pause");
////	return 0;
////}
//
//Sim* createProcesses(const int size){
//	// An array which holds all the processes default of 20 processes
//	Sim* pA = new Sim[size];	
//	// the seed value for the random number generator
//	srand(time(0));				 
//
//	/* the for loop creates the dummy processes that will be sent into the 
//	 * functions for testing the algorithms. The for loop will create the 
//	 * process by giving it a random CPU time and priority number */ 
//	for (int i = 0; i < size; i++){
//		int cpuTime = rand() % 7000 + 500;  // This generates a random number between 500 - 7500
//		int priority = rand() % 5; 	        // this generates a random number between 0 and 4 
//		Sim process(i+1, cpuTime, priority ); 
//		pA[i] = process;  
//	}
//	cout << "Create Processes: \n"; 
//	int tempWait = 0, eTemp;
//	for (int i = 0; i < size; i++)
//	{
//		if (i != 0){
//			tempWait += pA[i-1].getcTime();
//			pA[i].setWaitTime(tempWait);
//			pA[i].setiTime(tempWait); 
//		}
//		/* This for loop sets the inital times for each process and prints it's "create" statement */ 
//		eTemp = tempWait + pA[i].getcTime();
//		pA[i].setTerminateTime( eTemp );
//		pA[i].setTurnTime( eTemp );
//		pA[i].setTimeRemain( pA[i].getcTime() );
//	}
//	
//	printProcessCreate(pA, size);
//	return pA; 
//}
//
///* First-Come First Served(FCFS) The processes will get sent into this function and then worked on in 
// * a first-come-first-served basis so the first process in is the first process to run and terminate */ 
//void fcfs(Sim* p, int size)
//{
//	int minTurn = p[0].getTurnTime(), maxTurn = 0, turnT = 0, minInitial = p[0].getITime(), 
//		maxInitial = 0, initialT = 0, minWait = p[0].getWaitTime(), maxWait = 0, totalW = 0;  
//
//	elapsedTime = 0; // Clear out the Global Variable "elapsedTime" 
//
//	cout << "\n\n\nFirst-Come-First-Served | Send Processes to CPU and run: \n"; 
//
//	for(int j = 0; j < size; j++)  
//	{ 
//		if (j != 0)
//		{			
//			elapsedTime = totalElapsedTime(elapsedTime); 
//			printContextSwitch(elapsedTime, j, j+1);
//			elapsedTime = totalElapsedTime(elapsedTime); 
//		}
//		p[j].setiTime(elapsedTime);
//		p[j].setWaitTime(elapsedTime);
//		printFirst(elapsedTime, j+1, p[j].getITime());
//		elapsedTime += p[j].getcTime();
//		p[j].setTurnTime(elapsedTime);
//		cout << "[time " << elapsedTime << "ms] Process " << j+1 
//			<< " terminated (turnaround time " << p[j].getTurnTime() 
//			<< "ms, wait time " << p[j].getWaitTime() << "ms)\n"; 		
//	} 
//	dataToCollect(p, size, minTurn, maxTurn, turnT, minInitial, maxInitial, initialT, minWait, maxWait, totalW);
//}
//
//#ifndef sjf
///* Shortest-Job First (SFS)
// * This will sort the processes that are sent in based on the 
// * shortest job in the array. */ 
//void sjf(Sim* p, int size)
//{
//	int tempWait = 0, minTurn = p[0].getTurnTime(), maxTurn = 0, 
//		turnT = 0, minInitial = p[0].getITime(), maxInitial = 0, 
//		initialT = 0, minWait = p[0].getWaitTime(), maxWait = 0, 
//		totalW = 0;  
//
//	elapsedTime = 0; 
//
//	/* Sort the processes based on the CPU time once the processes 
//	 * are sorted then run the simulation similar to FCFS */ 
//	//Sim*  pSorted = sortProcesses(p, size);
//	Sim* pSorted = new Sim[size];
//	for(int x = 0; x < size; x ++) 
//	{ 
//		pSorted[x].setCTime(p[x].getcTime());
//		pSorted[x].setiTime(p[x].getITime());
//		pSorted[x].setTerminateTime(p[x].getTerminateTime());
//		pSorted[x].setTimeRemain(p[x].getTimeRemain());
//		pSorted[x].setTurnTime(p[x].getTurnTime());
//		pSorted[x].setWaitTime(p[x].getWaitTime());
//		pSorted[x].setP(p[x].getP()); 
//		pSorted[x].setPidId(p[x].getpId());
//	}
//
//	sortProcesses(pSorted,size);
//	pSorted[0].setWaitTime(tempWait);
//	for(int i = 1; i < size; i++)
//	{
//		tempWait += pSorted[i-1].getcTime();
//		pSorted[i].setWaitTime(tempWait);
//		pSorted[i].setiTime(tempWait);
//	}
//
//	cout << "\n\n\nShortest Job First without Preemption | Send Processes to CPU and run: \n"; 
//
//	for(int j = 0; j < size; j++) 
//	{ 
//		if (j != 0)
//		{
//			//printContextSwitch(pSorted[j].getWaitTime(), j);
//			elapsedTime = totalElapsedTime(elapsedTime); 
//			printContextSwitch(elapsedTime, pSorted[j-1].getpId(), pSorted[j].getpId());
//			
//			elapsedTime = totalElapsedTime(elapsedTime); 
//		} 
//		pSorted[j].setWaitTime(elapsedTime);
//		printFirst(elapsedTime, pSorted[j].getpId(), pSorted[j].getWaitTime());	
//		elapsedTime+=pSorted[j].getcTime(); 
//		pSorted[j].setTurnTime(elapsedTime);
//		printTerminate(elapsedTime, pSorted[j].getpId(), pSorted[j].getTurnTime(), pSorted[j].getWaitTime()); 
//	} 
//
//	dataToCollect(pSorted, size, minTurn, maxTurn, turnT, minInitial, maxInitial, initialT, minWait, maxWait, totalW);
//
//
//}
//
//Sim* sortProcesses(Sim* p, const int size)
//{ 
//	for(int i = 0; i < size; i ++) 
//	{ 
//		for(int j = 0; j < size; j++)
//		{
//			if (p[i].getcTime() < p[j].getcTime())
//			{
//				swap(p[i],p[j]);
//			}
//		}
//	} 
//	return p; 
//}
//#endif
//
//// Preemptive Shortest-Job First (SJF)
//void psjf(Sim* p, int size)
//{
//	int minTurn = p[0].getTurnTime(), maxTurn = 0, turnT = 0, minInitial = p[0].getITime(), 
//		maxInitial = 0, initialT = 0, minWait = p[0].getWaitTime(), maxWait = 0, totalW = 0;  
//
//	cout << "\n\n\nShortest Job First with Preemption | Send Processes to CPU and run: \n";
//
//	elapsedTime = 0;
//
//	//while there are still process remain
//	for (int i = 0; i < size; i++)
//	{
//		p[i].setTimeRemain(p[i].getTimeRemain() - p[i+i].getATime());
//	}
//	
//}
//
//// Round-Robin (RR)
//void rr(Sim* p, int size)
//{
//	int minTurn = p[0].getTurnTime(), maxTurn = 0, turnT = 0, minInitial = p[0].getITime(), 
//		maxInitial = 0, initialT = 0, minWait = p[0].getWaitTime(), maxWait = 0, totalW = 0;  
//	int timeSlice = 100; //initialize time slice with 100 ms
//
//	cout << "\n\n\nRound-Robin with time slice 100ms | Send Processes to CPU and run: \n";
//
//	elapsedTime = 0; 
//	int counter = 0; 
//	int store;  // stores the pidId of the last variable
//	bool firstTime = true; 
//	while(counter != size) 
//	{
//		counter = 0; // re-set counter since counter != size in the last iteration therefore not all the processes are finished
//		for (int j = 0; j < size; j++)
//		{
//			
//			if (p[j].getTimeRemain() != 0)
//			{
//				if(firstTime != true && store != p[j].getpId())
//				{ 
//					elapsedTime = totalElapsedTime(elapsedTime);
//					printContextSwitch(elapsedTime, store, p[j].getpId()); 
//					elapsedTime = totalElapsedTime(elapsedTime);
//					p[j].setWaitTime(elapsedTime-p[j].getcTime());
//				}
//				if (p[j].getcTime() == p[j].getTimeRemain())
//			{
//				p[j].setWaitTime(elapsedTime);
//				printFirst(elapsedTime, p[j].getpId(), p[j].getWaitTime());	
//			}
//				elapsedTime = elapsedTime + 100;
//				p[j].setTimeRemain( p[j].getTimeRemain() - timeSlice );
//				if (p[j].getTimeRemain() <= 0)				// if remain time == 0, print "terminate"
//				{
//					int check = abs(p[j].getTimeRemain());  // Checks to see if the program terminated before the timeslice
//					elapsedTime = elapsedTime - check; 		//subtract off the time that this slice did not use 
//					p[j].setTimeRemain(0); 					//sets the time to 0
//					p[j].setTurnTime(elapsedTime);
//					printTerminate(elapsedTime, p[j].getpId(), p[j].getTurnTime(), p[j].getWaitTime()); 
//					counter++; 								// This processes is now added to the "ended" counter 
//				}
//				store = p[j].getpId(); 
//			}
//			else{ counter++; }
//			firstTime = false; 
//		}
//	}
//	dataToCollect(p, size, minTurn, maxTurn, turnT, minInitial, maxInitial, initialT, minWait, maxWait, totalW);
//}
//
//// Preemptive Priority (PP) 
//void pp(Sim* p, int size)
//{
//	int tempWait = 0, minTurn = p[0].getTurnTime(), maxTurn = 0, turnT = 0, minInitial = p[0].getITime(), 
//		maxInitial = 0, initialT = 0, minWait = p[0].getWaitTime(), maxWait = 0, totalW = 0;  
//
//	elapsedTime = 0;
//
//	for (int i = 0; i < size; i++)
//	{
//		cout << "Process " << p[i].getpId() << " has a priority of " << p[i].getP() << endl;
//	}
//
//	cout << "\n\n\nPreemptive-Priority | Send Processes to CPU and run: \n";
//
//	Sim* pSorted = new Sim[size];
//	for(int x = 0; x < size; x ++) 
//	{ 
//		pSorted[x].setCTime(p[x].getcTime());
//		pSorted[x].setiTime(p[x].getITime());
//		pSorted[x].setTerminateTime(p[x].getTerminateTime());
//		pSorted[x].setTimeRemain(p[x].getTimeRemain());
//		pSorted[x].setTurnTime(p[x].getTurnTime());
//		pSorted[x].setWaitTime(p[x].getWaitTime());
//		pSorted[x].setP(p[x].getP()); 
//		pSorted[x].setPidId(p[x].getpId());
//	}
//
//	sortPriority(pSorted,size);
//	pSorted[0].setWaitTime(tempWait);
//	for(int i = 1; i < size; i++)
//	{
//		tempWait += pSorted[i-1].getcTime();
//		pSorted[i].setWaitTime(tempWait);
//		pSorted[i].setiTime(tempWait);
//	}
//
//	for(int j = 0; j < size; j++) 
//	{ 
//		if (j != 0)
//		{
//			//printContextSwitch(pSorted[j].getWaitTime(), j);
//			elapsedTime = totalElapsedTime(elapsedTime); 
//			printContextSwitch(elapsedTime, pSorted[j-1].getpId(), pSorted[j].getpId());
//			
//			elapsedTime = totalElapsedTime(elapsedTime); 
//		} 
//		pSorted[j].setWaitTime(elapsedTime);
//		printFirst(elapsedTime, pSorted[j].getpId(), pSorted[j].getWaitTime());	
//		elapsedTime+=pSorted[j].getcTime(); 
//		pSorted[j].setTurnTime(elapsedTime);
//		printTerminate(elapsedTime, pSorted[j].getpId(), pSorted[j].getTurnTime(), pSorted[j].getWaitTime()); 
//	} 
//
//	dataToCollect(pSorted, size, minTurn, maxTurn, turnT, minInitial, maxInitial, initialT, minWait, maxWait, totalW);
//}
//
//Sim* sortPriority(Sim* p, const int size)
//{ 
//	for(int i = 0; i < size; i ++) 
//	{ 
//		for(int j = 0; j < size; j++)
//		{
//			if (p[i].getP() < p[j].getP())
//			{
//				swap(p[i],p[j]);
//			}
//		}
//	} 
//	return p; 
//}
//
//void dataToCollect(Sim* p, int size, int minTurnAround, int maxTurnAround, int turnTotal, int minInitialWait, 
//	int maxInitialWait, int initialTotal, int minWaitTime, int maxWaitTime, int totalWait){
//
//	for (int i = 0; i < size; i++)
//	{
//		//TurnAroundTime
//		if(p[i].getTurnTime() < minTurnAround){
//			minTurnAround = p[i].getTurnTime();
//		}
//		if(p[i].getTurnTime() > maxTurnAround){
//			maxTurnAround = p[i].getTurnTime();
//		}
//		turnTotal += p[i].getTurnTime(); 
//
//		//InitialWaitTime
//		if(p[i].getITime() < minInitialWait){
//			minInitialWait = p[i].getITime();
//		}
//		if(p[i].getITime() > maxInitialWait){
//			maxInitialWait = p[i].getITime();
//		}
//		initialTotal += p[i].getITime(); 
//
//		//TotalWaitTime
//		if(p[i].getWaitTime() < minWaitTime){
//			minWaitTime = p[i].getWaitTime();
//		}
//		if(p[i].getWaitTime() > maxWaitTime){
//			maxWaitTime = p[i].getWaitTime();
//		}
//		totalWait += p[i].getWaitTime();
//	}
//
//	/* int minTurnAround, int maxTurnAround, int turnTotal, int minInitialWait, 
//	int maxInitialWait, int initialTotal, int minWaitTime, int maxWaitTime, int totalWait */ 
//	double tempTime = 0.0; 
//	cout << fixed;
//	cout << setprecision (3) <<endl;
//
//	cout << "\n\n\n"; 
//	cout << "Minimum Turn Around Time: " << minTurnAround << "\n"; 
//	cout << "Maximum Turn Around Time: " << maxTurnAround << "\n"; 
//	tempTime = (double)turnTotal/(double)size; 
//	cout << "Average Turn Around Time: " << tempTime << "\n\n";
//
//	cout << "Minimum Initial Wait Time: " << minInitialWait << "\n"; 
//	cout << "Maximum Initial Wait Time: " << maxInitialWait << "\n"; 
//	tempTime = (double)initialTotal/(double)size; 
//	cout << "Average Initial Wait Time: " << tempTime << "\n\n";
//
//	cout << "Minimum Wait Time: " << minWaitTime << "\n"; 
//	cout << "Maximum Wait Time: " << maxWaitTime << "\n"; 
//	tempTime = (double)totalWait/(double)size; 
//	cout << "Average Wait Time: " << tempTime << "\n\n";
//
//	 
//}
//
//
//
//#ifndef printFunctions 
///* printProcessCreate will print the processes that were 
// * created in the Sim array */ 
//void printProcessCreate(Sim* p, int size)
//{ 
//	for(int i = 0; i < size; i ++)
//	{
//		cout << "[time " << elapsedTime << "ms] Process " << p[i].getpId() 
//			<< " created (requiring " << p[i].getcTime() << "ms CPU time)\n";
//	}
//}
//
//void printContextSwitch(int waitTime, int location1, int location2)
//{
//	cout << "[time " << waitTime << "ms] Context switch (swapped out process " 
//		<< location1 << " for " << location2 << ")\n";
//}
//
//void printFirst(int eTime, int pId, int waitTime)
//{
//	cout << "[time " << eTime << "ms] Process " << pId 
//		<< " access CPU for the first time (wait time " << waitTime << "ms)\n";	
//}
//
//void printTerminate(int eTime, int pId, int tTime, int waitTime)
//{
//	cout << "[time " << eTime << "ms] Process " << pId 
//					<< " terminated (turnaround time " << tTime 
//					<< "ms, wait time " << waitTime << "ms)\n";
//}
//
//int totalElapsedTime(int eTime){ 
//	eTime+=4; 
//	return eTime; 
//}
//
//#endif
=======
* Tiffany Milano and Meng Jung Lin 
 * Project 1 - Operating Systems 
 * October 20th 2011 */ 

#include <iostream>
#include <time.h>
#include <ctime>
#include "classSim.h"
#include <string>
#include <memory>
#include <iomanip> 
#include <fstream>

using namespace std;

Sim* createProcesses(const int size); 

void fcfs(Sim* p, int size);  // First-Come First Served(FCFS)
void sjf(Sim* p, int size);   // Shortest-Job First (SFS)
void psjf(Sim* p, int size);  // Preemptive Shortest-Job First (SJF)
void rr(Sim* p, int size);    // Round-Robin (RR)
void pp(Sim* p, int size);    // Preemptive Priority (PP) 

void dataToCollect(Sim* p, int size, int minTurnAround, int maxTurnAround, 
					int turnTotal, int minInitialWait, int maxInitialWait, 
					int initialTotal, int minWaitTime, int maxWaitTime, 
					int totalWait);
Sim* sortProcesses(Sim* p, int size); 
void printProcessCreate(Sim* p, const int size);
void printContextSwitch(int waitTime, int location1, int location2);
void printCPUFirstTime(Sim* p, int size);
void printFirst(int eTime, int pId, int waitTime);
void printTerminate(int eTime, int pId, int tTime, int waitTime); 
bool compareSim(Sim a, Sim b);
int totalElapsedTime(int eTime);

// The elapsed time will be simulated using this global variable  
int elapsedTime = 0;  


int main(int argc, char * argv[])
{	
	streambuf *psbuf, *backup;
	ofstream filestr;
	filestr.open("output.txt");
	backup = cout.rdbuf(); //backup cout streambuf
	psbuf = filestr.rdbuf(); //get file streambuf
	cout.rdbuf(psbuf); //assign streambuf to cout

	/* To call a specific process management simulation functions use 	*
	 * fscs, sjf, psjf, rr, or pp as the second argument when calling 	*
	 * the program for example: bash$ ./a.exe fscs 						*/ 

	const int n = 20; 
	if(argc > 2) { 
		cout << "ERROR: too many arguments, enter either 1 or 2 arguments."; 
		return 1; 
	}

	Sim* pArr; 
	pArr = createProcesses(n); 


	/* if there is two arguments then check to compare the arguments with the
	 * specific functions if it does not compare return 1 with an error */ 
	if(argc == 2) {  
		if((string)argv[1] == "fcfs") { fcfs(pArr, n); } 
		else if((string)argv[1] == "sjf"){ sjf(pArr, n); }
		else if((string)argv[1] == "psjf"){ psjf(pArr, n); } 
		else if((string)argv[1] == "rr"){ rr(pArr, n); } 
		else if((string)argv[1] == "pp"){ pp(pArr, n); }
		else{ 
			cout << "ERROR: This argument does not match any of the test functions." <<
					"\nPlease use fcfs, sjf, psjf, rr, or pp as your second argument.\n"; 
			system("pause"); 
			return 0; 
		}
	}
	else {
		// Send the processes to the different functions 
		fcfs(pArr, n); 
		sjf(pArr, n); 
		psjf(pArr, n); 
		rr(pArr, n); 
		pp(pArr, n); 
	}
	/* 1. Process creation (display the process ID, required CPU time, and priority, if applicable) - DONE for FCFS, DONE for SJF
	 * 2. Context switch (display the two before/after process IDs involved) - DONE for FCFS, DONE for SJF
	 * 3. Process's first CPU usage (display the process ID and initial wait time) - DONE for FCFS, DONE for SJF
	 * 4. Process termination (display the process ID, its turnaround time, and its total wait time) - DONE for FCFS, DONE for SJF */ 

	filestr.close();

	system("pause");
	return 0;
}

Sim* createProcesses(const int size){
	// An array which holds all the processes default of 20 processes
	Sim* pA = new Sim[size];	
	// the seed value for the random number generator
	srand(time(0));				 

	/* the for loop creates the dummy processes that will be sent into the 
	 * functions for testing the algorithms. The for loop will create the 
	 * process by giving it a random CPU time and priority number */ 
	for (int i = 0; i < size; i++){
		int cpuTime = rand() % 7000 + 500;  // This generates a random number between 500 - 7500
		int priority = rand() % 5; 	        // this generates a random number between 0 and 4 
		Sim process(i+1, cpuTime, priority ); 
		pA[i] = process;  
	}
	cout << "Create Processes: \n"; 
	int tempWait = 0, eTemp;
	for (int i = 0; i < size; i++)
	{
		if (i != 0){
			tempWait += pA[i-1].getcTime();
			pA[i].setWaitTime(tempWait);
			pA[i].setiTime(tempWait); 
		}
		/* This for loop sets the inital times for each process and prints it's "create" statement */ 
		eTemp = tempWait + pA[i].getcTime();
		pA[i].setTerminateTime( eTemp );
		pA[i].setTurnTime( eTemp );
		pA[i].setTimeRemain( pA[i].getcTime() );
	}
	
	printProcessCreate(pA, size);
	return pA; 
}

* First-Come First Served(FCFS) The processes will get sent into this function and then worked on in 
 * a first-come-first-served basis so the first process in is the first process to run and terminate */ 
void fcfs(Sim* p, int size)
{
	int minTurn = p[0].getTurnTime(), maxTurn = 0, turnT = 0, minInitial = p[0].getITime(), 
		maxInitial = 0, initialT = 0, minWait = p[0].getWaitTime(), maxWait = 0, totalW = 0;  

	elapsedTime = 0; // Clear out the Global Variable "elapsedTime" 

	cout << "\n\n\nFirst-Come-First-Served | Send Processes to CPU and run: \n"; 

	for(int j = 0; j < size; j++)  
	{ 
		if (j != 0)
		{			
			elapsedTime = totalElapsedTime(elapsedTime); 
			printContextSwitch(elapsedTime, j, j+1);
			elapsedTime = totalElapsedTime(elapsedTime); 
		}
		p[j].setiTime(elapsedTime);
		p[j].setWaitTime(elapsedTime);
		printFirst(elapsedTime, j+1, p[j].getITime());
		elapsedTime += p[j].getcTime();
		p[j].setTurnTime(elapsedTime);
		cout << "[time " << elapsedTime << "ms] Process " << j+1 
			<< " terminated (turnaround time " << p[j].getTurnTime() 
			<< "ms, wait time " << p[j].getWaitTime() << "ms)\n"; 		
	} 
	dataToCollect(p, size, minTurn, maxTurn, turnT, minInitial, maxInitial, initialT, minWait, maxWait, totalW);
}

#ifndef sjf
* Shortest-Job First (SFS)
 * This will sort the processes that are sent in based on the 
 * shortest job in the array. */ 
void sjf(Sim* p, int size)
{
	int tempWait = 0, minTurn = p[0].getTurnTime(), maxTurn = 0, 
		turnT = 0, minInitial = p[0].getITime(), maxInitial = 0, 
		initialT = 0, minWait = p[0].getWaitTime(), maxWait = 0, 
		totalW = 0;  

	elapsedTime = 0; 

	/* Sort the processes based on the CPU time once the processes 
	 * are sorted then run the simulation similar to FCFS */ 
	//Sim*  pSorted = sortProcesses(p, size);
	Sim* pSorted = new Sim[size];
	for(int x = 0; x < size; x ++) 
	{ 
		pSorted[x].setCTime(p[x].getcTime());
		pSorted[x].setiTime(p[x].getITime());
		pSorted[x].setTerminateTime(p[x].getTerminateTime());
		pSorted[x].setTimeRemain(p[x].getTimeRemain());
		pSorted[x].setTurnTime(p[x].getTurnTime());
		pSorted[x].setWaitTime(p[x].getWaitTime());
		pSorted[x].setP(p[x].getP()); 
		pSorted[x].setPidId(p[x].getpId());
	}

	sortProcesses(pSorted,size);
	pSorted[0].setWaitTime(tempWait);
	for(int i = 1; i < size; i++)
	{
		tempWait += pSorted[i-1].getcTime();
		pSorted[i].setWaitTime(tempWait);
		pSorted[i].setiTime(tempWait);
	}

	cout << "\n\n\nShortest Job First without Preemption | Send Processes to CPU and run: \n"; 

	for(int j = 0; j < size; j++) 
	{ 
		if (j != 0)
		{
			//printContextSwitch(pSorted[j].getWaitTime(), j);
			elapsedTime = totalElapsedTime(pSorted[j].getWaitTime()); 
			printContextSwitch(elapsedTime, pSorted[j-1].getpId(), pSorted[j].getpId());
			
			elapsedTime = totalElapsedTime(elapsedTime); 
		} 
		pSorted[j].setWaitTime(elapsedTime);
		printFirst(elapsedTime, pSorted[j].getpId(), pSorted[j].getWaitTime());	
		elapsedTime+=pSorted[j].getcTime(); 
		pSorted[j].setTurnTime(elapsedTime);
		printTerminate(elapsedTime, pSorted[j].getpId(), pSorted[j].getTurnTime(), pSorted[j].getWaitTime()); 
	} 

	dataToCollect(pSorted, size, minTurn, maxTurn, turnT, minInitial, maxInitial, initialT, minWait, maxWait, totalW);


}

Sim* sortProcesses(Sim* p, const int size)
{ 
	for(int i = 0; i < size; i ++) 
	{ 
		for(int j = 0; j < size; j++)
		{
			if (p[i].getcTime() < p[j].getcTime())
			{
				swap(p[i],p[j]);
			}
		}
	} 
	return p; 
}
#endif

// Preemptive Shortest-Job First (SJF)
void psjf(Sim* p, int size)
{



	//while there are still process remain
	for (int i = 0; i < size; i++)
	{

	}
	
}

// Round-Robin (RR)
void rr(Sim* p, int size)
{
	int minTurn = p[0].getTurnTime(), maxTurn = 0, turnT = 0, minInitial = p[0].getITime(), 
		maxInitial = 0, initialT = 0, minWait = p[0].getWaitTime(), maxWait = 0, totalW = 0;  
	int timeSlice = 100; //initialize time slice with 100 ms

	cout << "\n\n\nRound-Robin with time slice 100ms | Send Processes to CPU and run: \n";

	elapsedTime = 0; 
	int counter = 0; 
	int store;  // stores the pidId of the last variable
	bool firstTime = true; 
	while(counter != size) 
	{
		counter = 0; // re-set counter since counter != size in the last iteration therefore not all the processes are finished
		for (int j = 0; j < size; j++)
		{
			
			if (p[j].getTimeRemain() != 0)
			{
				if(firstTime != true && store != p[j].getpId())
				{ 
					elapsedTime = totalElapsedTime(elapsedTime);
					printContextSwitch(elapsedTime, store, p[j].getpId()); 
					elapsedTime = totalElapsedTime(elapsedTime);
					p[j].setWaitTime(elapsedTime-p[j].getcTime());
				}
				if (p[j].getcTime() == p[j].getTimeRemain())
				{
					p[j].setWaitTime(elapsedTime);
					printFirst(elapsedTime, p[j].getpId(), p[j].getWaitTime());	
				}
				elapsedTime = elapsedTime + 100;
				p[j].setTimeRemain( p[j].getTimeRemain() - timeSlice );
				if (p[j].getTimeRemain() <= 0)				// if remain time == 0, print "terminate"
				{
					int check = abs(p[j].getTimeRemain());  // Checks to see if the program terminated before the timeslice
					elapsedTime = elapsedTime - check; 		//subtract off the time that this slice did not use 
					p[j].setTimeRemain(0); 					//sets the time to 0
					p[j].setTurnTime(elapsedTime);
					printTerminate(elapsedTime, p[j].getpId(), p[j].getTurnTime(), p[j].getWaitTime()); 
					counter++; 								// This processes is now added to the "ended" counter 
				}
				store = p[j].getpId(); 
			}
			else{ counter++; }
			firstTime = false; 
		}
	}
	dataToCollect(p, size, minTurn, maxTurn, turnT, minInitial, maxInitial, initialT, minWait, maxWait, totalW);
}

// Preemptive Priority (PP) 
void pp(Sim* p, int size)
{
} 

void dataToCollect(Sim* p, int size, int minTurnAround, int maxTurnAround, int turnTotal, int minInitialWait, 
	int maxInitialWait, int initialTotal, int minWaitTime, int maxWaitTime, int totalWait){

	for (int i = 0; i < size; i++)
	{
		//TurnAroundTime
		if(p[i].getTurnTime() < minTurnAround){
			minTurnAround = p[i].getTurnTime();
		}
		if(p[i].getTurnTime() > maxTurnAround){
			maxTurnAround = p[i].getTurnTime();
		}
		turnTotal += p[i].getTurnTime(); 

		//InitialWaitTime
		if(p[i].getITime() < minInitialWait){
			minInitialWait = p[i].getITime();
		}
		if(p[i].getITime() > maxInitialWait){
			maxInitialWait = p[i].getITime();
		}
		initialTotal += p[i].getITime(); 

		//TotalWaitTime
		if(p[i].getWaitTime() < minWaitTime){
			minWaitTime = p[i].getWaitTime();
		}
		if(p[i].getWaitTime() > maxWaitTime){
			maxWaitTime = p[i].getWaitTime();
		}
		totalWait += p[i].getWaitTime();
	}

	/* int minTurnAround, int maxTurnAround, int turnTotal, int minInitialWait, 
	int maxInitialWait, int initialTotal, int minWaitTime, int maxWaitTime, int totalWait */ 
	double tempTime = 0.0; 
	cout << fixed;
	cout << setprecision (3) <<endl;

	cout << "\n\n\n"; 
	cout << "Minimum Turn Around Time: " << minTurnAround << "\n"; 
	cout << "Maximum Turn Around Time: " << maxTurnAround << "\n"; 
	tempTime = (double)turnTotal/(double)size; 
	cout << "Average Turn Around Time: " << tempTime << "\n\n";

	cout << "Minimum Initial Wait Time: " << minInitialWait << "\n"; 
	cout << "Maximum Initial Wait Time: " << maxInitialWait << "\n"; 
	tempTime = (double)initialTotal/(double)size; 
	cout << "Average Initial Wait Time: " << tempTime << "\n\n";

	cout << "Minimum Wait Time: " << minWaitTime << "\n"; 
	cout << "Maximum Wait Time: " << maxWaitTime << "\n"; 
	tempTime = (double)totalWait/(double)size; 
	cout << "Average Wait Time: " << tempTime << "\n\n";

	 
}



#ifndef printFunctions 
* printProcessCreate will print the processes that were 
 * created in the Sim array */ 
void printProcessCreate(Sim* p, int size)
{ 
	for(int i = 0; i < size; i ++)
	{
		cout << "[time " << elapsedTime << "ms] Process " << p[i].getpId() 
			<< " created (requiring " << p[i].getcTime() << "ms CPU time)\n";
	}
}

void printContextSwitch(int waitTime, int location1, int location2)
{
	cout << "[time " << waitTime << "ms] Context switch (swapped out process " 
		<< location1 << " for " << location2 << ")\n";
}

void printFirst(int eTime, int pId, int waitTime)
{
	cout << "[time " << eTime << "ms] Process " << pId 
		<< " access CPU for the first time (wait time " << waitTime << "ms)\n";	
}

void printTerminate(int eTime, int pId, int tTime, int waitTime)
{
	cout << "[time " << eTime << "ms] Process " << pId 
					<< " terminated (turnaround time " << tTime 
					<< "ms, wait time " << waitTime << "ms)\n";
}

int totalElapsedTime(int eTime){ 
	eTime+=4; 
	return eTime; 
}

void printCPUFirstTime(Sim* p, int size){

}



#endif
>>>>>>> c01aaefbf1938a94f29e14024ab75599766dd2db
