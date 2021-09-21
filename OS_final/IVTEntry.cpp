/*
 * IVTEntry.cpp
 *
 *  Created on: May 10, 2020
 *      Author: OS1
 */

#include "IVTEntry.h"
#include "lock.h"
#include "KernelEv.h"
#include <dos.h>

IVTEntry* IVTEntry::IVTtable[256] = {0, 0};

IVTEntry::IVTEntry(int numEntry, pInterrupt interruptRoutine) {//proveriti!

        lock;
		entry = numEntry;
	#ifndef BCC_BLOCK_IGNORE
		oldRoutine = getvect(entry);
		setvect(entry, interruptRoutine);
	#endif
		IVTtable[numEntry] = this;
		myKernelEv = 0;
		unlock;

}

void IVTEntry::setKernelEv(KernelEv* kerEvent){
#ifndef BCC_BLOCK_IGNORE
	lock
#endif
	myKernelEv = kerEvent;
#ifndef BCC_BLOCK_IGNORE
	unlock
#endif
}

void IVTEntry::callOldRoutine(){
#ifndef BCC_BLOCK_IGNORE
	lock
#endif
	oldRoutine();
#ifndef BCC_BLOCK_IGNORE
	unlock
#endif
}

void IVTEntry::signal(){
#ifndef BCC_BLOCK_IGNORE
	lock
#endif
	if(myKernelEv != 0) {myKernelEv->signal();}
#ifndef BCC_BLOCK_IGNORE
	unlock
#endif
}



IVTEntry::~IVTEntry() {
#ifndef BCC_BLOCK_IGNORE
	lock
	setvect(entry, oldRoutine);
#endif
	myKernelEv = 0;
	IVTtable[entry] = 0;
	oldRoutine(); //Mora se pozvai stara rutina prilikom brisanja
#ifndef BCC_BLOCK_IGNORE
	unlock
#endif
}

