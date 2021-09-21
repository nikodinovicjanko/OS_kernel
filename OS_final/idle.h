/*
 * idle.h
 *
 *  Created on: Apr 30, 2020
 *      Author: OS1
 */

#ifndef IDLE_H_
#define IDLE_H_

#include "thread.h"

class Idle:public Thread {
public:
	Idle();
	void start();
	virtual void run();
	//virtual ~Idle();
};

#endif /* IDLE_H_ */
