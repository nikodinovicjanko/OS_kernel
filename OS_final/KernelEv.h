/*
 * KernelEv.h
 *
 *  Created on: May 10, 2020
 *      Author: OS1
 */

#ifndef KERNELEV_H_
#define KERNELEV_H_

#include "Event.h"

class PCB;

class KernelEv {
public:
	KernelEv(IVTNo ivtN);
	virtual ~KernelEv();

	void wait();
	void signal();
protected:
	PCB* pcb;
	int ivtNo;
	int semVal;
	IVTEntry* myIntr;
};

#endif /* KERNELEV_H_ */
