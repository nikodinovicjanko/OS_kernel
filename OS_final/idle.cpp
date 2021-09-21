/*
 * idle.cpp
 *
 *  Created on: Apr 30, 2020
 *      Author: OS1
 */

#include "idle.h"
#include "PCB.h"
#include "lock.h"
#include <iostream.h>

Idle::Idle():Thread() {
	// TODO Auto-generated constructor stub

}

void Idle::run()
{
while (1);
}

void Idle::start()
{
  lock;
 //ne stavlja u red spremnih vec explicitno poziva je red spremnih prazan
myPCB->state = READY;
myPCB->createStack();
PCB::idle = myPCB;
 unlock;
}



/*Idle::~Idle() {
	// TODO Auto-generated destructor stub
}*/

