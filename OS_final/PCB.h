/*
 * PCB.h
 *
 *  Created on: Apr 14, 2020
 *      Author: OS1
 */

#ifndef PCB_H_
#define PCB_H_

#include "List.h"
//#include "idle.h"
#include "thread.h"

typedef enum {NEW, READY, BLOCKED, OVER} State;
class List;


class PCB {
private:

	static int first;

public:

	PCB(StackSize stackSize, Time timeSlice, Thread*);
	virtual ~PCB();

	int threadID;
	static int sID;

	void createStack();
	unsigned int sp, ss;
	unsigned *stack;

	StackSize myStackSize;
	Time quantum;//vreme running stanja
	Time blockTime; //za semafore !!!
	Thread *myThread;

	State state;

    static PCB* running;
	static PCB* main;
	static PCB* idle; 
	static void wrapper();

	static List *pcbList;
	static List *blockedTime;
	List *waitQueue;

	friend class Thread;
	static Thread* setMain();
};

#endif /* PCB_H_ */
