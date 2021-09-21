/*
 * PCB.cpp
 *
 *  Created on: Apr 14, 2020
 *      Author: OS1
 */

#include "PCB.h"
#include "lock.h"
#include <dos.h>
#include "SCHEDULE.H"
#include <iostream.h>

int PCB::sID = 0;
PCB* PCB::running = 0;
PCB* PCB::main = 0;
PCB* PCB::idle=0; //idle !!!!!!!!
int PCB::first = 0;
List *PCB::pcbList = new List();
List *PCB::blockedTime = new List();

PCB::PCB(StackSize stackSize, Time timeSlice, Thread* myT) {

    lock;
	myStackSize = stackSize;
	quantum = timeSlice;
	blockTime = 0;
	myThread = myT;

	state = NEW;
	threadID = ++sID;

	waitQueue = new List();

	 pcbList->put(this); //!!
    unlock;

}

PCB::~PCB() {

	lock;
	delete waitQueue;
	unlock;
}

void PCB::wrapper(){
	running->myThread->run();
	lock;
	PCB::pcbList->deleteElem(running); 
	running->state = OVER;

	PCB* temp;
	while(!running->waitQueue->empty()){
		temp = running->waitQueue->get();
		temp->state = READY;
		//cout<<"ODblokirala se nit "<<temp->threadID<<endl;
		Scheduler::put(temp);
	}
    //cout<<"GOTOVA NIT"<<PCB::running->threadID<<endl;
	dispatch();
	unlock; 
}

void PCB::createStack() {

	lock;
	myStackSize/=sizeof(unsigned);
	stack = new unsigned int[myStackSize];

	// setovanje I flega u pocetnom PSW-u za nit
		stack[myStackSize-1] =0x200;

		// postavljanje adrese funkcije koju ce nit da izvrsava
		stack[myStackSize-2] = FP_SEG(&wrapper);
		stack[myStackSize-3] = FP_OFF(&wrapper);

		//svi sacuvani registri pri ulasku u interrupt rutinu
		sp = FP_OFF(stack + myStackSize - 12);
		ss = FP_SEG(stack + myStackSize - 12);
    unlock;
		//bp = sp;


}

Thread* PCB::setMain(){

	if (!first){
		Thread* t = new Thread();
		running = t->myPCB;
		main = running;//!!!
		running->state = READY;
		first = 1;
		return t;
	}
	return 0;
}

