/*
 * kersem.cpp
 *
 *  Created on: Apr 27, 2020
 *      Author: OS1
 */

#include "kersem.h"
#include "SCHEDULE.H"

KernelSem::KernelSem(int init){//RETURN U LOCK-U !!
	value = init;
	blocked = new List();
	//blockedTime = new List();
}
/*KernelSem::~kersem() {
	// TODO Auto-generated destructor stub
}*/
int KernelSem::wait(Time maxTime) {

	if (maxTime == 0){
		value--;

		if (value < 0){
				PCB::running->state = BLOCKED;
				blocked->put(PCB::running); 
				dispatch();
	}

		return 1;
   }

	                PCB::running->state = BLOCKED;
					PCB::running->blockTime = maxTime;
					PCB::blockedTime->put(PCB::running);
					dispatch();
	                return 0;

}

int KernelSem::signal(int n) {

	//if( n < 0)return n;

	if (n == 0){
		value++;
			if (value <= 0) {
				PCB* temp = blocked->get();
				temp->state = READY;
				Scheduler::put(temp);
			}
		return 0;
	}

	if (n > 0){
		value = value + n;
		int cnt = 0;

		while(cnt < n){//!

			PCB* temp = blocked->get();
			if (temp == 0)break;
			temp->state = READY;
			Scheduler::put(temp);
			cnt++;

		}

		return cnt;
	}

	return n;

}
