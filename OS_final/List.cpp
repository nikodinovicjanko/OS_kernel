/*
 * List.cpp
 *
 *  Created on: Apr 13, 2020
 *      Author: OS1
 */

#include "List.h"
#include "SCHEDULE.H"
#include <iostream.h>

List::~List() {
	// TODO Auto-generated destructor stub
	Element *current = first, *toDelete;
		while(current != 0){
			toDelete = current;
			current = current->next;
			delete toDelete;
		}
}

void List::put(PCB *pcb) {
	Element *current = new Element(pcb);
	if (!first) first = current;
	else last->next = current;
	last = current;
	//cout<<"Stavljen PCB "<< pcb->threadID<<endl;
}

PCB* List::get(){
	if (!first) return 0;
	Element* current = first;
	first  = first->next;
	PCB* pcb = current->pcb;
	delete current;
	return pcb;
}

Thread* List::findID(ID idToFind){
	//cout<<"Trazim... "<<idToFind<<endl;
	Element *current = first;
	while(current != NULL){
		if (idToFind == current->pcb->threadID){
			//cout<<" Nadjena nit "<< current->pcb->myThread->getId();
			return current->pcb->myThread;}
		else {
			//cout<<"Nit "<< current->pcb->myThread->getId();
			current = current->next;}
	}
	//cout<<"NISTA\n";
	return NULL;
}

int List::deleteElem(PCB* pcb){
	if (first == NULL) return 0;

	Element *current = first->next, *previous = first, *temp = NULL;
	if (first->pcb == pcb){
		if (first == last) first = last = NULL;
		else first = current;
		delete previous;
		return 1;
	}
	if (!current) return 0;

	while ((current->pcb != pcb) && (current->next != NULL)){
		previous = previous->next;
		current = current->next;
	}

	if (current->pcb == pcb){
		temp = current;
		previous->next = current->next;
		if (current == last) last = previous;
		delete temp;
		return 1;
	} else return 0;
}

void List::update(){
	Element *current = first;
	while (current != NULL) {
		Element *temp = current->next;
		if (current->pcb->blockTime == 0){
			current->pcb->state = READY;
			Scheduler::put(current->pcb);

			//printf("Vracena nit");
			deleteElem(current->pcb);
		}
		else{
			current->pcb->blockTime = current->pcb->blockTime - 1;
			}
		current = temp;
		}

	}

