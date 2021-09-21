/*
 * IVTEntry.h
 *
 *  Created on: May 10, 2020
 *      Author: OS1
 */

#ifndef IVTENTRY_H_
#define IVTENTRY_H_

class KernelEv;

typedef void interrupt (*pInterrupt)(...);

class IVTEntry {
private:
	int entry;
	KernelEv* myKernelEv;
	pInterrupt oldRoutine;

public:
	IVTEntry(int numEntry, pInterrupt interruptRoutine);
	virtual ~IVTEntry();

	static IVTEntry* IVTtable[256];

	void callOldRoutine();
	void signal();
	void setKernelEv(KernelEv* kerEvent);
};

#endif /* IVTENTRY_H_ */
