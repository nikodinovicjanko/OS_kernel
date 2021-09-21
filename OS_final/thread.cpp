/*
 * thread.cpp
 *
 *  Created on: Apr 13, 2020
 *      Author: OS1
 */

#include "thread.h"
#include "SCHEDULE.H"
#include "PCB.h"
#include "lock.h"
#include <iostream.h>

Thread::Thread(StackSize stackSize, Time timeSlice) {

	lock;
	myPCB = new PCB(stackSize,timeSlice,this);
	unlock;

}

Thread::~Thread(){

	lock;
	waitToComplete();
	delete myPCB;
	unlock;

}

void Thread::start(){
	lock;
	myPCB->state = READY;
	myPCB->createStack();
	Scheduler::put(myPCB);
	unlock;
}

ID Thread::getId(){
	return myPCB->threadID;
}

Thread *Thread::getThreadById(ID id){
	//cout<<id<<endl;
	return PCB::pcbList->findID(id);
}

ID Thread::getRunningId(){
	return PCB::running->threadID;
}

void Thread::waitToComplete(){
	lock;

	//ne cekamo ako je nit zavrsila
	if (myPCB->state == OVER){
		unlock
		return;
	}

	//nit ne ceka samu sebe
	if (myPCB == PCB::running){
		unlock
		return;
	}

	//nit ne radi nista
    if(myPCB == PCB::idle){
		unlock
		return;
	}


    //cout<<"Zablokirala se nit "<<PCB::running->threadID<<endl;
    //cout<<"Zbog niti "<<this->getId()<<endl;
	PCB::running->state = BLOCKED; //doraditi!!!!- u wrapper()-u sredjeno
	myPCB->waitQueue->put(PCB::running); 
	//cout<<"WAIT\n";
	dispatch();
	unlock;
}

