/*
 * Semaphor.cpp
 *
 *  Created on: Apr 27, 2020
 *      Author: OS1
 */

#include "Semaphor.h"
#include "kersem.h"
#include "lock.h"

Semaphore::Semaphore(int init) {

	lock
	myImpl = new KernelSem(init);
	unlock

}

Semaphore::~Semaphore() {

	lock;
    delete myImpl;
	unlock;
}

int Semaphore::wait(Time maxTime){

	lock;
	int ret = myImpl->wait(maxTime);
	unlock;
	return ret;
}

int Semaphore::signal(int n){

	lock;
	int ret = myImpl->signal(n);
	unlock;
	return ret;
}

int Semaphore::val() const{
	return myImpl->val();
}

