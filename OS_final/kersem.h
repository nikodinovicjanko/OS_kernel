/*
 * kersem.h
 *
 *  Created on: Apr 27, 2020
 *      Author: OS1
 */

#ifndef KERSEM_H_
#define KERSEM_H_

#include "semaphor.h"
#include "List.h"

class KernelSem
{
   // private:

   public:

   volatile int value;
   List *blocked;
  // List *blockedTime;

   KernelSem(int init);

   int wait(Time maxTime);
   int signal(int n);

   int val() const {return value; }
};

#endif /* KERSEM_H_ */
