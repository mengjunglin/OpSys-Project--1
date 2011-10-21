/* Tiffany Milano and Meng Jung Lin 
 * Project 1 - Operating Systems 
 * October 20th 2011 */ 

#include <iostream>
#include <time.h>
#include <ctime>
#include "classSim2.h"
#include <string>
#include <memory>
#include <iomanip> 
#include <fstream>
#include <vector>
#include <algorithm>

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
void sortPriority(vector<Sim> &a);
Sim* sortPriority(Sim* p, const int size);
Sim* sortArrivalTime(Sim* p, const int size);
bool compareCPU(Sim a, Sim b); 
void printProcessCreate(int arrTime, int pId, int cpu);
void printContextSwitch(int waitTime, int location1, int location2);
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
		//fcfs(pArr, n); 
		//sjf(pArr, n); 
		//psjf(pArr, n); 
		//rr(pArr, n); 
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
	int temp = 0, tempA = 0, cpuTime, priority, i; 

	/* the for loop creates the dummy processes that will be sent into the 
	 * functions for testing the algorithms. The for loop will create the 
	 * process by giving it a random CPU time and priority number */ 
	for (i = 0; i < size; i++){
		cpuTime = rand() % 7000 + 500;  // This generates a random number between 500 - 7500
		priority = rand() % 5; 	        // this generates a random number between 0 and 4 
		Sim process(i+1, cpuTime, priority ); 
		pA[i] = process;  
	}
	cout << "Create Processes: \n"; 
	int tempWait = 0, eTemp;
	for (i = 0; i < size; i++)
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
	//for (int d = 0; d < size; d++)
	//{
	//	cout << "***CPU Time is " << pA[d].getcTime() << " and timeRemain is " << pA[d].getTimeRemain() << endl;
	//}
	
	temp = size * .25;  //sets temp to 25% of all processes with a decimal that gets chopped off 
	for(i = 0; i < temp; i ++){ pA[i].setATime(0); } // sets the first 25% to 0 arrival time
	
	//tempA = size - temp; //sets temp to the amount of the rest of the processes 
	for(i = temp; i < size; i ++) { 
		int aTime = rand() % 2400 + 100; // random number between 100 and 2500 
		pA[i].setATime(aTime); 
	}
		
	for(i = 0; i < size; i ++) {
		printProcessCreate(pA[i].getATime(), pA[i].getpId(), pA[i].getcTime());
	}

	sortArrivalTime(pA, size);
	
	return pA; 
}

/* First-Come First Served(FCFS) The processes will get sent into this function and then worked on in 
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
		p[j].setWaitTime(elapsedTime-p[j].getATime());	//subtract from its arrival time
		printFirst(elapsedTime, p[j].getpId(), p[j].getITime());
		elapsedTime += p[j].getcTime();
		p[j].setTurnTime(elapsedTime-p[j].getATime());	//subtract from its arrival time
		printTerminate(elapsedTime, p[j].getpId(), p[j].getTurnTime(), p[j].getWaitTime());
	} 
	dataToCollect(p, size, minTurn, maxTurn, turnT, minInitial, maxInitial, initialT, minWait, maxWait, totalW);
}

#ifndef sjf
/* Shortest-Job First (SFS)
 * This will sort the processes that are sent in based on the 
 * shortest job in the array. */ 
void sjf(Sim* p, int size)
{
	int tempWait = 0, minTurn = p[0].getTurnTime(), maxTurn = 0, 
		turnT = 0, minInitial = p[0].getITime(), maxInitial = 0, 
		initialT = 0, minWait = p[0].getWaitTime(), maxWait = 0, 
		totalW = 0;  

	elapsedTime = 0; 
	vector <Sim> arrived;

	int check = 1; 

	//push it into vector if it arrives at time 0
	for(int i = 0; i < size; i++)
	{
		if (p[i].getATime() == 0)
		{
			arrived.push_back(p[i]);
			check = i + 1;
		}
	}

	sort(arrived.begin(), arrived.end(), compareCPU); 

	cout << "\n\n\nShortest Job First without Preemption | Send Processes to CPU and run: \n"; 
	
	//for(int j = 0; j < size; j++) 
	int counter = 0;
	bool firstTime = true; 
	Sim temp; 
	while(counter != size)
	{ 
		for(int i = check; i < size; i++)
		{
			int totalTime = arrived[0].getcTime() + elapsedTime;
			if (totalTime > p[i].getATime())
			{
				arrived.push_back(p[i]);
				check = i + 1;
			}
		}
		temp = arrived[0];
		arrived.erase(arrived.begin()); // this process will have terminated so it can be removed from the vector
		sort(arrived.begin(), arrived.end(), compareCPU); // sorts all the processes that will be in the vector after the one terminates

		temp.setWaitTime(elapsedTime);
		printFirst(elapsedTime, temp.getpId(), temp.getWaitTime());	
		elapsedTime+=temp.getcTime(); 
		temp.setTurnTime(elapsedTime);
		printTerminate(elapsedTime, temp.getpId(), temp.getTurnTime(), temp.getWaitTime()); 
		firstTime = false;
		counter ++; 

		if (!firstTime && !arrived.empty( ))
		{
			elapsedTime = totalElapsedTime(elapsedTime); 
			printContextSwitch(elapsedTime, temp.getpId(), arrived[0].getpId());			
			elapsedTime = totalElapsedTime(elapsedTime);  
		} 
		
	} 

	dataToCollect(p, size, minTurn, maxTurn, turnT, minInitial, maxInitial, initialT, minWait, maxWait, totalW);
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
	int minTurn = p[0].getTurnTime(), maxTurn = 0, turnT = 0, minInitial = p[0].getITime(), 
		maxInitial = 0, initialT = 0, minWait = p[0].getWaitTime(), maxWait = 0, totalW = 0;  

	cout << "\n\n\nShortest Job First with Preemption | Send Processes to CPU and run: \n";

	elapsedTime = 0;

	//while there are still process remain
	for (int i = 0; i < size; i++)
	{
		p[i].setTimeRemain(p[i].getTimeRemain() - p[i+i].getATime());
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
	vector <Sim> arrived;	//vector that stores the processes that arrived

	//if the process arrives at time 0, push it back into the vector
	for (int k = 0; k < size; k++)
	{
		if(p[k].getATime() == 0)
		{
			arrived.push_back(p[k]);
		}
	}


	int temptime;

	while(counter != size) 
	{
		counter = 0; // re-set counter since counter != size in the last iteration therefore not all the processes are finished
		for(int k = arrived.size(); k < size; k++)
		{
			if ((elapsedTime+100*(arrived.size())) >= p[k].getATime())
			{
				arrived.push_back(p[k]);
			}
		}
		for (int j = 0; j < arrived.size(); j++)
		{
			if (arrived[j].getTimeRemain() != 0)
			{
				if(firstTime != true && store != arrived[j].getpId())
				{ 
					elapsedTime = totalElapsedTime(elapsedTime);
					printContextSwitch(elapsedTime, store, arrived[j].getpId()); 
					elapsedTime = totalElapsedTime(elapsedTime);
					arrived[j].setWaitTime(elapsedTime-arrived[j].getcTime());
				}
				if (arrived[j].getcTime() == arrived[j].getTimeRemain())
				{
					arrived[j].setWaitTime(elapsedTime);
					printFirst(elapsedTime, arrived[j].getpId(), arrived[j].getWaitTime());	
				}
				elapsedTime = elapsedTime + 100;
				arrived[j].setTimeRemain( arrived[j].getTimeRemain() - timeSlice );
				if (arrived[j].getTimeRemain() < 0)				// if remain time == 0, print "terminate"
				{
					int check = timeSlice + arrived[j].getTimeRemain(); // Checks to see if the program terminated before the timeslice
					elapsedTime = elapsedTime - 100 + check; 		//subtract off the time that this slice did not use 
					arrived[j].setTimeRemain(0); 					//sets the time to 0
					arrived[j].setTurnTime(elapsedTime);
					printTerminate(elapsedTime, arrived[j].getpId(), arrived[j].getTurnTime(), arrived[j].getWaitTime()); 
					counter++; 								// This processes is now added to the "ended" counter 
				}
				store = arrived[j].getpId(); 
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
	int tempWait = 0, minTurn = p[0].getTurnTime(), maxTurn = 0, turnT = 0, minInitial = p[0].getITime(), 
		maxInitial = 0, initialT = 0, minWait = p[0].getWaitTime(), maxWait = 0, totalW = 0;  

	vector <Sim> arrived;	//vector to store processes that has arrived
	int counter = 0;
	int store = 0;
	bool firstTime = true;

	elapsedTime = 0;

	for (int i = 0; i < size; i++)
	{
		cout << "Process " << p[i].getpId() << " has a priority of " << p[i].getP() << endl;
	}

	cout << "\n\n\nPreemptive-Priority | Send Processes to CPU and run: \n";


	//push process into the vector if the arrival time is 0
	for (int i = 0; i < size; i++)
	{
		if (p[i].getATime() == 0)
		{
			arrived.push_back(p[i]);
		}
	}

	//Sort "arrived" by priority
	sortPriority(arrived);

	while(counter != size)
	{
		int checkArrival; 
		int timeShortest = 8000;
		bool found = false; 
		for (int i = 0; i < size; i++)
		{	
			//if the next process arrives before the current process finish running, THEN push_back(new process) & pause when new process arrives
			if ((arrived[0].getTimeRemain() + elapsedTime) > p[i].getATime())
			{
				if(p[i].getATime() < timeShortest)
				{
					timeShortest = p[i].getATime(); 
				}
				found = true;
			}
		}

		if(found == true)
		{ 
			arrived[0].setTimeRemain(elapsedTime - arrived[0].getcTime());	// set the remain time for current process
			elapsedTime = elapsedTime - arrived[0].getTimeRemain(); 
			for(int i = 0; i < size; i ++)
			{ 
				if(p[i].getATime() == timeShortest) 
				{
					arrived.push_back(p[i]);
				}
			}
			sortPriority(arrived);
		}
		for(int i = 0; i < arrived.size(); i++)
		{
			if (arrived[i].getTimeRemain() != 0)
			{
				if(firstTime != true && store != arrived[i].getpId())
				{ 
					elapsedTime = totalElapsedTime(elapsedTime);
					printContextSwitch(elapsedTime, store, arrived[i].getpId()); 
					elapsedTime = totalElapsedTime(elapsedTime);
					arrived[i].setWaitTime(elapsedTime-arrived[i].getcTime());
				}
				if (arrived[i].getcTime() == arrived[i].getTimeRemain())
				{
					arrived[i].setWaitTime(elapsedTime);
					printFirst(elapsedTime, arrived[i].getpId(), arrived[i].getWaitTime());	
				}
				
				//arrived[i].setTimeRemain(0);
				elapsedTime = elapsedTime + arrived[i].getcTime() - arrived[i].getTimeRemain();
				if (arrived[i].getTimeRemain() < 0)				// if remain time == 0, print "terminate"
				{
					//int check = timeSlice + arrived[j].getTimeRemain(); // Checks to see if the program terminated before the timeslice
					
					
					arrived[i].setTimeRemain(0); 					//sets the time to 0
					arrived[i].setTurnTime(elapsedTime);
					printTerminate(elapsedTime, arrived[i].getpId(), arrived[i].getTurnTime(), arrived[i].getWaitTime()); 
					counter++; 								// This processes is now added to the "ended" counter 
				}

				store = arrived[i].getpId(); 
			}
			counter++;
			firstTime = false; 
		}
	}
	
	
	/*
	for(int j = 0; j < size; j++) 
	{ 
		if (j != 0)
		{
			elapsedTime = totalElapsedTime(elapsedTime); 
			printContextSwitch(elapsedTime, pSorted[j-1].getpId(), pSorted[j].getpId());	
			elapsedTime = totalElapsedTime(elapsedTime); 
		} 
		pSorted[j].setWaitTime(elapsedTime);
		printFirst(elapsedTime, pSorted[j].getpId(), pSorted[j].getWaitTime());	
		elapsedTime+=pSorted[j].getcTime(); 
		pSorted[j].setTurnTime(elapsedTime);
		printTerminate(elapsedTime, pSorted[j].getpId(), pSorted[j].getTurnTime(), pSorted[j].getWaitTime()); 
	} 
	*/
	//dataToCollect(pSorted, size, minTurn, maxTurn, turnT, minInitial, maxInitial, initialT, minWait, maxWait, totalW);
}

void sortPriority(vector<Sim> &a){

	//Sort "arrived" by priority
	for (int i = 0; i < a.size(); i++)
	{
		for (int j = i; j < a.size(); j++)
		{
			if(a[i].getP() > a[j].getP())
			{
				swap(a[i], a[j]);
			}
		}
	}
}


Sim* sortPriority(Sim* p, const int size)
{ 
	for(int i = 0; i < size; i ++) 
	{ 
		for(int j = 0; j < size; j++)
		{
			if (p[i].getP() < p[j].getP())
			{
				swap(p[i],p[j]);
			}
		}
	} 
	return p; 
}
/* sorts by arrival time and then 
 * sorts by the CPU time */ 
Sim* sortArrivalTime(Sim* p, const int size)
{ 
	for(int i = 0; i < size; i ++) 
	{ 
		for(int j = i+1; j < size; j++)
		{
			if (p[i].getATime() > p[j].getATime())
			{
				swap(p[i],p[j]);
			}	
		}
	} 
	return p; 
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
	cout << "Minimum Turn Around Time: " << (double)minTurnAround << "\n"; 
	cout << "Maximum Turn Around Time: " << (double)maxTurnAround << "\n"; 
	tempTime = (double)turnTotal/(double)size; 
	cout << "Average Turn Around Time: " << tempTime << "\n\n";

	cout << "Minimum Initial Wait Time: " << (double)minInitialWait << "\n"; 
	cout << "Maximum Initial Wait Time: " << (double)maxInitialWait << "\n"; 
	tempTime = (double)initialTotal/(double)size; 
	cout << "Average Initial Wait Time: " << tempTime << "\n\n";

	cout << "Minimum Wait Time: " << (double)minWaitTime << "\n"; 
	cout << "Maximum Wait Time: " << (double)maxWaitTime << "\n"; 
	tempTime = (double)totalWait/(double)size; 
	cout << "Average Wait Time: " << tempTime << "\n\n";


}

bool compareCPU(Sim a, Sim b)
{
	return a.getcTime() < b.getcTime();
}

#ifndef printFunctions 
/* printProcessCreate will print the processes that were 
 * created in the Sim array */ 
void printProcessCreate(int arrTime, int pId, int cpu)
{ 
		cout << "[time " << arrTime << "ms] Process " << pId 
			<< " created (requiring " << cpu << "ms CPU time)\n";
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

#endif