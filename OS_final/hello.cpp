//  v2_zad3.cpp
//  prevodjenje iz komandne linije: bcc -mh -Ic:\bc31\include -Lc:\bc31\lib v2_zad3.cpp

#include <iostream.h>
#include <dos.h>
#include"SCHEDULE.H"
#include"PCB.h"
#include"lock.h"
#include <stdlib.h>//za test
#include "idle.h"
#include "Semaphor.h"
//#include "user.h"
//#include"thread.h"


//ZA TIMER-------------------------
volatile unsigned tsp; 
volatile unsigned tss;

// stara prekidna rutina
unsigned oldTimerOFF, oldTimerSEG; //inic i restore


volatile int cntr = 20;
volatile int context_switch = 0;



// prekidna rutina
void interrupt timer() {

            if (!context_switch && PCB::running->quantum!=0) cntr--;
            if (!context_switch && !(PCB::blockedTime->empty()))
            		PCB::blockedTime->update();
			if (cntr == 0 || context_switch) {

				asm {
					// cuva sp
					mov tsp, sp
					mov tss, ss
				}

				PCB::running->sp = tsp;
				PCB::running->ss = tss;

	if (PCB::running->state == READY && PCB::running!=PCB::idle) Scheduler::put(PCB::running);


				//Scheduler::put(PCB::running); //ZBOG OVOGA NIJE HTELO!!!!
				PCB::running = Scheduler::get();

	if(PCB::running == 0)PCB::running = PCB::idle;

				tsp = PCB::running->sp;
				tss = PCB::running->ss;
	            //quantum time slice !!!
	if(PCB::running->quantum !=0){
				cntr = PCB::running->quantum;
	             } else{
		         cntr=10;
	             }


				asm {
					// restaurira sp
					mov sp, tsp
					mov ss, tss
				}

			}


			// poziv stare prekidne rutine koja se nalazila na 08h, a sad je na 60h;
			// poziva se samo kada nije zahtevana promena konteksta tako da se stara rutina poziva samo kada je stvarno doslo do prekida
			if(!context_switch) {
				//tick();

				asm int 60h;
			}

			context_switch = 0;


}



void inic(){
	asm{
		cli
		push es
		push ax

		mov ax,0
		mov es,ax // es = 0

		// pamti staru rutinu
		mov ax, word ptr es:0022h
		mov word ptr oldTimerSEG, ax
		mov ax, word ptr es:0020h
		mov word ptr oldTimerOFF, ax

		// postavlja novu rutinu
		mov word ptr es:0022h, seg timer
		mov word ptr es:0020h, offset timer

		// postavlja staru rutinu
        // na int 60h - zasto?
		mov ax, oldTimerSEG
		mov word ptr es:0182h, ax
		mov ax, oldTimerOFF
		mov word ptr es:0180h, ax

		pop ax
		pop es
		sti
	}
}

// vraca staru prekidnu rutinu
void restore(){
	asm {
		cli
		push es
		push ax

		mov ax,0
		mov es,ax

		mov ax, word ptr oldTimerSEG
		mov word ptr es:0022h, ax
		mov ax, word ptr oldTimerOFF
		mov word ptr es:0020h, ax

		pop ax
		pop es
		sti
	}
}





void dispatch(){
	lock
	context_switch = 1;
	timer();
	unlock
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
extern int userMain(int argc, char* argv[]);

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
int main(int argc, char* argv[]){
	Thread *starting = PCB::setMain();
	Idle *idl = new Idle();
	idl->start();
	cout<<"Idle "<<PCB::idle->quantum<<endl;
  inic();
  //dispatch();
  //printf("User main starts\n");
  int value = userMain(argc, argv);
  	//printf("User main ends\n");
  restore();
 //cout<<"Srecan kraj!!"<<value<<endl;
  return 0;
}

