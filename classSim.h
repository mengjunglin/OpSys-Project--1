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
	int terminateTime;
	int waitTime;
	int timeRemain;

public: 
	Sim(); 
	Sim( int pId, int cTime, int p ); 
	void setCTime(int cTime);
	void setiTime( int iTime ); 
	void setTurnTime( int turnTime ); 
	void setTerminateTime( int terTime ); 
	void setWaitTime(int wTime);
	void setTimeRemain(int tRemain);
	void setPidId(int pId); 
	void setP(int p);
	int getpId(); 
	int getcTime(); 
	int getP(); 
	int getITime(); 
	int getTurnTime(); 
	int getTerminateTime(); 
	int getWaitTime();
	int getTimeRemain();
};

Sim::Sim(){ 
	processId = 0; 
	cpuTime = 0; 
	priority = 0; 
	initialWaitTime = 0; 
	turnAroundTime = 0; 
	terminateTime = 0;
	timeRemain = 0;
}

Sim::Sim( int pId, int cTime, int p ){
	processId = pId; 
	cpuTime = cTime; 
	priority = p; 
	// Set the initial times to 0
	initialWaitTime = 0; 
	turnAroundTime = 0; 
	terminateTime = 0; 
	waitTime = 0;
	timeRemain = 0;
}

void Sim::setCTime(int cTime){
	cpuTime = cTime;
}

void Sim::setiTime( int iTime ){ 
	initialWaitTime = iTime; 
}

void Sim::setTurnTime( int turnTime ){ 
	turnAroundTime = turnTime; 
} 

void Sim::setTerminateTime( int terTime ){ 
	terminateTime = terTime; 
}

void Sim::setWaitTime(int wTime){
	waitTime = wTime;
}

void Sim::setTimeRemain(int tRemain){
	timeRemain = tRemain;
}
void Sim::setPidId(int pId){ 
	processId = pId;
}
void Sim::setP(int p){
	priority = p; 
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

int Sim::getTerminateTime(){ 
	return terminateTime; 
}

int Sim::getWaitTime(){
	return waitTime;
}

int Sim::getTimeRemain(){
	return timeRemain;
}





