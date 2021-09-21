/*
 * List.h
 *
 *  Created on: Apr 13, 2020
 *      Author: OS1
 */

#ifndef LIST_H_
#define LIST_H_

#include<stdio.h>
#include "pcb.h"
#include"thread.h"

class PCB;

class List {
	struct Element {
			PCB* pcb; 
			Element* next;
			Element(PCB* p, Element* s=0){
				pcb = p;
				next = s;
			}
		};
	Element* first, *last;
public:
	List():first(0),last(0) {};
	virtual ~List();

	void put(PCB* pcb);
	PCB* get();
	int empty() const { return first == 0;}

    Thread* findID(ID idToFind);
	int deleteElem(PCB* pcb);
	void update();




};

#endif /* LIST_H_ */
