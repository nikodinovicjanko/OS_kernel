/*
 * Event.cpp
 *
 *  Created on: May 2, 2020
 *      Author: OS1
 */

#include "Event.h"
#include "lock.h"
#include "KernelEv.h"

Event::Event(IVTNo ivtNo) {
#ifndef BCC_BLOCK_IGNORE
	lock
#endif
	myImpl = new KernelEv(ivtNo);
#ifndef BCC_BLOCK_IGNORE
	unlock
#endif

}

void Event::wait(){

	lock;
	myImpl->wait();
	unlock;

}

void Event::signal(){
    lock;
	myImpl->signal();
	unlock;
}

Event::~Event() {
	lock;
	delete myImpl;
	myImpl = 0;
	unlock;
}

