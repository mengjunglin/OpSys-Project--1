/* Tiffany Milano and Meng Jung Lin 
 * Project 1 - Operating Systems 
 * October 20th 2011 */ 

#include <iostream>
using namespace std;

class Sim{ 
private: 
	int processId; 
	int cpuTime; 
	int priority; 
	int initialWaitTime; 
	int turnAroundTime; 
	int totalWaitTime; 

public: 
	Sim(); 
	Sim( int pId, int cTime, int p ); 
	void setiTime( int iTime ); 
	void setTurnTime( int turnTime ); 
	void setTotalTime( int totalTime ); 
	int getpId(); 
	int getcTime(); 
	int getP(); 
	int getITime(); 
	int getTurnTime(); 
	int getTotalTime(); 
};

Sim::Sim(){ 
	processId = 0; 
	cpuTime = 0; 
	priority = 0; 
	initialWaitTime = 0; 
	turnAroundTime = 0; 
	totalWaitTime = 0; 
}

Sim::Sim( int pId, int cTime, int p ){
	processId = pId; 
	cpuTime = cTime; 
	priority = p; 
	// Set the initial times to 0
	initialWaitTime = 0; 
	turnAroundTime = 0; 
	totalWaitTime = 0; 
}

void Sim::setiTime( int iTime ){ 
	initialWaitTime = iTime; 
}

void Sim::setTurnTime( int turnTime ){ 
	turnAroundTime = turnTime; 
} 

void Sim::setTotalTime( int totalTime ){ 
	totalWaitTime = totalTime; 
}

int Sim::getpId(){ 
	return processId; 
}	
	
int Sim::getcTime(){ 
	return cpuTime; 
}

int Sim::getP(){ 
	return priority; 
}

int Sim::getITime(){
	return initialWaitTime; 
}

int Sim::getTurnTime(){ 
	return turnAroundTime; 
}

int Sim::getTotalTime(){ 
	return totalWaitTime; 
}





