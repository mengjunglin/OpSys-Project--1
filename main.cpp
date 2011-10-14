/* Tiffany Milano and Meng Jung Lin 
 * Project 1 - Operating Systems 
 * October 20th 2011 */ 

#include <iostream>
#include <time.h>
#include <ctime>
#include "classSim.h"
using namespace std;

void fcfs(Sim* p);  // First-Come First Served(FCFS)
void sjf(Sim* p);   // Shortest-Job First (SFS)
void psjf(Sim* p);  // Preemptive Shortest-Job First (SJF)
void rr(Sim* p);    // Round-Robin (RR)
void pp(Sim* p);    // Preemptive Priority (PP) 

void dataToCollect(Sim* p, int minTurnAround, int maxTurnAround, int turnTotal, int minInitialWait, 
	int maxInitialWait, int initialTotal, int minWaitTime, int maxWaitTime, int totalWait);

// Simulate elapsed time using a global variable 
int elapsedTime = 0; 


int main(int argc, char * argv[])
{	
	if(argc > 2) { 
		cout << "Error: too many arguments, enter either 1 or 2 arguments."; 
		return 1; 
	}
	
	Sim p[20];	// An array which holds all the processes default of 20 processes
	srand(time(0)); // the seed value for the random number generator 
	/* the for loop creates the dummy processes that will be sent 
	 * into the functions for testing the algorithms. The for loop
	 * will create the process by giving it a random CPU time and 
	 * priority number */ 
	for (int i = 0; i < 20; i++)
	{
		int cpuTime = rand() % 7000 + 500;  // This generates a random number between 500 - 7500
		int priority = rand() % 5; 	    // this generates a random number between 0 and 4 
		Sim process(i, cpuTime, priority ); 
		p[i] = process;  
	}
	
	// Send the processes to the different functions 
	fcfs(p); 
	sjf(p); 
	psjf(p); 
	rr(p); 
	pp(p); 

	
	/* 1. Process creation (display the process ID, required CPU time, and priority, if applicable) - DONE
	 * 2. Context switch (display the two before/after process IDs involved)
	 * 3. Process's first CPU usage (display the process ID and initial wait time)
	 * 4. Process termination (display the process ID, its turnaround time, and its total wait time)*/ 


	system("pause");
	return 0;
}

void dataToCollect(Sim* p, int minTurnAround, int maxTurnAround, int turnTotal, int minInitialWait, 
	int maxInitialWait, int initialTotal, int minWaitTime, int maxWaitTime, int totalWait){
	
	for (int i = 0; i < 20; i++)
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
	cout << "\n\n\n"; 
	cout << "Minimum Turn Around Time: " << minTurnAround << "\n"; 
	cout << "Maximum Turn Around Time: " << maxTurnAround << "\n"; 
	cout << "Average Turn Around Time: " << turnTotal/20 << "\n\n";

	cout << "Minimum Initial Wait Time: " << minInitialWait << "\n"; 
	cout << "Maximum Initial Wait Time: " << maxInitialWait << "\n"; 
	cout << "Average Initial Wait Time: " << initialTotal/20 << "\n\n";

	cout << "Minimum Wait Time: " << minWaitTime << "\n"; 
	cout << "Maximum Wait Time: " << maxWaitTime << "\n"; 
	cout << "Average Wait Time: " << totalWait/20 << "\n\n";
}


/* First-Come First Served(FCFS)
 * The processes will get sent into this function and then 
 * worked on in a first-come-first-served basis so the first 
 * process in is the first process to run and terminate */ 
void fcfs(Sim* p)
{
	int tempWait = 0, eTemp, minTurn = p[0].getTurnTime(), maxTurn = 0, turnT = 0, minInitial = p[0].getITime(), 
		maxInitial = 0, initialT = 0, minWait = p[0].getWaitTime(), maxWait = 0, totalW = 0;  

	// elapsedTime = 0; // Clear out the Global Variable "elapsedTime" 

	/* This for loop sets the inital times for each process and 
	 * prints it's "create" statement */ 
	cout << "Create Processes: \n"; 
	for (int i = 0; i < 20; i++)
	{

		if (i != 0)
		{
			tempWait += p[i-1].getcTime();
			p[i].setWaitTime(tempWait);
			p[i].setiTime(tempWait); 
		}

		eTemp = tempWait + p[i].getcTime();
		p[i].setTerminateTime( eTemp );
		p[i].setTurnTime( eTemp ); 
		cout << "[time " << elapsedTime << "ms] Process " << i+1 << " created (requiring " << p[i].getcTime() << "ms CPU time)\n";
	}

	cout << "\n\n\nFirst-Come-First-Served | Send Processes to CPU and run: \n"; 
	
	for(int j = 0; j < 20; j++) 
	{ 
		if (j != 0)
		{
			cout << "[time " << p[j].getWaitTime() << "ms] Context switch (swapped out process " << j << " for " << j+1 << ")\n";
		}
		cout << "[time " << p[j].getWaitTime() << "ms] Process " << j+1 << " access CPU for the first time (wait time " << p[j].getITime() << "ms)\n";	
		cout << "[time " << p[j].getTerminateTime() << "ms] Process " << j+1 << " terminated (turnaround time " << p[j].getTurnTime() << "ms, wait time " << p[j].getWaitTime() << "ms)\n"; 
	} 

	dataToCollect(p, minTurn, maxTurn, turnT, minInitial, maxInitial, initialT, minWait, maxWait, totalW);
}


/* Shortest-Job First (SFS)
 * This will sort the processes that are sent in based on the 
 * shortest job in the array. */ 
void sjf(Sim* p)
{
}

// Preemptive Shortest-Job First (SJF)
void psjf(Sim* p)
{
}

// Round-Robin (RR)
void rr(Sim* p)
{
}

// Preemptive Priority (PP) 
void pp(Sim* p)
{
}