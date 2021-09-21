/*
 * KernelEv.cpp
 *
 *  Created on: May 10, 2020
 *      Author: OS1
 */

#include "KernelEv.h"
#include "pcb.h"
#include "SCHEDULE.H"
#include "lock.h"

KernelEv::KernelEv(IVTNo ivtN) {//signal i wait !!
	pcb = PCB::running;
	ivtNo = ivtN;
	semVal = 1;//ili 1 proveriti
	myIntr = IVTEntry::IVTtable[ivtNo];
	myIntr->setKernelEv(this);
}

KernelEv::~KernelEv() {
	    signal(); //Ako je nit negde zablokirana
		pcb = 0;
		myIntr =0;
}

void KernelEv::signal(){
lock;
	if(pcb==0)return;
		if(pcb->state==BLOCKED){

			semVal = 1;
			pcb->state=READY;
			Scheduler::put(pcb);
		}
unlock;
}

void KernelEv::wait(){

	if(pcb!=PCB::running)return;

	   semVal=0;
	   pcb->state=BLOCKED;
	   dispatch();
}

